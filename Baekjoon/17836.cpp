#include <iostream>
#include <queue>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

struct Node {
	int r, c, move;
};
int N, M, T, map[100][100], dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 }, dest = 10001, gram = 10001, dest2 = 10001;
bool visited[100][100];
queue<Node> q;

int BFS()
{
	q.push({ 0, 0, 0 });
	visited[0][0] = true;

	while (!q.empty()) {
		Node node = q.front();
		q.pop();

		if (node.r == N - 1 && node.c == M - 1) {	// ���ָ� �߰����� ��� dest ���� �� BFS ����
			dest = node.move;
			break;
		}
		else if (map[node.r][node.c] == 2) {		// �׶��� �߰����� ��� dest2 ����
			gram = min(gram, node.move);
			dest2 = gram + N - 1 - node.r + M - 1 - node.c;		// �׶����δ� �� ���Ѿ��� �μ� �� �����ϱ� �ٷ� ��ǥ�� �ִ� �Ÿ� ���
			continue;
		}
		for (int d = 0; d < 4; d++) {
			int R = node.r + dr[d];
			int C = node.c + dc[d];
			if (R >= 0 && R < N && C >= 0 && C < M && !visited[R][C] && map[R][C] != 1) {
				q.push({ R, C, node.move + 1 });
				visited[R][C] = true;
			}
		}
	}
	if (min(dest, dest2) <= T)
		return min(dest, dest2);

	return -1;
}

int main()
{
	FAST;
	cin >> N >> M >> T;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> map[i][j];
	
	int ans = BFS();
	if (ans != -1)
		cout << ans;
	else
		cout << "Fail";

	return 0;
}