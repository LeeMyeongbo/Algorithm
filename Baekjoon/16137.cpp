#include <iostream>
#include <queue>
using namespace std;

int N, M, map[10][10], visited[10][10], dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 }, Ans = -1;
struct Node {
	int r, c, time;			// 행, 열, 소요 시간
};
queue<Node> q;

int BFS()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j])					// 오작교를 반드시 하나 이상 놓을 수 있다고 했으므로 BFS 적어도 한 번은 무적권 돌림
				continue;

			map[i][j] = M;					// 비어있는 절벽 발견 시 일단 오작교 설치 (절벽 교차하는 곳엔 놓을 수 없지만 뭐 답에는 영향 x)
			for (int i = 0; i < N; i++)
				fill(visited[i], visited[i] + N, -1);	// visited는 일반적인 방문 체크가 아닌 이동 시간의 최솟값을 저장해야 함

			q.push({ 0, 0, 0 });
			visited[0][0] = 0;

			while (!q.empty()) {
				Node node = q.front();
				q.pop();

				if (node.r == N - 1 && node.c == N - 1) {
					if (Ans == -1)
						Ans = visited[node.r][node.c];
					Ans = Ans > visited[node.r][node.c] ? visited[node.r][node.c] : Ans;
					continue;
				}

				for (int d = 0; d < 4; d++) {
					int R = node.r + dr[d];
					int C = node.c + dc[d];
					if (R >= 0 && R < N && C >= 0 && C < N && map[R][C]) {
						if (map[node.r][node.c] > 1 && map[R][C] > 1)			// 오작교를 2번 연속으로 건너는 경우 skip (문제 잘 읽기!)
							continue;
						// 이동과 동시에 건너려는 오작교 주기의 배수이면서 node.time 이상인 자연수 중 최솟값 저장 (일반 땅에도 똑같이 적용됨)
						if (visited[R][C] == -1 || visited[R][C] > node.time + map[R][C] - node.time % map[R][C]) {
							visited[R][C] = node.time + map[R][C] - node.time % map[R][C];
							q.push({ R, C, visited[R][C] });
						}
					}
				}
			}
			map[i][j] = 0;		// BFS 끝나면 설치했던 오작교 다시 제거해줘야 함
		}
	}
	return Ans;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];
	
	cout << BFS();

	return 0;
}