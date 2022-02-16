#include <iostream>
#include <cmath>
#include <queue>
using namespace std;

int N, M, S, dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
char map[50][51];
bool visited[32][50][50];
struct Node {
	int r, c, stuff, move;
};
queue<Node> q;

int BFS()
{
	while (!q.empty()) {
		Node node = q.front();
		q.pop();

		if (map[node.r][node.c] == 'E' && node.stuff == S)
			return node.move;

		for (int d = 0; d < 4; d++) {
			int R = node.r + dr[d];
			int C = node.c + dc[d];
			if (R >= 0 && R < M && C >= 0 && C < N && !visited[node.stuff][R][C] && map[R][C] != '#') {
				if (map[R][C] >= '0' && map[R][C] < '5') {
					int new_stuff = node.stuff | (1 << (map[R][C] - 48));
					q.push({ R, C, new_stuff, node.move + 1 });
					visited[new_stuff][R][C] = true;
				}
				else {
					q.push({ R, C, node.stuff, node.move + 1 });
					visited[node.stuff][R][C] = true;
				}
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> map[i];
		for (int j = 0; j < N; j++) {
			if (map[i][j] == 'S') {				// 원래 내가 있던 곳 '.'으로 처리
				q.push({ i, j, 0 });
				visited[0][i][j] = true;
				map[i][j] = '.';
			}
			else if (map[i][j] == 'X')			// 물건 하나하나 구분해서 저장
				map[i][j] = S++ + 48;
		}
	}
	S = (int)pow(2, S) - 1;

	cout << BFS();
	return 0;
}