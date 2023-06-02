#include <iostream>
#include <cmath>
using namespace std;

int n, S, a[100000];
int leftTree[1 << 18];          // [0, j) 구간 내에서 원소 개수를 저장하는 인덱스 트리
int rightTree[1 << 18];         // (j, n) 구간 내에서 원소 개수를 저장하는 인덱스 트리

int search(int tree[], int index, int left, int right, int r1, int r2)
{
    if (left > r2 || right < r1)
        return 0;

    if (left >= r1 && right <= r2)
        return tree[index];

    int mid = (left + right) >> 1;
    return search(tree, index << 1, left, mid, r1, r2) + search(tree, (index << 1) + 1, mid + 1, right, r1, r2);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n;
    S = 1 << (int)ceil(log2(n));

    for (register int x = 0; x < n; ++x)
    {
        cin >> a[x];

        if (x)
        {
            register int idx = S + a[x] - 1;
            while (idx)
            {
                ++rightTree[idx];
                idx >>= 1;
            }
        }
    }

    register long long ans = 0;
    for (register int j = 1; j < n - 1; ++j)
    {
        register int idx = S + a[j - 1] - 1;
        while (idx)                 // leftTree에서 j - 1번 index 원소의 값 +1
        {
            ++leftTree[idx];
            idx >>= 1;
        }

        idx = S + a[j] - 1;
        while (idx)                 // rightTree에서 현재 j번 index 원소 값 -1
        {
            --rightTree[idx];
            idx >>= 1;
        }

        ans += (long long)search(leftTree, 1, 1, S, a[j] + 1, n) * search(rightTree, 1, 1, S, 1, a[j] - 1);
    }

    cout << ans;

    return 0;
}
