#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int N, M, S, i, j;
long long tree[1 << 12], ans;
vector<int> graph[2001];

long long getSum(int index, int start, int end, int left, int right)
{
    if (left > end || right < start)
        return 0;
    if (left >= start && right <= end)
        return tree[index];
    return getSum(index * 2, start, end, left, (left + right) / 2) + getSum(index * 2 + 1, start, end, (left + right) / 2 + 1, right);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N >> M;
    S = 1 << (int)ceil(log2(N + 1));

    while (M--) {
        cin >> i >> j;
        graph[i].push_back(j);
    }
    for (int i = 1; i <= N; i++) {
        for (int j : graph[i])
            ans += getSum(1, j + 1, N, 0, S - 1);
        for (int j : graph[i]) {
            int idx = S + j;
            while (idx) {
                tree[idx]++;
                idx /= 2;
            }
        }
    }

    cout << ans;
    return 0;
}
