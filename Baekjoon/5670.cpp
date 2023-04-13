#include <iostream>
#include <vector>
using namespace std;

struct Trie
{
    int word_index, child;      // word_index : 단어가 끝났을 경우 현재 단어가 몇 번째?
    Trie* ch[26];

    Trie() {
        fill(ch, ch + 26, nullptr);
        word_index = child = 0;
    }

    ~Trie() {
        for (int i = 0; i < 26; i++)
            if (ch[i])
                delete(ch[i]);
    }
};
Trie* head;
int ans;

void search(Trie* node, int input_sum)
{
    if (node->word_index)               // 단어가 다 입력이 되었으면 ans에 입력횟수 갱신
        ans += input_sum;
    
    for (int i = 0; i < 26; i++)
    {
        if (node->ch[i])
        {
            if (node->child > 1 || node->word_index || node == head)    // 단어의 시작 or 끝이거나 자식이 여럿일 때는 입력 횟수 + 1
                search(node->ch[i], input_sum + 1);
            else
                search(node->ch[i], input_sum);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int N;
    string str;
    cout << fixed;
    cout.precision(2);
    
    while (true)
    {
        cin >> N;
        if (cin.eof())
            return 0;
        
        vector<string> strs;
        head = new Trie();

        for (int n = 0; n < N; n++)
        {
            cin >> str;
            strs.push_back(str);
        }
        for (int i = 0; i < strs.size(); i++)
        {
            Trie* cur = head;
            int len = strs[i].length();
            for (int j = 0; j < len; j++)
            {
                if (!cur->ch[strs[i][j] - 'a'])
                {
                    cur->child++;
                    cur->ch[strs[i][j] - 'a'] = new Trie();
                }    
                if (j == len - 1)
                    cur->ch[strs[i][j] - 'a']->word_index = i + 1;  // 단어 입력 완료되면 해당 단어가 몇 번째였는지 저장
                
                cur = cur->ch[strs[i][j] - 'a'];
            }
        }
        search(head, 0);
        cout << (double)ans / (double)strs.size() << '\n';

        ans = 0;
        delete(head);
    }
}