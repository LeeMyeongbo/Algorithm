#include <iostream>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, map[100][100];
unsigned long long dp[100][100];

int main()
{
	FAST;
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];

	dp[0][0] = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!dp[i][j] || !map[i][j])
				continue;
			if (i + map[i][j] < N)
				dp[i + map[i][j]][j] += dp[i][j];
			if (j + map[i][j] < N)
				dp[i][j + map[i][j]] += dp[i][j];
		}
	}
	cout << dp[N - 1][N - 1];
	return 0;
}