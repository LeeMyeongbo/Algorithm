#include <iostream>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

struct Node {
	pair<int, int> coin[2];			// ���� 2���� ��ġ
	int move;						// ������ Ƚ��
};
queue<Node> q;
int N, M, c, dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 }, start[2][2];
char map[22][23];
bool visited[22][22][22][22];		// �����ڸ��� �湮üũ�� �̷������ ���� �ɷ� ó�� (�׻� �������� �ͱ��� ����Ѵٸ� ������� �� ĭ�� �÷�����)

int BFS()
{
	Node node;
	node.coin[0] = { start[0][0], start[0][1] }, node.coin[1] = { start[1][0], start[1][1] };
	node.move = 0;
	q.push(node);
	visited[start[0][0]][start[0][1]][start[1][0]][start[1][1]] = true;

	while (!q.empty()) {
		Node node = q.front();
		q.pop();
		// �� �� ���� ��� skip
		if ((node.coin[0].first == 0 || node.coin[0].first == N + 1 || node.coin[0].second == 0 || node.coin[0].second == M + 1) &&
			(node.coin[1].first == 0 || node.coin[1].first == N + 1 || node.coin[1].second == 0 || node.coin[1].second == M + 1))
			continue;
		// ������ Ƚ���� 10���� �Ѿ�� -1 ����
		else if (node.move > 10)
			return -1;
		// �� �� �ϳ��� ���� ��� ������ Ƚ�� ����
		else if (node.coin[0].first == 0 || node.coin[0].first == N + 1 || node.coin[0].second == 0 || node.coin[0].second == M + 1 ||
			node.coin[1].first == 0 || node.coin[1].first == N + 1 || node.coin[1].second == 0 || node.coin[1].second == M + 1)
			return node.move;

		for (int d = 0; d < 4; d++) {
			Node new_node = node;
			for (int c = 0; c < 2; c++) {
				if (map[node.coin[c].first + dr[d]][node.coin[c].second + dc[d]] != '#') {	// �����̷��� ���� ���� �ƴϸ� �̵�
					new_node.coin[c].first += dr[d];
					new_node.coin[c].second += dc[d];
				}
			}
			if (!visited[new_node.coin[0].first][new_node.coin[0].second][new_node.coin[1].first][new_node.coin[1].second]) {
				visited[new_node.coin[0].first][new_node.coin[0].second][new_node.coin[1].first][new_node.coin[1].second] = true;
				new_node.move += 1;
				q.push(new_node);
			}
		}
	}
	return -1;
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'o')
				start[c][0] = i, start[c++][1] = j;
		}
	}
	cout << BFS();
	return 0;
}