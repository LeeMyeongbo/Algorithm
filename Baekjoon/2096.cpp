#include <iostream>
#include <algorithm>
using namespace std;

int N, dp[2][3], new_dp[2][3], pos[3];		// dp[0][0~2] : 최대, dp[1][0~2] : 최소

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> pos[0] >> pos[1] >> pos[2];

		new_dp[0][0] = max(dp[0][0], dp[0][1]) + pos[0];
		new_dp[0][1] = max(max(dp[0][0], dp[0][1]), dp[0][2]) + pos[1];
		new_dp[0][2] = max(dp[0][1], dp[0][2]) + pos[2];
		new_dp[1][0] = min(dp[1][0], dp[1][1]) + pos[0];
		new_dp[1][1] = min(min(dp[1][0], dp[1][1]), dp[1][2]) + pos[1];
		new_dp[1][2] = min(dp[1][1], dp[1][2]) + pos[2];

		for (int a = 0; a < 2; a++)
			for (int b = 0; b < 3; b++)
				dp[a][b] = new_dp[a][b];
	}
	cout << max(max(dp[0][0], dp[0][1]), dp[0][2]) << ' ' << min(min(dp[1][0], dp[1][1]), dp[1][2]);

	return 0;
}