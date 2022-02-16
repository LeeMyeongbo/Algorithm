#include <iostream>
#include <queue>
using namespace std;

int R, C, Sr, Sc, Dr, Dc, visited[50][50];
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
char map[50][51];
struct Node {
	int r, c, time;
	bool water;
};
queue<Node> q;

/*	BFS 단계
	1. 큐에서 꺼냄
	2. 목적지인지 확인
	3. 연결된 곳 순회
		4. 각 연결된 곳 갈 수 있는지 확인
			5. 체크인
			6. 큐에 넣음
*/

void BFS()
{
	q.push({ Sr, Sc, 0, false });
	while (!q.empty()) {
		// 1. 큐에서 꺼냄
		Node node = q.front();
		q.pop();

		// 2. 목적지인지 확인
		if (!node.water && node.r == Dr && node.c == Dc)
			break;

		// 3. 연결된 곳 순회
		for (int d = 0; d < 4; d++) {
			int r = node.r + dr[d];
			int c = node.c + dc[d];

			// 4. 각 연결된 곳 갈 수 있는지 확인
			if (r >= 0 && r < R && c >= 0 && c < C && !visited[r][c]) {
				if (node.water && map[r][c] == '.') {								// 물이 이동할 경우
					// 5. 체크인
					visited[r][c] = node.time + 1;
					map[r][c] = '*';
					// 6. 큐에 넣음
					q.push({ r, c, node.time + 1, true });
				}
				else if (!node.water && (map[r][c] == '.' || map[r][c] == 'D')) {	// 고슴도치가 이동할 경우
					// 5. 체크인
					visited[r][c] = node.time + 1;
					// 6. 큐에 넣음
					q.push({ r, c, node.time + 1, false });
				}
			}
		}
	}
}

int main()
{
	cin >> R >> C;
	for (int r = 0; r < R; r++)
	{
		cin >> map[r];
		for (int c = 0; c < C; c++) {
			if (map[r][c] == 'S')
				Sr = r, Sc = c, map[r][c] = '.';
			else if (map[r][c] == 'D')
				Dr = r, Dc = c;
			else if (map[r][c] == '*')
				q.push({ r, c, 0, true });
		}
	}

	BFS();
	if (visited[Dr][Dc])
		cout << visited[Dr][Dc];
	else
		cout << "KAKTUS";

	return 0;
}