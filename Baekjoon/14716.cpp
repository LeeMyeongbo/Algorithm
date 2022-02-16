#include <iostream>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int M, N, map[250][250], dr[] = { -1, -1, 0, 1, 1, 1, 0, -1 }, dc[] = { 0, 1, 1, 1, 0, -1, -1, -1 }, word;
bool visited[250][250];
queue<pair<int, int>> q;

int BFS()
{
	for (int r = 0; r < M; r++) {
		for (int c = 0; c < N; c++) {
			if (visited[r][c] || !map[r][c])
				continue;
			q.push({ r, c });
			visited[r][c] = true;

			while (!q.empty()) {
				int cur_r = q.front().first;
				int cur_c = q.front().second;
				q.pop();

				for (int d = 0; d < 8; d++) {
					int R = cur_r + dr[d];
					int C = cur_c + dc[d];
					if (R >= 0 && R < M && C >= 0 && C < N && !visited[R][C] && map[R][C]) {
						q.push({ R, C });
						visited[R][C] = true;
					}
				}
			}
			word++;
		}
	}
	return word;
}

int main()
{
	FAST;
	cin >> M >> N;
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];

	cout << BFS();
	return 0;
}