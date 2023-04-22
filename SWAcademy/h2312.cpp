#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct Trie {
    Trie* tr[26];
    vector<string> words;            // Trie 내 해당 노드에 속하는 단어 저장

    Trie() {
        memset(tr, 0, sizeof(tr));
    }
};
struct Result {
	int mOrder;
	int mRank;
};
int cnt, parent[10000], view[10000];
unordered_map<string, int> word_index;
Trie* head;

int findUnion(int v)
{
    if (v == parent[v])
        return v;
    
    return parent[v] = findUnion(parent[v]);
}

int merge(int u, int v)
{
    u = findUnion(u);
    v = findUnion(v);
    
    if (u < v) swap(u, v);      // u를 더 크게 만듦
    parent[u] = v;              // 집합 번호를 더 작은 정점 번호에 맞춤
    view[v] += view[u];

    return view[v];
}

bool cmp(const string& s1, const string& s2) {
    int idx1 = word_index[s1], idx2 = word_index[s2];
    if (view[findUnion(idx1)] > view[findUnion(idx2)])
        return true;
    else if (view[findUnion(idx1)] == view[findUnion(idx2)])
        return s1.compare(s2) < 0 ? true : false;
    else
        return false;
}

void updateTrie(string word, bool insert)
{
    Trie* node = head;
    if (insert) 
        node->words.push_back(word);
    sort(node->words.begin(), node->words.end(), cmp);

    for (char c : word)
    {
        if (!node->tr[c - 'a'])
            node->tr[c - 'a'] = new Trie();
        node = node->tr[c - 'a'];

        if (insert) 
            node->words.push_back(word);
        sort(node->words.begin(), node->words.end(), cmp);
    }
}

void init()
{
    if (head) delete(head);
    cnt = 0;
    head = new Trie();
    word_index.clear();
    memset(view, 0, sizeof(view));

    for (int i = 0; i < 10000; i++)
        parent[i] = i;
    
	return;
}

void search(char mStr[], int mCount)
{
    string word(mStr);
    if (!word_index.count(word))        // mStr이 처음 들어올 시
    {
        word_index[word] = ++cnt;
        view[findUnion(word_index[word])] = mCount;
        updateTrie(word, true);
    }
    else                                // 처음이 아닐 시
    {
        view[findUnion(word_index[word])] += mCount;
        updateTrie(word, false);
    }

	return;
}

Result recommend(char mStr[])
{
    string word(mStr);

    Trie* node = head;
    sort(node->words.begin(), node->words.end(), cmp);

    for (int i = 0; i < min(5, (int)node->words.size()); i++)
        if (!word.compare(node->words[i]))
        {
            view[findUnion(word_index[word])]++;
            return {0, i + 1};
        }

    for (int l = 0; l < (int)word.length(); l++)
    {
        if (!node->tr[word[l] - 'a'])
            node->tr[word[l] - 'a'] = new Trie();
        node = node->tr[word[l] - 'a'];
        sort(node->words.begin(), node->words.end(), cmp);

        for (int i = 0; i < min(5, (int)node->words.size()); i++)
            if (!word.compare(node->words[i]))
            {
                view[findUnion(word_index[word])]++;
                return {l + 1, i + 1};
            }
    }

    return {0, 0};
}

int relate(char mStr1[], char mStr2[])
{
    string w1(mStr1), w2(mStr2);
    int idx1 = word_index[w1], idx2 = word_index[w2];
    
    return merge(idx1, idx2);
}

void Rank(char mPrefix[], int mRank, char mReturnStr[])
{
    Trie* node = head;
    for (int i = 0; mPrefix[i]; i++)
    {
        sort(node->words.begin(), node->words.end(), cmp);
        node = node->tr[mPrefix[i] - 'a'];
    }
    sort(node->words.begin(), node->words.end(), cmp);

    string str = node->words[mRank - 1];
    for (int i = 0; i < (int)str.length(); i++)
        mReturnStr[i] = str[i];
    
	return;
}
