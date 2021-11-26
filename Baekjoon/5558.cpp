#include <iostream>
#include <queue>
using namespace std;

int H, W, N, dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
char map[1001][1001];				// char �迭�� �׻� �� �ڸ� �� �÷��� �����ϴ� �� ���!
bool visited[11][1001][1001];
struct Mouse {
	int r, c, hp, time;
};
queue<Mouse> q;

int BFS()
{
	while (!q.empty()) {
		Mouse m = q.front();
		q.pop();

		if (m.hp == N + 1)			// ��� ġ� �Ծ��� ��� ����
			return m.time;

		for (int d = 0; d < 4; d++) {
			int R = m.r + dr[d];
			int C = m.c + dc[d];
			if (R >= 0 && R < H && C >= 0 && C < W && map[R][C] != 'X') {
				if (map[R][C] - '0' == m.hp && !visited[m.hp + 1][R][C]) {		// ���� �� �ִ� ġ� ����
					q.push({ R, C, m.hp + 1, m.time + 1 });
					visited[m.hp + 1][R][C] = true;
				}
				else if((map[R][C] == '.' || map[R][C] - '0' != m.hp) && !visited[m.hp][R][C]) {	// �� ĭ �Ǵ� ���� �� �Դ� ġ�� ����
					q.push({ R, C, m.hp, m.time + 1 });
					visited[m.hp][R][C] = true;
				}
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> H >> W >> N;
	for (int i = 0; i < H; i++) {
		cin >> map[i];
		for (int j = 0; j < W; j++) {
			if (map[i][j] == 'S') {
				q.push({ i, j, 1, 0 });
				visited[1][i][j] = true;
				map[i][j] = '.';
			}
		}
	}

	cout << BFS();
	return 0;
}