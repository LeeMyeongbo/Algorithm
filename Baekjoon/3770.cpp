#include <iostream>
//#include <fstream>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;

int T, N, M, K, n, m;
long long tree[1 << 11];

long long getCnt(int index, int start, int end, int left, int right)
{
    if (left > end || right < start)
        return 0;
    if (left >= start && right <= end)
        return tree[index];
    return getCnt(index * 2, start, end, left, (left + right) / 2) + getCnt(index * 2 + 1, start, end, (left + right) / 2 + 1, right);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int t = 1; t <= T; t++) {
        vector<int> road[1001];
        long long ans = 0;

        cin >> N >> M >> K;
        int S = 1 << (int)ceil(log2(M + 1));

        while (K--) {
            cin >> n >> m;
            road[n].emplace_back(m);
        }

        for (int i = 1; i <= N; i++) {
            for (int& r : road[i])
                ans += getCnt(1, r + 1, S - 1, 0, S - 1);
            
            for (int& r : road[i]) {
                int idx = S + r;
                while (idx) {
                    tree[idx]++;
                    idx /= 2;
                }
            }
        }
        cout << "Test case " << t << ": " << ans << '\n';
        memset(tree, 0, sizeof(tree));
    }

    return 0;
}
