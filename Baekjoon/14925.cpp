#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
using namespace std;

int M, N, map[1000][1000], dp[1000][1000], L = 0;

int main()
{
	if (!scanf("%d %d", &M, &N))
		return 1;

	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			if (!scanf("%d", &map[i][j]))
				return 1;

	for (int i = 0; i < N; i++) {
		dp[0][i] = map[0][i] ? 0 : 1;
		if (!map[0][i])
			L = 1;
	}
	for (int i = 0; i < M; i++) {
		dp[i][0] = map[i][0] ? 0 : 1;
		if (!map[i][0])
			L = 1;
	}

	for (int i = 1; i < M; i++) {
		for (int j = 1; j < N; j++) {
			if (!map[i][j]) {
				dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
				L = max(L, dp[i][j]);
			}
		}
	}
	printf("%d", L);
	return 0;
}