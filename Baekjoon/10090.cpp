#include <iostream>
#include <cmath>
using namespace std;

int N, a;
long long tree[1 << 21], ans;

long long getCount(int index, int start, int end, int left, int right)
{
    if (left > end || right < start)
        return 0;
    if (left >= start && right <= end)
        return tree[index];
    return getCount(index * 2, start, end, left, (left + right) / 2) + getCount(index * 2 + 1, start, end, (left + right) / 2 + 1, right);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    int S = 1 << (int)ceil(log2(N + 1));

    for (int i = 0; i < N; i++) {
        cin >> a;
        ans += getCount(1, a + 1, S - 1, 0, S - 1);         // a보다 큰 구간인 [a+1, S-1]에서 몇 개의 숫자가 나왔었는지 헤아림

        int idx = S + a;
        while (idx) {
            tree[idx]++;
            idx /= 2;
        }
    }
    cout << ans;
    return 0;
}
