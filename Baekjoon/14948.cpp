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
bool visited[2][100][100];			// [0][r][c] : 장비 사용 x, [1][r][c] : 장비 사용 o

bool bfs(int M)						// 레벨이 M이하인 곳은 모두 방문
{
	if (map[0][0] > M)				// 시작 위치부터 M보다 크면 아예 출발을 못함
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
				else if (map[R][C] > M && !node.depth) {	// 레벨이 M보다 높은 곳을 발견하고 장비를 아직 안 쓴 경우
					R += dr[d], C += dc[d];
					if (R >= 0 && R < n && C >= 0 && C < m && !visited[1][R][C] && map[R][C] <= M) { // 뛰어넘어 도착한 곳이 레벨 M이하라면
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
		if (bfs(mid)) {				// mid 이하의 레벨만 거치고도 (n-1, m-1)에 도달 가능할 경우
			ans = mid;
			Right = mid - 1;		// 현재 mid값 저장하고 더 작은 범위로 줄임
		}
		else						// 그렇지 않다면
			Left = mid + 1;			// 더 큰 범위로 줄임
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