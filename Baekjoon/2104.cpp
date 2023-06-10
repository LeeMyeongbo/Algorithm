#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

unsigned int N, S, leftTree[1 << 18], rightTree[1 << 18];
long long sumTree[1 << 18];

long long search(int index, int left, int right, int& r1, int& r2)
{
    if (left > r2 || right < r1)
        return 0;

    if (left >= r1 && right <= r2)
        return sumTree[index];

    int mid = (left + right) >> 1;
    return search(index << 1, left, mid, r1, r2) + search((index << 1) + 1, mid + 1, right, r1, r2);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    memset(rightTree, UINT32_MAX, sizeof(rightTree));
    memset(leftTree, UINT32_MAX, sizeof(leftTree));

    cin >> N;
    S = 1 << (int)ceil(log2(N));

    for (register int i = 0; i < N; ++i)
    {
        register int idx = S + i;

        cin >> rightTree[idx];
        sumTree[idx] = rightTree[S + i];
        
        while (idx >> 1)
        {
            sumTree[idx >> 1] += rightTree[S + i];
            rightTree[idx >> 1] = min(rightTree[idx >> 1], rightTree[idx]);
            idx >>= 1;
        }
    }
    
    long long ans = 0;
    for (register int i = 0; i < N; ++i)
    {
        register int idx = S + i, cur = rightTree[idx], leftidx = 0, rightidx = N + 1;

        leftTree[idx] = cur;
        while (idx >> 1)
        {
            leftTree[idx >> 1] = min(leftTree[idx >> 1], leftTree[idx]);
            idx >>= 1;
        }

        // 현재 A[i]보다 왼쪽에 있는 A값들 중 A[i]보다 작으면서 가장 오른쪽에 있는 A값의 위치 구함
        register int index = 1;
        if (leftTree[index] < cur)
        {
            while (index < S)
            {
                if (leftTree[(index << 1) + 1] < cur)
                    index = (index << 1) + 1;
                else
                    index <<= 1;
            }
            leftidx = index - S + 1;
        }

        // 현재 A[i]보다 오른쪽에 있는 A값들 중 A[i]보다 작으면서 가장 왼쪽에 있는 A값의 위치 구함
        index = 1;
        if (rightTree[index] < cur)
        {
            while (index < S)
            {
                if (rightTree[index << 1] < cur)
                    index <<= 1;
                else
                    index = (index << 1) + 1;
            }
            rightidx = index - S + 1;
        }

        idx = S + i;
        rightTree[idx] = UINT32_MAX;
        idx >>= 1;
        while (idx)
        {
            rightTree[idx] = min(rightTree[idx << 1], rightTree[(idx << 1) + 1]);
            idx >>= 1;
        }

        ans = max(ans, search(1, 1, S, ++leftidx, --rightidx) * cur);
    }

    cout << ans;

    return 0;
}
