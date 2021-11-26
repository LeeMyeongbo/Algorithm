#include <iostream>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, map[10][10], ans = 10000;
bool visited[10][10];

void dfs(int r, int c, int n, int cost)
{
	if (n == 3) {
		ans = ans > cost ? cost : ans;
		return;
	}
	else if (r == N - 1)		// ���� ���� ������ ���� ����
		return;
	else if (c == N - 1) {		// ���� ������ ���� ���� ���� ���� 1������ ����
		dfs(r + 1, 1, n, cost);
		return;
	}
	// ���� �ڸ��� ���� ���� �� �ִ� ��� ���� ���� ��ġ Ž�� ����
	else if (!visited[r][c] && !visited[r - 1][c] && !visited[r][c - 1] && !visited[r + 1][c] && !visited[r][c + 1]) {
		visited[r][c] = visited[r - 1][c] = visited[r + 1][c] = visited[r][c - 1] = visited[r][c + 1] = true;
		dfs(r, c + 1, n + 1, cost + map[r][c] + map[r - 1][c] + map[r + 1][c] + map[r][c - 1] + map[r][c + 1]);
		visited[r][c] = visited[r - 1][c] = visited[r + 1][c] = visited[r][c - 1] = visited[r][c + 1] = false;
	}
	// �� ��ġ�� ���� ���� ��츦 Ž�������� ���� ���� ���·� ���� ��ġ Ž���� ����
	dfs(r, c + 1, n, cost);
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];
	
	for (int i = 1; i < N - 1; i++)
		for (int j = 1; j < N - 1; j++)
			dfs(i, j, 0, 0);

	cout << ans;
	return 0;
}