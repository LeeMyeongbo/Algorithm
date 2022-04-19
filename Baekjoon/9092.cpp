#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

int T, n, k, dp[500][500];      // dp[i][j] : i에서 남은 건너뛰기 개수가 j일 때 달려야 하는 최소 거리
pair<int, int> chk[500];

int dfs(int cur, int jump)
{
    int j = 0, tmp = 0;
    while (cur + j  + 1 < n && jump - j >= 0) {     // 현 위치 cur에서 0개, 1개, 2개, ... 건너뛰면서 진행
        int dist = abs(chk[cur].first - chk[cur + j + 1].first) + abs(chk[cur].second - chk[cur + j + 1].second);
        tmp = dp[cur + j + 1][jump - j] ? dp[cur + j + 1][jump - j] + dist : dfs(cur + j + 1, jump - j) + dist;
        
        if (!dp[cur][jump])
            dp[cur][jump] = tmp;
        
        dp[cur][jump] = min(dp[cur][jump], tmp);
        j++;
    }

    return dp[cur][jump];
}

int main(int argc, char** argv)
{
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> n >> k;
        for (int i = 0; i < n; i++)
            cin >> chk[i].first >> chk[i].second;
        
        cout << '#' << test_case << ' ' << dfs(0, k) << '\n';
        memset(dp, 0, sizeof(dp));
	}
	return 0;
}