#include <iostream>
#include <queue>
using namespace std;

queue<pair<int, int>> q;
int N, M, map[100][100], Time, dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };

int BFS()
{
	q.push({ 0, 0 });
	map[0][0] = -1;

	while (1) {
		bool complete = true, chk[100][100] = { false, };
		while (!q.empty()) {
			int r = q.front().first;
			int c = q.front().second;
			q.pop();

			for (int d = 0; d < 4; d++) {
				int R = r + dr[d];
				int C = c + dc[d];
				if (R >= 0 && R < N && C >= 0 && C < M && !map[R][C]) {
					q.push({ R, C });
					map[R][C] = -1;
				}
			}
		}
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				if (map[r][c] != -1)
					complete = false;
				if (map[r][c] != 1)
					continue;
				int melting = 0;
				for (int d = 0; d < 4; d++) {
					int R = r + dr[d];
					int C = c + dc[d];
					if (map[R][C] == -1)
						melting++;
				}
				if (melting >= 2)
					chk[r][c] = true;
			}
		}
		if (complete)
			break;
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				if (chk[r][c]) {
					map[r][c] = -1;
					q.push({ r, c });
				}
			}
		}
		Time++;
	}
	return Time;
}

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> map[i][j];
	printf("%d", BFS());

	return 0;
}