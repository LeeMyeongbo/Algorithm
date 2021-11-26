#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int M, N, map[500][500], dp[4][500][500];
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };		// �� �� �� �� ������ �湮
bool visited[4][500][500];

int DFS(int r, int c)
{
	if (r == M - 1 && c == N - 1)			// ���� ������ �Ʒ��� �ٴٸ��� 1 ����
		return 1;

	for (int d = 0; d < 4; d++) {
		int R = r + dr[d];
		int C = c + dc[d];

		if (R >= 0 && R < M && C >= 0 && C < N && !visited[d][R][C] && map[R][C] < map[r][c]) {		// �湮�� �� ���� ��������
			visited[d][R][C] = true;		// �湮 üũ�ϰ�
			dp[d][r][c] += DFS(R, C);		// �� ���� ���� �ش� ���⿡���� ��� �� ����
		}
	}
	return dp[0][r][c] + dp[1][r][c] + dp[2][r][c] + dp[3][r][c];	// �� 4���⿡���� ��� ���� ���� ����
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