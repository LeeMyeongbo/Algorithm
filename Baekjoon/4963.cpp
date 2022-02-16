#include <iostream>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int h, w, map[50][50], dr[] = { -1, -1, 0, 1, 1, 1, 0, -1 }, dc[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
bool visited[50][50];
queue<pair<int, int>> q;

int Solve()
{
	int island = 0;
	for (int i = 0; i < h; i++)
		fill(visited[i], visited[i] + w, false);

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (visited[i][j] || !map[i][j])
				continue;
			q.push({ i, j });
			visited[i][j] = true;

			while (!q.empty()) {
				int r = q.front().first;
				int c = q.front().second;
				q.pop();

				for (int d = 0; d < 8; d++) {
					int R = r + dr[d];
					int C = c + dc[d];
					if (R >= 0 && R < h && C >= 0 && C < w && !visited[R][C] && map[R][C]) {
						visited[R][C] = true;
						q.push({ R, C });
					}
				}
			}
			island++;
		}
	}
	return island;
}

int main()
{
	FAST;
	while (1) {
		cin >> w >> h;
		if (!w && !h)
			return 0;

		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				cin >> map[i][j];

		cout << Solve() << "\n";
	}
	return 0;
}