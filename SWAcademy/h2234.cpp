#include <cstring>
#include <algorithm>
#include <unordered_map>
#define MAX_STOCK_LEN 10
using namespace std;

struct Node {
    int gap, id, lazy;
} tree[1 << 18];
int n, price[100000], index2Id[100000];     // price[i] : 사전 순서가 i번째인 종목의 가격, index2Id[i] : 사전 순서가 i번째인 종목의 Id
pair<long long, int> hashNId[100000];       // hashNId[i] : 사전 순서가 i번째인 종목의 (해쉬값, Id)  
unordered_map<long long, int> hash2Index;   // (종목 이름의 해쉬값 : 해당 종목의 사전 순서)

void buildTree(int index, int left, int right)
{
    if (left == right)
    {
        tree[index].id = index2Id[left];
        return;
    }

    int mid = (left + right) >> 1;
    buildTree(index << 1, left, mid);
    buildTree((index << 1) + 1, mid + 1, right);

    // 초기에는 주가 변화량이 모두 0이므로 왼쪽, 오른쪽 자식의 종목 id값을 비교하여 작은 것을 부모의 id값으로 삼음
    tree[index].id = tree[index << 1].id < tree[(index << 1) + 1].id ? tree[index << 1].id : tree[(index << 1) + 1].id;
}

// lazy propagation
void prop(int index, int left, int right)
{
    if (tree[index].lazy)
    {
        tree[index].gap += tree[index].lazy;
        if (left != right)
        {
            tree[index << 1].lazy += tree[index].lazy;
            tree[(index << 1) + 1].lazy += tree[index].lazy;
        }
        tree[index].lazy = 0;
    }
}

Node updateTree(int index, int left, int right, int r1, int r2, int diff)
{
    prop(index, left, right);
    if (left > r2 || right < r1)
        return tree[index];

    if (left >= r1 && right <= r2)
    {
        tree[index].gap += diff;
        if (left != right)
        {
            tree[index << 1].lazy += diff;
            tree[(index << 1) + 1].lazy += diff;
        }

        return tree[index];
    }

    int mid = (left + right) >> 1;
    Node lnode = updateTree(index << 1, left, mid, r1, r2, diff);
    Node rnode = updateTree((index << 1) + 1, mid + 1, right, r1, r2, diff);

    // 왼쪽 자식의 주가 변화량이 더 크거나 혹은 변동값이 서로 같고 왼쪽의 id가 더 작다면 현재 노드에 왼쪽 자식의 노드 정보를 저장
    if (lnode.gap > rnode.gap || (lnode.gap == rnode.gap && lnode.id < rnode.id))
        return tree[index] = lnode;
    else
        return tree[index] = rnode;
}

Node searchTree(int index, int left, int right, int r1, int r2)
{
    prop(index, left, right);
    if (left > r2 || right < r1)                    // 현재 살피는 범위가 구하고자 하는 범위를 벗어나면 id에 -1 저장하여 리턴
        return { 0, -1, 0};

    if (left >= r1 && right <= r2)
        return tree[index];

    int mid = (left + right) >> 1;
    Node lnode = searchTree(index << 1, left, mid, r1, r2);
    Node rnode = searchTree((index << 1) + 1, mid + 1, right, r1, r2);
    
    if (lnode.id == -1)                             // 왼쪽 자식이 구하고자 하는 범위에 속하지 않을 때
        return rnode;
    else if (rnode.id == -1)                        // 오른쪽 자식이 속하지 않을 때
        return lnode;
    else
    {
        if (lnode.gap > rnode.gap || (lnode.gap == rnode.gap && lnode.id < rnode.id))
            return lnode;
        else
            return rnode;
    }
}

long long getKey(char stock[MAX_STOCK_LEN + 1])
{
    register long long key = 0;

    for (register int i = 0, bit = 45; stock[i]; ++i, bit -= 5)
        key |= (long long)stock[i] - 96 << bit;

    return key;
}

void init(int N, char mStocks[][MAX_STOCK_LEN + 1], int mPrices[])
{
    hash2Index.clear();
    memset(tree, 0, sizeof(tree));
    n = N;

    for (register int i = 0; i < N; ++i)
        hashNId[i] = { getKey(mStocks[i]), i };

    sort(hashNId, hashNId + N);
    
    for (register int i = 0; i < N; ++i)
    {
        hash2Index.insert({ hashNId[i].first, i });
        index2Id[i] = hashNId[i].second;
        price[i] = mPrices[index2Id[i]];
    }
    
    buildTree(1, 0, n - 1);
}

void changePrices(char mFromStock[], char mToStock[], int mPriceDiff)
{
    updateTree(1, 0, n - 1, hash2Index[getKey(mFromStock)], hash2Index[getKey(mToStock)], mPriceDiff);
}

int getPrice(char mStock[])
{
    register int index = hash2Index[getKey(mStock)];

    return price[index] + searchTree(1, 0, n - 1, index, index).gap;
}

int getMostIncreasedStock(char mFromStock[], char mToStock[])
{
    return searchTree(1, 0, n - 1, hash2Index[getKey(mFromStock)], hash2Index[getKey(mToStock)]).id;
}
