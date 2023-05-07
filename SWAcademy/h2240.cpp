#include <string>
#include <cstring>
#define S 65536
using namespace std;

struct Trie {
    Trie* t[26];
    int idx;

    Trie() {
        memset(t, NULL, sizeof(t));
        idx = -1;                               // 저장된 ID의 끝 글자가 아닌 경우는 -1 (반대로 끝 글자인 경우 해당 ID의 순번 저장)
    }
};
Trie* head;
int IDidx, tree[S << 1], cnt;                   // tree : 순번이 0번부터 IDidx번 까지의 저장된 id 개수를 저장하는 IndexedTree
string idList[50000];                           // idList[i] : 순번이 i번인 id 저장

void deleteIDs(Trie* node)                      // node로부터 시작해서 저장된 모든 id 삭제
{
    if (node)
    {
        for (int i = 0; i < 26; i++)
            deleteIDs(node->t[i]);

        if (node->idx != -1)
        {
            cnt++;
            register int index = S + node->idx;
            while (index)
            {
                tree[index]--;
                index >>= 1;
            }

            node->idx = -1;                     // ID 삭제했으므로 -1 처리
        }
    }
}

int getCnt(int index, int left, int right, int r1, int r2)
{
    if (left > r2 || right < r1)
        return 0;
    
    if (left >= r1 && right <= r2)
        return tree[index];

    int mid = (left + right) >> 1;
    return getCnt(index << 1, left, mid, r1, r2) + getCnt((index << 1) + 1, mid + 1, right, r1, r2);
}

void destroyTrie(Trie* node)
{
    if (node)
    {
        for (int i = 0; i < 26; i++)
            destroyTrie(node->t[i]);

        delete(node);
    }
}

void init()
{
    IDidx = 0;
    memset(tree, 0, sizeof(tree));
    fill(idList, idList + 50000, "");
    destroyTrie(head);

    head = new Trie;
}

void loginID(char mID[10])
{
    string id(mID);
    register int index = 0;
    register Trie* node = head;

    for (char c : id)
    {
        if (!node->t[c - 'a'])
            node->t[c - 'a'] = new Trie;
        node = node->t[c - 'a'];
    }

    if (node->idx != -1)                        // 만약 이미 저장되어 있던 ID라면 IndexedTree에서 삭제
    {
        index = S + node->idx;
        while (index)
        {
            tree[index]--;
            index >>= 1;
        }
    }
    node->idx = IDidx;                          // Trie에 해당 ID의 업데이트 된 순번 저장

    index = S + IDidx;                          // IndexedTree에 새로운 순번 반영
    while (index)
    {
        tree[index]++;
        index >>= 1;
    }

    idList[IDidx++] = id;
}

int closeIDs(char mStr[10])
{
    cnt = 0;
    string str(mStr);
    register Trie* node = head;

    for (char c : str)
    {
        if (node->t[c - 'a'])
            node = node->t[c - 'a'];
        else
            return 0;
    }
    
    deleteIDs(node);
    return cnt;
}

void connectCnt(int mCnt)
{
    register int index = 1, cntLeft = mCnt;
    while (index < S)                               // 먼저 mCnt개가 되려면 몇 번 순번까지 가야하는 지 구함
    {
        if (tree[index << 1] >= cntLeft)            // 왼쪽 서브트리에 있는 id 개수가 현재 찾고자 하는 개수보다 큰 경우 -> 왼쪽으로 이동
            index <<= 1;
        else                                        // 그렇지 않다면 현재 개수에서 왼쪽 서브트리 개수 뺀 다음 오른쪽으로 이동
        {
            cntLeft -= tree[index << 1];
            index = (index << 1) + 1;
        }
    }

    for (register int i = S; i <= index; i++)       // 몇 번 순번까지 mCnt개가 있는가를 알았으면 처음부터 해당 순번까지 모두 제거
    {
        if (tree[i])
        {
            register int cur = i;
            while (cur)
            {
                tree[cur]--;
                cur >>= 1;
            }

            register Trie* node = head;
            for (char c : idList[i - S])
                node = node->t[c - 'a'];

            node->idx = -1;                         // ID 삭제했으므로 -1 처리
        }
    }
}

int waitOrder(char mID[10])
{
    string id(mID);
    register Trie* node = head;

    for (char c : id)
    {
        if (node->t[c - 'a'])
            node = node->t[c - 'a'];
        else
            return 0;
    }

    if (node->idx != -1)
        return getCnt(1, 0, S - 1, 0, node->idx);   // mID가 있을 경우 mID의 순번까지 몇 개의 ID가 저장되어 있는지 구해서 반환

    return 0;
}
