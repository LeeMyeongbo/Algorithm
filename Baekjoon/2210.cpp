#include <iostream>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int map[5][6], ans, dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
bool numbers[1000000];

void dfs(int r, int c, int move, int num)
{
	if (move == 5) {
		numbers[num] = true;
		return;
	}
	for (int d = 0; d < 4; d++) {
		int R = r + dr[d];
		int C = c + dc[d];
		if (R >= 0 && R < 5 && C >= 0 && C < 5) {
			dfs(R, C, move + 1, num * 10 + map[R][C]);
		}
	}
}

int main()
{
	FAST;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			cin >> map[i][j];

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			dfs(i, j, 0, map[i][j]);

	for (int i = 0; i < 1000000; i++)
		if (numbers[i])
			ans++;

	cout << ans;
	return 0;
}