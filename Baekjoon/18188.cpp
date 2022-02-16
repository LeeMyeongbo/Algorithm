#include <iostream>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int H, W, N, start_r, start_c;
char map[20][21], B_C[21][2];

void dfs(int r, int c, int n) {
	static char path[21] = { 0, };
	if (map[r][c] == 'Z') {
		cout << "YES\n";
		for (int i = 0; i < n; i++)
			cout << path[i];
		exit(0);
	}
	if (n == N)
		return;
	for (int i = 0; i < 2; i++) {
		if (B_C[n][i] == 'W' && r - 1 >= 0 && map[r - 1][c] != '@') {
			path[n] = 'W';
			dfs(r - 1, c, n + 1);
			path[n] = 0;
		}
		else if (B_C[n][i] == 'A' && c - 1 >= 0 && map[r][c - 1] != '@') {
			path[n] = 'A';
			dfs(r, c - 1, n + 1);
			path[n] = 0;
		}
		else if (B_C[n][i] == 'S' && r + 1 < H && map[r + 1][c] != '@') {
			path[n] = 'S';
			dfs(r + 1, c, n + 1);
			path[n] = 0;
		}
		else if (B_C[n][i] == 'D' && c + 1 < W && map[r][c + 1] != '@') {
			path[n] = 'D';
			dfs(r, c + 1, n + 1);
			path[n] = 0;
		}
	}
}

int main()
{
	FAST;
	cin >> H >> W;
	for (int i = 0; i < H; i++) {
		cin >> map[i];
		for (int j = 0; j < W; j++) {
			if (map[i][j] == 'D')
				start_r = i, start_c = j;
		}
	}
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> B_C[i][0] >> B_C[i][1];

	dfs(start_r, start_c, 0);
	cout << "NO";
	return 0;
}