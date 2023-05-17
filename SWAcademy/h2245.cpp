#include <vector>
#include <cmath>
using namespace std;

extern bool checkCards(int mIndexA, int mIndexB, int mDiff);

vector<int> tree[1 << 17];
int S;

void buildTree(int node, int left, int right)
{
    if (node >= S || tree[node].empty())
        return;

    int mid = (left + right) >> 1;
    
    for (int& i : tree[node])
    {
        if (checkCards(0, i, mid))
            tree[node << 1].emplace_back(i);
        else
            tree[(node << 1) + 1].emplace_back(i);
    }

    buildTree(node << 1, left, mid);
    buildTree((node << 1) + 1, mid + 1, right);
}

void playGame(int N)
{
    for (register int i = 0; i < (S << 1); i++)
        tree[i].clear();

    S = 1 << (int)ceil(log2(N));            // N보다 크거나 같으면서 N과 가장 가까운 2^k 자연수
    
    for (register int i = 0; i < (N << 1); i++)
        tree[1].emplace_back(i);

    buildTree(1, 0, S - 1);

    for (int i = S + 1; i < (S << 1); i++)
    {
        if (tree[i].size() == 2)
            checkCards(tree[i][0], tree[i][1], 0);
        else if (tree[i].size() == 4)
        {
            if (checkCards(tree[i][0], tree[i][1], 0))
                checkCards(tree[i][2], tree[i][3], 0);
            else if (checkCards(tree[i][0], tree[i][2], 0))
                checkCards(tree[i][1], tree[i][3], 0);
            else if (checkCards(tree[i][0], tree[i][3], 0))
                checkCards(tree[i][1], tree[i][2], 0);
        }
        else
            break;
    }

    return;
}
