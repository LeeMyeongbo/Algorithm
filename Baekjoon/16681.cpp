#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define MAX 5000000000000
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, D, E, a, b, n, h[100001];
long long house[100001], korea[100001];		// house : 집(1)에서, korea : 고려대(N)에서 출발하여 각 정점까지의 최단 거리
priority_queue<pair<long long, int>> q;		// 항상 자료형 맞춰주기 (최단 거리가 int형 범위 넘어설 수도 있으므로 그거 감안해서...)
vector<pair<int, int>> graph[100001];

void dijkstra(int start, long long di[])
{
	fill(di, di + N + 1, MAX);
	di[start] = 0;
	q.push({ 0, start });

	while (!q.empty()) {
		int cur = q.top().second;
		long long sum = -q.top().first;
		q.pop();

		if (sum > di[cur])					// 힙에 저장되어 있던 합이 현재 위치까지의 최단거리보다 크다면 살필 필요 x
			continue;

		for (auto p : graph[cur]) {
			if (di[p.second] > di[cur] + p.first) {
				di[p.second] = di[cur] + p.first;
				q.push({ -di[p.second], p.second });
			}
		}
	}
}

void Solve()
{
	dijkstra(1, house);
	dijkstra(N, korea);
	
	long long Max = -MAX;
	for (int i = 2; i < N; i++)
		if (house[i] < MAX && korea[i] < MAX)		// 집에서 목표지점까지 & 목표지점에서 고려대까지 경로가 존재한다면
			Max = max(Max, (long long)h[i] * E - (house[i] + korea[i]) * D);	// 가치 최댓값 갱신
	if (Max > -MAX)
		cout << Max;
	else
		cout << "Impossible";
}

int main()
{
	FAST;
	cin >> N >> M >> D >> E;
	for (int i = 1; i <= N; i++)
		cin >> h[i];
	for (int i = 0; i < M; i++) {					// 양방향 간선이지만
		cin >> a >> b >> n;
		if (h[a] < h[b])
			graph[a].push_back({ n, b });			// 높이가 더 높은 곳으로만 가는 단방향 간선들로 보고 그래프 형성
		else if (h[a] > h[b])
			graph[b].push_back({ n, a });
	}
	for (int i = 1; i <= N; i++)
		sort(graph[i].begin(), graph[i].end());		// 각 정점들과 연결된 간선들을 가중치 오름차순으로 정렬
	
	Solve();
	return 0;
}