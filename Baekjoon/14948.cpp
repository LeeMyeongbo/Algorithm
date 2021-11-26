#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

struct Node {
	int depth, r, c;
};
int n, m, map[100][100], Left = 1000000000, Right;
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
bool visited[2][100][100];			// [0][r][c] : ��� ��� x, [1][r][c] : ��� ��� o

bool bfs(int M)						// ������ M������ ���� ��� �湮
{
	if (map[0][0] > M)				// ���� ��ġ���� M���� ũ�� �ƿ� ����� ����
		return false;

	queue<Node> q;
	q.push({ 0, 0, 0 });
	visited[0][0][0] = true;

	while (!q.empty()) {
		Node node = q.front();
		q.pop();

		if (node.r == n - 1 && node.c == m - 1)
			return true;

		for (int d = 0; d < 4; d++) {
			int R = node.r + dr[d];
			int C = node.c + dc[d];
			if (R >= 0 && R < n && C >= 0 && C < m) {
				if (!visited[node.depth][R][C] && map[R][C] <= M) {
					q.push({ node.depth, R, C });
					visited[node.depth][R][C] = true;
				}
				else if (map[R][C] > M && !node.depth) {	// ������ M���� ���� ���� �߰��ϰ� ��� ���� �� �� ���
					R += dr[d], C += dc[d];
					if (R >= 0 && R < n && C >= 0 && C < m && !visited[1][R][C] && map[R][C] <= M) { // �پ�Ѿ� ������ ���� ���� M���϶��
						q.push({ 1, R, C });
						visited[1][R][C] = true;
					}
				}
			}
		}
	}
	return false;
}

int Solve()
{
	int ans = 0;
	while (Left <= Right) {
		int mid = (Left + Right) / 2;
		if (bfs(mid)) {				// mid ������ ������ ��ġ�� (n-1, m-1)�� ���� ������ ���
			ans = mid;
			Right = mid - 1;		// ���� mid�� �����ϰ� �� ���� ������ ����
		}
		else						// �׷��� �ʴٸ�
			Left = mid + 1;			// �� ū ������ ����
		memset(visited, false, sizeof(visited));
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			Left = min(Left, map[i][j]);
			Right = max(Right, map[i][j]);
		}

	cout << Solve();
	return 0;
}