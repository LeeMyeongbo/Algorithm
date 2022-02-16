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
	else if (r == N - 1)		// 가장 밑의 행으로 오면 종료
		return;
	else if (c == N - 1) {		// 가장 오른쪽 열로 오면 다음 행의 1열부터 시작
		dfs(r + 1, 1, n, cost);
		return;
	}
	// 현재 자리에 꽃을 놓을 수 있는 경우 놓고 다음 위치 탐색 ㄱㄱ
	else if (!visited[r][c] && !visited[r - 1][c] && !visited[r][c - 1] && !visited[r + 1][c] && !visited[r][c + 1]) {
		visited[r][c] = visited[r - 1][c] = visited[r + 1][c] = visited[r][c - 1] = visited[r][c + 1] = true;
		dfs(r, c + 1, n + 1, cost + map[r][c] + map[r - 1][c] + map[r + 1][c] + map[r][c - 1] + map[r][c + 1]);
		visited[r][c] = visited[r - 1][c] = visited[r + 1][c] = visited[r][c - 1] = visited[r][c + 1] = false;
	}
	// 현 위치에 꽃을 놓은 경우를 탐색했으면 놓지 않은 상태로 다음 위치 탐색도 ㄱㄱ
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