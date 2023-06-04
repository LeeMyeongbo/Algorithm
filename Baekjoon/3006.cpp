#include <iostream>
#include <cmath>
using namespace std;

int cntTree[1 << 18], idx[100001];

int search(int index, int left, int right, int& r1, int& r2)
{
    if (left > r2 || right < r1)
        return 0;

    if (left >= r1 && right <= r2)
        return cntTree[index];

    int mid = (left + right) >> 1;
    return search(index << 1, left, mid, r1, r2) + search((index << 1) + 1, mid + 1, right, r1, r2);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    register int N, S, n;
    cin >> N;
    S = 1 << (int)ceil(log2(N));

    for (register int i = 1; i <= N; ++i)
    {
        cin >> n;
        idx[n] = i;

        register int index = S + i - 1;
        while (index)
        {
            ++cntTree[index];
            index >>= 1;
        }
    }

    register int start = 1, end = N;
    for (register int i = 1; i <= N; ++i)
    {
        if (i & 1)                                          // 홀수 번째 단계
        {
            register int pos = idx[(i + 1) >> 1];
            register int index = S + pos - 1;
            while (index)
            {
                --cntTree[index];
                index >>= 1;
            }
            cout << search(1, 1, S, start, pos) << '\n';
        }
        else                                                // 짝수 번째 단계
        {
            register int pos = idx[N - (i >> 1) + 1];
            register int index = S + pos - 1;
            while (index)
            {
                --cntTree[index];
                index >>= 1;
            }
            cout << search(1, 1, S, pos, end) << '\n';
        }
    }

    return 0;
}
