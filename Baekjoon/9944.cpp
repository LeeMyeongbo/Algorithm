#include <iostream>
using namespace std;

int T = 1, N, M, ans = -1;
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
char map[31][31];

void DFS(int r, int c, int move)		// 현재 공이 위치한 열, 행, 움직인 횟수
{
	bool Move = false;
	for (int d = 0; d < 4; d++) {		// 동 서 남 북 4방향 살피고 움직일 수 있으면 해당 방향으로 최대한 움직임
		int R = r, C = c, n = 0;		// n : 움직인 횟수 (나중에 다시 되돌아갈 때 필요)
		while (R + dr[d] >= 0 && R + dr[d] < N && C + dc[d] >= 0 && C + dc[d] < M && map[R + dr[d]][C + dc[d]] == '.') {
			Move = true;
			R += dr[d], C += dc[d];
			map[R][C] = 'x';
			n++;
		}
		if (n > 0)
			DFS(R, C, move + 1);		// 현재 방향으로 한 번 이상 움직였으면 깊이 들어감
		for (int i = 0; i < n; i++) {	// 움직인 만큼 다시 되돌아감
			map[R][C] = '.';
			R -= dr[d], C -= dc[d];
		}
	}
	if (!Move) {				// 현재 위치에서 4방향 모두 전혀 움직이지 않았을 경우 => 이 이상 움직일 수 없으며 빈 칸 모두 방문했을 킹능성 존재
		bool All = true;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				if (map[i][j] == '.')
					All = false;
		if (All && (ans == -1 || ans > move))		// 실제로 모두 방문했고 최솟값 갱신 가능하면 갱신
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