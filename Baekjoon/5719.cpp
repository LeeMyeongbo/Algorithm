#include <iostream>
#include <vector>
#include <queue>
#define MAX 1000000000
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, S, D, U, V, P, di[500];				// di[i] : S에서 i번 정점까지의 최단 거리
vector<pair<int, int>> graph[500], pre[500];	// pre[i] : i번 정점 이전에 거친 정점들을 (가중치, 연결된 정점)로 저장
priority_queue<pair<int, int>> pq;				// (최단 거리, 현 위치)
bool deleted_edge[500][500];					// 만약 정점 i에서 정점 j로 가는 간선이 지워지면 [i][j] = true로 됨

void Dijkstra()
{
	fill(di, di + N, MAX);
	di[S] = 0;
	pq.push({ 0, S });

	while (!pq.empty()) {
		int cur = pq.top().second;
		int sum = -pq.top().first;
		pq.pop();

		if (sum > di[cur] || cur == D)
			continue;

		for (auto p : graph[cur]) {
			if (!deleted_edge[cur][p.second] && di[p.second] >= di[cur] + p.first) {	// 지워진 간선이 아니면서 갈 수 있을 경우
				if (di[p.second] > di[cur] + p.first) {									// 최단 거리 갱신
					di[p.second] = di[cur] + p.first;
					pq.push({ -di[p.second], p.second });
				}
				// 처음 방문하는 정점이거나 이미 저장되어 있는 최단 거리랑 같을 경우엔 그대로 추가
				if (pre[p.second].empty() || pre[p.second][0].first == di[p.second])
					pre[p.second].push_back({ di[p.second], cur });
				// 더 작은 최단 거리로 갱신되면 기존에 저장된 것들은 모두 제거하고 새롭게 갱신된 최단 거리 및 이전 정점 저장
				else if (pre[p.second][0].first > di[p.second]) {
					pre[p.second].clear();
					pre[p.second].push_back({ di[p.second], cur });
				}
			}
		}
	}
}

void Delete_Edges(int now)
{
	for (auto e : pre[now]) {
		if (!deleted_edge[e.second][now]) {			// 중복 방문 방지!! (항상 중요! 간과하지 말기)
			deleted_edge[e.second][now] = true;
			Delete_Edges(e.second);
		}
	}
}

int Solve()
{
	Dijkstra();					// 출발지에서부터 최단 경로 모두 구하고
	if (di[D] == MAX)
		return -1;

	Delete_Edges(D);			// 최단 경로들 모두 지워준다

	for (int i = 0; i < N; i++)
		pre[i].clear();

	Dijkstra();					// 그리고 지운 간선들 제외하고 나머지 간선들로 다시 한 번 최단 경로 구함
	if (di[D] == MAX)
		return -1;
	return di[D];
}

int main()
{
	FAST;
	while (1) {
		cin >> N >> M;
		if (!N && !M)
			return 0;

		cin >> S >> D;
		for (int i = 0; i < M; i++) {
			cin >> U >> V >> P;
			graph[U].push_back({ P, V });
		}
		cout << Solve() << "\n";
		for (int i = 0; i < N; i++) {
			graph[i].clear();
			pre[i].clear();
		}
		for (int i = 0; i < N; i++)
			fill(deleted_edge[i], deleted_edge[i] + N, false);
	}
}