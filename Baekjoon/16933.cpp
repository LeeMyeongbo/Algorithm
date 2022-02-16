#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
using namespace std;				// 이 문제 잘 보기!

struct Node {
	int R, C, sum, broken;
	bool is_day;					// true라면 낮, false라면 밤
};
int N, M, K;
char map[1001][1001];
bool visited[11][1000][1000];		// 부순 벽 개수에 따라 방문 체크 따로 할 수 있도록 하기! (0부터 10까지므로 11을 써야 함!)
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
queue<Node> q;

int Solve()
{
	q.push({ 0, 0, 1, 0, true });	// 맨 처음엔 [0][0]에서 방문한 칸 개수 1, 부순 벽 개수 0, 낮인 상태로 출발
	visited[0][0][0] = true;
	while (!q.empty()) {
		Node node = q.front();
		q.pop();

		if (node.R == N - 1 && node.C == M - 1)									// 목적지에 도달하면 바로 최단 경로 리턴
			return node.sum;
		for (int i = 0; i < 4; i++) {											// 동서남북으로 움직이며 체크
			int R = node.R + dr[i];
			int C = node.C + dc[i];
			if (R >= 0 && R < N && C >= 0 && C < M) {							// 이동할 곳이 맵 범위 내에 있을 경우
				if (map[R][C] == '0' && !visited[node.broken][R][C]) {			// 이동할 곳이 방문한 적 없는 빈칸일 경우
					visited[node.broken][R][C] = true;							// broken은 그대로, 방문한 칸 개수 + 1, 낮밤전환
					q.push({ R, C, node.sum + 1, node.broken, !node.is_day });
				}
				// 이동할 곳이 방문한 적 없는 벽이면서 아직 부술 수 있는 횟수가 남아있는 경우
				else if (map[R][C] == '1' && node.broken + 1 <= K && !visited[node.broken + 1][R][C]) {
					if (node.is_day) {								// 낮이면 broken에 +1하고 
						visited[node.broken + 1][R][C] = true;
						q.push({ R, C, node.sum + 1, node.broken + 1, !node.is_day });
					}
					else											// 밤이라면 부술 수 없으므로 이동 x,방문한 칸 개수만 +1, 낮밤전환
						q.push({ node.R, node.C, node.sum + 1, node.broken, !node.is_day });
				}
			}
		}
	}
	return -1;
}

int main()
{
	if (!scanf("%d %d %d", &N, &M, &K))
		return 1;
	for (int i = 0; i < N; i++)
		if (!scanf("%s", map[i]))
			return 1;
	printf("%d\n", Solve());
	return 0;
}