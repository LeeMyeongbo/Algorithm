#include <iostream>
using namespace std;

int T = 1, N, M, ans = -1;
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
char map[31][31];

void DFS(int r, int c, int move)		// ���� ���� ��ġ�� ��, ��, ������ Ƚ��
{
	bool Move = false;
	for (int d = 0; d < 4; d++) {		// �� �� �� �� 4���� ���ǰ� ������ �� ������ �ش� �������� �ִ��� ������
		int R = r, C = c, n = 0;		// n : ������ Ƚ�� (���߿� �ٽ� �ǵ��ư� �� �ʿ�)
		while (R + dr[d] >= 0 && R + dr[d] < N && C + dc[d] >= 0 && C + dc[d] < M && map[R + dr[d]][C + dc[d]] == '.') {
			Move = true;
			R += dr[d], C += dc[d];
			map[R][C] = 'x';
			n++;
		}
		if (n > 0)
			DFS(R, C, move + 1);		// ���� �������� �� �� �̻� ���������� ���� ��
		for (int i = 0; i < n; i++) {	// ������ ��ŭ �ٽ� �ǵ��ư�
			map[R][C] = '.';
			R -= dr[d], C -= dc[d];
		}
	}
	if (!Move) {				// ���� ��ġ���� 4���� ��� ���� �������� �ʾ��� ��� => �� �̻� ������ �� ������ �� ĭ ��� �湮���� ŷ�ɼ� ����
		bool All = true;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				if (map[i][j] == '.')
					All = false;
		if (All && (ans == -1 || ans > move))		// ������ ��� �湮�߰� �ּڰ� ���� �����ϸ� ����
			ans = move;
	}
}

int main()
{
	while (1) {
		cin >> N >> M;
		if (cin.eof())
			return 0;
		for (int i = 0; i < N; i++)
			cin >> map[i];
		for (int r = 0; r < N; r++) {
			for(int c = 0; c < M; c++)
				if (map[r][c] == '.') {
					map[r][c] = 'x';
					DFS(r, c, 0);
					map[r][c] = '.';
				}
		}
		printf("Case %d: %d\n", T++, ans);
		ans = -1;
	}
}