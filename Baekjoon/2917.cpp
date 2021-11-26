#include <iostream>
#include <queue>
using namespace std;

struct Node {
	int r, c, dis;
};
int N, M, start_r, start_c, weights[500][500];						// �����κ��� �ּ� �Ÿ� �����
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
char map[500][501];
bool visited[500][500];												// ���ͽ�Ʈ�� �� �湮 üũ��
queue<Node> q;

int Dij()
{
	int tmp = 10000, ans = 0;
	priority_queue<pair<int, pair<int, int>>> pq;					// (�������� �ּ� �Ÿ�, (��, ��))�� ����
	pq.push({ weights[start_r][start_c], {start_r, start_c} });		// V�κ��� �����ؼ�
	visited[start_r][start_c] = true;

	while (!pq.empty()) {											// �������� �Ÿ��� �ִ��� ���� �켱���� pop�ϸ� ���ͽ�Ʈ��
		int dis = pq.top().first;
		pair<int, int> cur = pq.top().second;
		pq.pop();

		tmp = tmp > dis ? dis : tmp;								// ��� �󿡼� �Ÿ� �ּڰ� ����
		if (map[cur.first][cur.second] == 'J') {
			ans = ans < tmp ? tmp : ans;							// ��ǥ ���� J�� �������� �� �ּڰ��� �ִ� ����
			continue;
		}

		for (int d = 0; d < 4; d++) {
			int R = cur.first + dr[d];
			int C = cur.second + dc[d];
			if (R >= 0 && R < N && C >= 0 && C < M && !visited[R][C]) {
				visited[R][C] = true;
				pq.push({ weights[R][C], {R, C} });
			}
		}
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		cin >> map[i];
		fill(weights[i], weights[i] + M, -1);
		for (int j = 0; j < M; j++) {
			if (map[i][j] == '+') {
				q.push({ i, j, 0 });			// �ϴ� ������ ��� ť�� ����
				weights[i][j] = 0;
			}
			else if (map[i][j] == 'V')
				start_r = i, start_c = j;
		}
	}
	while (!q.empty()) {						// �� �����κ��� �����ؼ� bfs�� �� �� �������� �ּ� �Ÿ� ������
		Node node = q.front();
		q.pop();

		for (int d = 0; d < 4; d++) {
			int R = node.r + dr[d];
			int C = node.c + dc[d];
			if (R >= 0 && R < N && C >= 0 && C < M && (weights[R][C] == -1 || weights[R][C] > node.dis + 1)) {
				weights[R][C] = node.dis + 1;
				q.push({ R, C, weights[R][C] });
			}
		}
	}
	cout << Dij();
	return 0;
}