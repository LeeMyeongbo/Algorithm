#include <iostream>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int n, map[500][500], dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 }, dp[500][500], K;

int DFS(int r, int c)
{
	int ans = 1;
	if (dp[r][c])
		return dp[r][c];
	for (int d = 0; d < 4; d++) {
		int R = r + dr[d];
		int C = c + dc[d];
		if (R >= 0 && R < n && C >= 0 && C < n && map[R][C] > map[r][c])
			ans = max(ans, DFS(R, C) + 1);
	}
	return dp[r][c] = ans;			// dp를 통한 가지치기! (중간중간마다 살 수 있는 최대 일수를 저장해서 중복 탐색 막자)
}

int main()
{
	FAST;
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> map[i][j];
	for(int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (!dp[i][j])
				dp[i][j] = DFS(i, j);
			K = max(K, dp[i][j]);
		}

	cout << K;
	return 0;
}