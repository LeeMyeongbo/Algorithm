#include <iostream>
#include <queue>
using namespace std;

char map[1000][1001];
int test_case, T, N, M, visited[1000][1000];
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
struct Node {
	int r, c, dist;
};
queue<Node> q;

int BFS()
{
	int ans = 0;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			if (map[r][c] == 'L')
				continue;
			
			for (int d = 0; d < 4; d++) {
				int R = r + dr[d];
				int C = c + dc[d];
				if (R >= 0 && R < N && C >= 0 && C < M && map[R][C] == 'L')		// 육지가 인접한 바다만 모두 큐에 저장
					q.push({ r, c, 0 });
			}
		}
	}
	while (!q.empty()) {					// BFS 돌리면 끝!
		Node node = q.front();
		q.pop();

		for (int d = 0; d < 4; d++) {
			int R = node.r + dr[d];
			int C = node.c + dc[d];
			if (R >= 0 && R < N && C >= 0 && C < M && map[R][C] == 'L' && (!visited[R][C] || visited[R][C] > node.dist + 1)) {
				visited[R][C] = node.dist + 1;
				q.push({ R, C, node.dist + 1 });
			}
		}
	}
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			if (map[r][c] == 'L')
				ans += visited[r][c];
		}
	}
	return ans;
}

int main(int argc, char** argv)
{
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		cin >> N >> M;
		for (int r = 0; r < N; r++)
			cin >> map[r];

		cout << "#" << test_case << " " << BFS() << endl;

		for (int i = 0; i < N; i++)
			fill(visited[i], visited[i] + M, 0);
	}
	return 0;
}