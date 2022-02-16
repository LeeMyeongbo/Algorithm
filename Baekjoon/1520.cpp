#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int M, N, map[500][500], dp[4][500][500];
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };		// 동 서 남 북 순으로 방문
bool visited[4][500][500];

int DFS(int r, int c)
{
	if (r == M - 1 && c == N - 1)			// 제일 오른쪽 아래에 다다르면 1 리턴
		return 1;

	for (int d = 0; d < 4; d++) {
		int R = r + dr[d];
		int C = c + dc[d];

		if (R >= 0 && R < M && C >= 0 && C < N && !visited[d][R][C] && map[R][C] < map[r][c]) {		// 방문한 적 없는 내리막길
			visited[d][R][C] = true;		// 방문 체크하고
			dp[d][r][c] += DFS(R, C);		// 더 깊이 들어가서 해당 방향에서의 경로 수 더함
		}
	}
	return dp[0][r][c] + dp[1][r][c] + dp[2][r][c] + dp[3][r][c];	// 각 4방향에서의 경로 수의 합을 리턴
}

int main()
{
	if (!scanf("%d %d", &M, &N))
		return 1;
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			if (!scanf("%d", &map[i][j]))
				return 1;
	int ans = DFS(0, 0);
	printf("%d", ans);
	return 0;
}