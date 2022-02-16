#include <iostream>
using namespace std;

int N, M, dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
char map[50][51];
bool visited[50][50];

void dfs(int cur_r, int cur_c, int pre_r, int pre_c)	// cur_r : 현재 행, cur_c : 현재 열, pre_r : 바로 이전 행, pre_c : 바로 이전 열
{
	visited[cur_r][cur_c] = true;

	for (int d = 0; d < 4; d++) {
		int R = cur_r + dr[d];
		int C = cur_c + dc[d];
		if (R >= 0 && R < N && C >= 0 && C < M && map[cur_r][cur_c] == map[R][C]) {		// 알파벳이 같은 영역으로만 갈 수 있음
			if (!visited[R][C])
				dfs(R, C, cur_r, cur_c);
			else if (visited[R][C] && (R != pre_r || C != pre_c)) {		// 분명히 방문한 지점인데 바로 전에 방문한 점은 아닌 경우 사이클
				cout << "Yes";
				exit(0);
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		cin >> map[i];

	for (int r = 0; r < N; r++)
		for (int c = 0; c < M; c++)
			if (!visited[r][c])
				dfs(r, c, r, c);

	cout << "No";
	return 0;
}