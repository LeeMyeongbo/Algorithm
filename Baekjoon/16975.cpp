#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Node {
    long long value, lazy;
};
vector<Node> tree;

void prop(int index, int left, int right)
{
    if (tree[index].lazy)
    {
        tree[index].value += (right - left + 1) * tree[index].lazy;

        if (left != right)
        {
            tree[index << 1].lazy += tree[index].lazy;
            tree[(index << 1) + 1].lazy += tree[index].lazy;
        }
        tree[index].lazy = 0;
    }
}

long long update(int index, int left, int right, int r1, int r2, long long diff)
{
    prop(index, left, right);
    if (left > r2 || right < r1)
        return tree[index].value;

    if (left >= r1 && right <= r2)
    {
        tree[index].value += diff * (right - left + 1);
        if (left != right)
        {
            tree[index << 1].lazy += diff;
            tree[(index << 1) + 1].lazy += diff;
        }

        return tree[index].value;
    }

    int mid = (left + right) >> 1;
    return tree[index].value = update(index << 1, left, mid, r1, r2, diff) + update((index << 1) + 1, mid + 1, right, r1, r2, diff);
}

long long search(int index, int left, int right, int r1, int r2)
{
    prop(index, left, right);
    if (left > r2 || right < r1)
        return 0;

    if (left >= r1 && right <= r2)
        return tree[index].value;

    int mid = (left + right) >> 1;
    return search(index << 1, left, mid, r1, r2) + search((index << 1) + 1, mid + 1, right, r1, r2);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    register int N, S, M, query, i, j, k, val;
    cin >> N;

    S = 1 << (int)ceil(log2(N));
    tree.resize(S << 1, {0, 0});

    for (register unsigned int n = 0; n < N; n++)
    {
        register int index = S + n;
        cin >> val;

        while (index)
        {
            tree[index].value += val;
            index >>= 1;
        }
    }

    cin >> M;
    while (M--)
    {
        cin >> query;
        if (query == 1)
        {
            cin >> i >> j >> k;
            update(1, 1, S, i, j, k);
        }
        else
        {
            cin >> i;
            cout << search(1, 1, S, i, i) << '\n';
        }
    }

    return 0;
}
