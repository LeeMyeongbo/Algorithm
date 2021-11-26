#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
using namespace std;

struct Node {
	int r, c, passed, broken;
};
int N, M, K, dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
char map[1000][1001];
bool visited[11][1000][1000];		// K�� 0���� 10���� �� 11�� �����ϹǷ� [11][1000][1000]���� �־� ��!! (�Ǽ�)
queue<Node> q;

int BFS()
{
	q.push({ 0, 0, 1, 0 });
	visited[0][0][0] = true;

	while (!q.empty()) {
		Node node = q.front();
		q.pop();

		if (node.r == N - 1 && node.c == M - 1)
			return node.passed;

		for (int d = 0; d < 4; d++) {
			int R = node.r + dr[d];
			int C = node.c + dc[d];
			if (R >= 0 && R < N && C >= 0 && C < M) {
				if (map[R][C] == '0' && !visited[node.broken][R][C]) {
					q.push({ R, C, node.passed + 1, node.broken });
					visited[node.broken][R][C] = true;
				}
				else if (map[R][C] == '1' && node.broken + 1 <= K && !visited[node.broken + 1][R][C]) {
					q.push({ R, C, node.passed + 1, node.broken + 1 });
					visited[node.broken + 1][R][C] = true;
				}
			}
		}
	}
	return -1;
}

int main()
{
	if (!scanf("%d %d %d", &N, &M, &K))
		return 1;
	
	for (int i = 0; i < N; i++)
		if (!scanf("%s", map[i]))
			return 1;
	printf("%d", BFS());
	return 0;
}