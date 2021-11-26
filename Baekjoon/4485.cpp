#include <iostream>
#include <queue>
#include <cstring>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, Test, map[125][125], dijkstra[125][125], dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

int Solve()
{
	memset(dijkstra, -1, sizeof(dijkstra));
	q.push({ 0, 0 });
	dijkstra[0][0] = map[0][0];

	while (!q.empty()) {
		int r = q.top().first;
		int c = q.top().second;
		q.pop();

		for (int d = 0; d < 4; d++) {
			int R = r + dr[d];
			int C = c + dc[d];
			if (R >= 0 && R < N && C >= 0 && C < N && (dijkstra[R][C] == -1 || dijkstra[R][C] > dijkstra[r][c] + map[R][C])) {
				dijkstra[R][C] = dijkstra[r][c] + map[R][C];
				q.push({ R, C });
			}
		}
	}
	return dijkstra[N - 1][N - 1];
}

int main()
{
	FAST;
	while (1) {
		cin >> N;
		if (!N)
			return 0;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> map[i][j];
		cout << "Problem " << ++Test << ": " << Solve() << "\n";
	}
}