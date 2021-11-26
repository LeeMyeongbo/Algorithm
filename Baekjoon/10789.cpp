#include <iostream>
#include <queue>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

struct Node {
	int r, c, move, index;		// move : 입력 횟수, index : 현재 입력하려는 텍스트의 index
};
queue<Node> q;
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };	// 동-서-남-북 순서
int r, c, visited[10001][50][50], ans;
char map[50][51];
string input;
pair<int, int> go[4][50][50];	// 키보드 상의 각 위치에서 동 서 남 북 순서로 움직였을 때 어느 위치로 가게 되는지 저장 (범위 벗어나면 (-1, -1))

int BFS()
{
	q.push({ 0, 0, 0, 0 });
	while (!q.empty()) {
		Node node = q.front();
		q.pop();
		// 텍스트 모두 입력하고 난 뒤에 엔터키에 도달했을 경우
		if (node.index == (int)input.length() && map[node.r][node.c] == '*') {
			if (!ans)
				ans = node.move + 1;
			ans = min(ans, node.move + 1);
			continue;
		}
		// 입력하려는 알파벳의 키에 도달했을 경우 select & 다음 글자 입력해야 하므로 index + 1하고 입력 횟수 갱신, 큐 삽입
		else if (node.index < (int)input.length() && map[node.r][node.c] == input[node.index]) {
			q.push({ node.r, node.c, node.move + 1, node.index + 1 });
			visited[node.index + 1][node.r][node.c] = node.move + 1;
			continue;
		}
		// 동 서 남 북 4방향으로 살피며 갈 수 있는 위치에 대하여 입력 횟수 갱신, 큐 삽입
		for (int d = 0; d < 4; d++) {
			int R = go[d][node.r][node.c].first;
			int C = go[d][node.r][node.c].second;
			if (R != -1 && (!visited[node.index][R][C] || visited[node.index][R][C] > node.move + 1)) {
				q.push({ R, C, node.move + 1, node.index });
				visited[node.index][R][C] = node.move + 1;
			}
		}
	}
	return ans;
}

int main()
{
	FAST;
	cin >> r >> c;
	for (int i = 0; i < r; i++)
		cin >> map[i];
	
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			for (int d = 0; d < 4; d++) {		// 현재 [i][j] 지점에서 동 서 남 북 4방향으로 움직였을 때 어느 위치로 가게 되는지를 저장
				int R = i + dr[d];
				int C = j + dc[d];
				while (1) {
					if (R < 0 || R >= r || C < 0 || C >= c) {	// 범위 벗어나면 (-1, -1) 저장
						go[d][i][j] = { -1, -1 };
						break;
					}
					else if (map[R][C] != map[i][j]) {			// 현재 키의 알파벳과 다른 위치에 도달하면 그 위치가 도착 지점
						go[d][i][j] = { R, C };
						break;
					}
					R += dr[d], C += dc[d];
				}
			}
		}
	}
	cin >> input;
	cout << BFS();

	return 0;
}