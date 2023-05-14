#include <string.h>

struct Result {
    int top;
    int count;
};

struct Node {
    int lazy, max, min;
} tree[4000000];
int n;
long long cnt;

void init(int C)
{
    memset(tree, 0, sizeof(tree));
    cnt = 0, n = C;
}

void prop(int index, int left, int right)
{
    if (tree[index].lazy)
    {
        tree[index].max += tree[index].lazy;
        tree[index].min += tree[index].lazy;

        if (left != right)
        {
            tree[index << 1].lazy += tree[index].lazy;
            tree[(index << 1) + 1].lazy += tree[index].lazy;
        }

        tree[index].lazy = 0;
    }
}

Node update(int index, int left, int right, int r1, int r2, int diff)
{
    prop(index, left, right);
    if (left > r2 || right < r1)
        return tree[index];

    if (left >= r1 && right <= r2)
    {
        tree[index].max += diff;
        tree[index].min += diff;

        if (left != right)
        {
            tree[index << 1].lazy += diff;
            tree[(index << 1) + 1].lazy += diff;
        }

        return tree[index];
    }
    register int mid = (left + right) >> 1;
    Node lnode = update(index << 1, left, mid, r1, r2, diff);
    Node rnode = update((index << 1) + 1, mid + 1, right, r1, r2, diff);

    return tree[index] = { 0, lnode.max > rnode.max ? lnode.max : rnode.max, lnode.min < rnode.min ? lnode.min : rnode.min };
}

Result dropBlocks(int mCol, int mHeight, int mLength)
{
    cnt += mHeight * mLength;

    register Node node = update(1, 0, n - 1, mCol, mCol + mLength - 1, mHeight);
    register int top = node.max - node.min;
    register int count = (cnt - n * node.min) % 1000000;
    
    return { top, count };
}
