#include <iostream>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, map[5][5], ans;
const int dr[] = { 0, 1, 0, -1 }, dc[] = { 1, 0, -1, 0 };	// 동 남 서 북
bool visited[5][5];

void dfs(int r, int c, int sum) {		// r : 부메랑 중앙부분의 행, c : 중앙부분 열
	if (r == N) {
		ans = max(ans, sum);
		return;
	}
	else if (c == M)
		dfs(r + 1, 0, sum);
	else {
		for (int d = 0; d < 4; d++) {	// 현재 [r][c] 영역을 부메랑 중앙부분으로 삼을 경우
			if (visited[r][c])
				continue;
			int wing1_r = r + dr[d];
			int wing1_c = c + dc[d];
			int wing2_r = r + dr[(d + 1) % 4];
			int wing2_c = c + dc[(d + 1) % 4];
			if (wing1_r >= 0 && wing1_r < N && wing1_c >= 0 && wing1_c < M && wing2_r >= 0 && wing2_r < N && wing2_c >= 0 && wing2_c < M) {
				if (!visited[wing1_r][wing1_c] && !visited[wing2_r][wing2_c]) {
					visited[r][c] = visited[wing1_r][wing1_c] = visited[wing2_r][wing2_c] = true;
					dfs(r, c + 1, sum + 2 * map[r][c] + map[wing1_r][wing1_c] + map[wing2_r][wing2_c]);
					visited[r][c] = visited[wing1_r][wing1_c] = visited[wing2_r][wing2_c] = false;
				}
			}
		}
		dfs(r, c + 1, sum);				// 현재 [r][c] 영역을 부메랑 중앙부분으로 삼지 않을 경우
	}
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> map[i][j];

	dfs(0, 0, 0);
	cout << ans;
	return 0;
}