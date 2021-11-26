#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
using namespace std;		// Ư�� ĭ���� ������ Ƚ���� �ִ��� �ѹ� ���ϸ� ���Ŀ� �Ȱ��� ĭ�� �ٽ� ���� �� �� ������ ���� �ʿ䰡 ������ �̿�(DP)

int N, M, Max_move[4][50][50];		// Max_move : �ش� ĭ�� ���� ���� �ִ��� ������ �� �ִ� Ƚ���� �����ؼ� ����ġ�⿡ Ȱ��!
const int dr[] = { 0, 1, 0, -1 }, dc[] = { 1, 0, -1, 0 };			// �� �� �� �� ������ ������
char map[50][51];
bool visited[4][50][50];			// ����Ŭ�� �����ϴ� �� Ȯ���ϱ� ����

int dfs(int r, int c, int move)
{
	if (r < 0 || r >= N || c < 0 || c >= M || map[r][c] == 'H')		// ������ ����ų� ���ۿ� �ٴٸ��� �ٷ� 0 ����
		return 0;

	for (int d = 0; d < 4; d++) {
		int R = r + dr[d] * (map[r][c] - '0');
		int C = c + dc[d] * (map[r][c] - '0');
		
		if (!visited[d][r][c]) {
			visited[d][r][c] = true;
			if (!Max_move[d][r][c])
				Max_move[d][r][c] = max(Max_move[d][r][c], dfs(R, C, move + 1) + 1);	// ���� ���� ������ �� �ִ� �ִ� Ƚ�� ����
			visited[d][r][c] = false;
		}
		else {						// �̹� �湮�� �� �� �湮�ϸ� ����Ŭ�� ����!
			printf("-1");
			exit(0);
		}
	}
	
	return max(max(Max_move[0][r][c], Max_move[1][r][c]), max(Max_move[2][r][c], Max_move[3][r][c]));	// �� �� �� �� ���� �� �ִ�
}

int main()
{
	if (!scanf("%d %d", &N, &M))
		return 1;
	for (int i = 0; i < N; i++)
		if (!scanf("%s", map + i))
			return 1;
	dfs(0, 0, 0);

	printf("%d", max(max(Max_move[0][0][0], Max_move[1][0][0]), max(Max_move[2][0][0], Max_move[3][0][0])));
	return 0;
}