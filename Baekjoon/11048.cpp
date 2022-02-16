#include <iostream>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, map[1000][1000], dp[1000][1000];

int Solve()
{
	dp[0][0] = map[0][0];

	for (int c = 1; c < M; c++)
		dp[0][c] = dp[0][c - 1] + map[0][c];
	for (int r = 1; r < N; r++)
		dp[r][0] = dp[r - 1][0] + map[r][0];

	for (int i = 1; i < N; i++)
		for (int j = 1; j < M; j++)
			dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + map[i][j];
	
	return dp[N - 1][M - 1];
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> map[i][j];

	cout << Solve();
	return 0;
}