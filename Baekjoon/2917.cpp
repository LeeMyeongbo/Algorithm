#include <iostream>
#include <queue>
using namespace std;

struct Node {
	int r, c, dis;
};
int N, M, start_r, start_c, weights[500][500];						// 나무로부터 최소 거리 저장용
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
char map[500][501];
bool visited[500][500];												// 다익스트라 시 방문 체크용
queue<Node> q;

int Dij()
{
	int tmp = 10000, ans = 0;
	priority_queue<pair<int, pair<int, int>>> pq;					// (나무와의 최소 거리, (행, 열))로 저장
	pq.push({ weights[start_r][start_c], {start_r, start_c} });		// V로부터 시작해서
	visited[start_r][start_c] = true;

	while (!pq.empty()) {											// 나무와의 거리가 최대인 것을 우선으로 pop하며 다익스트라
		int dis = pq.top().first;
		pair<int, int> cur = pq.top().second;
		pq.pop();

		tmp = tmp > dis ? dis : tmp;								// 경로 상에서 거리 최솟값 갱신
		if (map[cur.first][cur.second] == 'J') {
			ans = ans < tmp ? tmp : ans;							// 목표 지점 J에 도달했을 때 최솟값의 최댓값 갱신
			continue;
		}

		for (int d = 0; d < 4; d++) {
			int R = cur.first + dr[d];
			int C = cur.second + dc[d];
			if (R >= 0 && R < N && C >= 0 && C < M && !visited[R][C]) {
				visited[R][C] = true;
				pq.push({ weights[R][C], {R, C} });
			}
		}
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		cin >> map[i];
		fill(weights[i], weights[i] + M, -1);
		for (int j = 0; j < M; j++) {
			if (map[i][j] == '+') {
				q.push({ i, j, 0 });			// 일단 나무들 모두 큐에 저장
				weights[i][j] = 0;
			}
			else if (map[i][j] == 'V')
				start_r = i, start_c = j;
		}
	}
	while (!q.empty()) {						// 각 나무로부터 시작해서 bfs로 맵 각 지점까지 최소 거리 저장함
		Node node = q.front();
		q.pop();

		for (int d = 0; d < 4; d++) {
			int R = node.r + dr[d];
			int C = node.c + dc[d];
			if (R >= 0 && R < N && C >= 0 && C < M && (weights[R][C] == -1 || weights[R][C] > node.dis + 1)) {
				weights[R][C] = node.dis + 1;
				q.push({ R, C, weights[R][C] });
			}
		}
	}
	cout << Dij();
	return 0;
}