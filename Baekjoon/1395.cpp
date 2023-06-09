#include <iostream>
#include <cmath>
using namespace std;

struct Node {
    int on;                  // 구간 내 켜진 스위치 개수
    bool lazy;
} tree[1 << 18];
int N, M, S, o, s, t;

void prop(int& index, int& left, int& right)
{
    if (tree[index].lazy)
    {
        tree[index].on = right - left + 1 - tree[index].on;
        if (index < S)
        {
            tree[index << 1].lazy = !tree[index << 1].lazy;
            tree[(index << 1) + 1].lazy = !tree[(index << 1) + 1].lazy;
        }
        tree[index].lazy = false;
    }
}

void update(int index, int left, int right, int& r1, int& r2)
{
    prop(index, left, right);
    if (left > r2 || right < r1)
        return;

    if (left >= r1 && right <= r2)
    {
        tree[index].on = right - left + 1 - tree[index].on;
        if (index < S)
        {
            tree[index << 1].lazy = !tree[index << 1].lazy;
            tree[(index << 1) + 1].lazy = !tree[(index << 1) + 1].lazy;
        }

        return;
    }

    int mid = (left + right) >> 1;
    update(index << 1, left, mid, r1, r2);
    update((index << 1) + 1, mid + 1, right, r1, r2);

    tree[index] = { tree[index << 1].on + tree[(index << 1) + 1].on, false };
}

int search(int index, int left, int right, int& r1, int& r2)
{
    prop(index, left, right);
    if (left > r2 || right < r1)
        return 0;

    if (left >= r1 && right <= r2)
        return tree[index].on;

    int mid = (left + right) >> 1;
    return search(index << 1, left, mid, r1, r2) + search((index << 1) + 1, mid + 1, right, r1, r2);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M;
    S = 1 << (int)ceil(log2(N));

    for (register int q = 0; q < M; ++q)
    {
        cin >> o >> s >> t;
        if (!o)
            update(1, 1, S, s, t);
        else
            cout << search(1, 1, S, s, t) << '\n';
    }

    return 0;
}
