#include <iostream>
#include <cmath>
using namespace std;

struct Node {
    int val, lazy;
} tree[1 << 20];
int N, M, S, i, j, k, query;

void prop(int index)
{
    if (tree[index].lazy)
    {
        if (index < S)
        {
            tree[index << 1].lazy ^= tree[index].lazy;
            tree[(index << 1) + 1].lazy ^= tree[index].lazy;
        }
        else
            tree[index].val ^= tree[index].lazy;

        tree[index].lazy = 0;
    }
}

void update(int index, int left, int right, int& r1, int& r2, int& diff)
{
    prop(index);
    if (left > r2 || right < r1)
        return;

    if (left >= r1 && right <= r2)
    {
        if (index < S)
        {
            tree[index << 1].lazy ^= diff;
            tree[(index << 1) + 1].lazy ^= diff;
        }
        else
            tree[index].val ^= diff;

        return;
    }

    int mid = (left + right) >> 1;
    update(index << 1, left, mid, r1, r2, diff);
    update((index << 1) + 1, mid + 1, right, r1, r2, diff);

    tree[index].val = tree[index << 1].val ^ tree[(index << 1) + 1].val;
}

int search(int index, int left, int right, int& r1, int& r2)
{
    prop(index);
    if (left > r2 || right < r1)
        return 0;

    if (left >= r1 && right <= r2)
        return tree[index].val;

    int mid = (left + right) >> 1, next = index << 1;
    return search(next, left, mid, r1, r2) ^ search(next + 1, mid + 1, right, r1, r2);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N;
    S = 1 << (int)ceil(log2(N));
    
    for (register int idx = 0; idx < N; ++idx)
    {
        int index = S + idx;
        cin >> tree[index].val;
        
        while (index >> 1)
        {
            tree[index >> 1].val ^= tree[S + idx].val;
            index >>= 1;
        }
    }

    cin >> M;
    for (register int q = 0; q < M; ++q)
    {
        cin >> query >> i >> j;
        if (query == 1)
        {
            cin >> k;
            update(1, 0, S - 1, i, j, k);
        }
        else
            cout << search(1, 0, S - 1, i, j) << '\n';
    }

    return 0;
}
