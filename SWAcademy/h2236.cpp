#include <string>
#include <cstring>
#include <unordered_map>
#define BASE(x) x == 'A' ? 0 : x == 'G' ? 1 : x == 'C' ? 2 : 3
using namespace std;

unordered_map<int, string> BaseList;

struct Trie {
    Trie* c[4];
    int cnt, id;

    Trie() {
        memset(c, NULL, sizeof(c));
        cnt = 0, id = 0;
    }
};
Trie* head;

Trie* destroyTrie(Trie* node)
{
    if (node)
    {
        for (register int i = 0; i < 4; i++)
            node->c[i] = destroyTrie(node->c[i]);
        delete node;
    }

    return NULL;
}

Trie* erase(Trie* node, string& base, int idx)
{
    if (idx == base.size())
        return node;
    
    node->c[BASE(base[idx + 1])] = erase(node->c[BASE(base[idx + 1])], base, idx + 1);

    node->cnt--;
    if (idx == base.size() - 1)
        node->id = 0;

    if (!node->cnt)
    {
        delete node;
        return NULL;
    }

    return node;
}

void init()
{
    BaseList.clear();
    head = new Trie;
}

int addSeq(int mID, int mLen, char mSeq[])
{
    if (BaseList.count(mID))
        return 0;

    Trie* node = head;
    for (register int i = 0; i < mLen; i++)
    {
        register int baseIdx = BASE(mSeq[i]);
        if (!node->c[baseIdx])
            node->c[baseIdx] = new Trie;

        node = node->c[baseIdx];
    }

    if (node->id)
        return 0;

    BaseList.insert({ mID, string(mSeq) });

    node = head;
    for (register int i = 0; i < mLen; i++)
    {
        register int baseIdx = BASE(mSeq[i]);
        node = node->c[baseIdx];
        node->cnt++;
    }
    node->id = mID;

    return 1;
}

int searchSeq(int mLen, char mBegin[])
{
    Trie* node = head;
    for (register int i = 0; i < mLen; i++)
    {
        register int baseIdx = BASE(mBegin[i]);
        if (!node->c[baseIdx])
            return -1;

        node = node->c[baseIdx];
    }

    if (node->cnt > 1)
        return node->cnt;
    
    while (!node->id)
    {
        for (register int i = 0; i < 4; i++)
        {
            if (node->c[i])
            {
                node = node->c[i];
                break;
            }
        }
    }

    return node->id;
}

int eraseSeq(int mID)
{
    if (!BaseList.count(mID))
        return 0;

    string base = BaseList[mID];
    BaseList.erase(mID);
    head->c[BASE(base[0])] = erase(head->c[BASE(base[0])], base, 0);

    return 1;
}

int changeBase(int mID, int mPos, char mBase)
{
    if (!BaseList.count(mID))                                           // mID인 염기 서열이 없으면 실패
        return 0;

    string base = BaseList[mID];
    if (mPos >= base.size() || mBase == base[mPos])                     // mPos번째 위치가 없거나 mPos번째 문자가 이미 mBase라면 실패
        return 0;

    Trie* node = head;
    for (register int i = 0; i < mPos; i++)                             // 0번째에서부터 mPos - 1번째까지 이동
        node = node->c[BASE(base[i])];
    
    if (!node->c[BASE(mBase)])
        node->c[BASE(mBase)] = new Trie;
    node = node->c[BASE(mBase)];                                        // mPos번째를 mBase문자로 변환

    for (register int i = mPos + 1; i < base.size(); i++)
    {
        if (!node->c[BASE(base[i])])
            node->c[BASE(base[i])] = new Trie;
        node = node->c[BASE(base[i])];                                  // mPos + 1부터 base 끝까지 이동
    }
    
    if (node->id)                                                       // 이미 똑같은 염기 서열 존재 시 실패
        return 0;

    head->c[BASE(base[0])] = erase(head->c[BASE(base[0])], base, 0);    // 기존에 저장된 염기 서열은 지우고

    base[mPos] = mBase;                                                 // mPos번째를 mBase로 업데이트
    BaseList[mID] = base;

    node = head;
    for (char b : base)                                                 // 그리고 업데이트 된 염기 서열 새로 저장
    {
        if (!node->c[BASE(b)])
            node->c[BASE(b)] = new Trie;

        node = node->c[BASE(b)];
        node->cnt++;
    }
    node->id = mID;

    return 1;
}
