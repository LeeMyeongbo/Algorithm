#include <cmath>
#include <vector>
using namespace std;

struct Result {
    int top;
    int count;
};
struct Node {
    long long val, lazy, Max, Min;
};
vector<Node> tree;
int n;

void init(int C)
{
    tree = vector<Node>(1 << ((int)ceil(log2(C)) + 1));
    n = C;
}

void prop(int index, int left, int right)
{
    if (tree[index].lazy)
    {
        tree[index].val += (right - left + 1) * tree[index].lazy;
        tree[index].Max += tree[index].lazy;
        tree[index].Min += tree[index].lazy;

        if (left != right)
        {
            tree[index << 1].lazy += tree[index].lazy;
            tree[(index << 1) + 1].lazy += tree[index].lazy;
        }

        tree[index].lazy = 0;
    }
}

Node update(int index, int left, int right, int r1, int r2, long long diff)
{
    prop(index, left, right);
    if (left > r2 || right < r1)
        return tree[index];

    if (left >= r1 && right <= r2)
    {
        tree[index].val += (right - left + 1) * diff;
        tree[index].Max += diff;
        tree[index].Min += diff;

        if (left != right)
        {
            tree[index << 1].lazy += diff;
            tree[(index << 1) + 1].lazy += diff;
        }

        return tree[index];
    }
    int mid = (left + right) >> 1;
    Node lnode = update(index << 1, left, mid, r1, r2, diff);
    Node rnode = update((index << 1) + 1, mid + 1, right, r1, r2, diff);

    return tree[index] = { lnode.val + rnode.val, 0, max(lnode.Max, rnode.Max), min(lnode.Min, rnode.Min) };
}

Result dropBlocks(int mCol, int mHeight, int mLength)           // Segment Tree with lazy propagation
{
    register Node node = update(1, 0, n - 1, mCol, mCol + mLength - 1, mHeight);
    register int top = node.Max - node.Min;
    register int count = (node.val - node.Min * n) % 1000000;

    return { top, count };
}
