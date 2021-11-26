#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int V, E, K, u, graph, w, dijkstra[20001];
vector<pair<int, int>> graph[20001];	// (가중치, 도착 정점) 형태로 저장
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;	// (가중치 합, 현재 정점)

void Solve()
{
	fill(dijkstra, dijkstra + 20001, -1);
	q.push({ 0, K });
	dijkstra[K] = 0;

	while (!q.empty()) {
		int cur = q.top().second;
		int sum = q.top().first;
		q.pop();

		for (auto p : graph[cur]) {
			if (dijkstra[p.second] == -1 || dijkstra[p.second] > dijkstra[cur] + p.first) {
				dijkstra[p.second] = dijkstra[cur] + p.first;
				q.push({ dijkstra[p.second], p.second });
			}
		}
	}
	for (int i = 1; i <= V; i++) {
		if (dijkstra[i] == -1)
			cout << "INF\n";
		else
			cout << dijkstra[i] << "\n";
	}
}

int main()
{
	FAST;
	cin >> V >> E >> K;
	for (int e = 0; e < E; e++) {
		cin >> u >> graph >> w;
		graph[u].push_back({ w, graph });
	}
	for (int i = 1; i <= V; i++)
		sort(graph[i].begin(), graph[i].end());
	Solve();
	return 0;
}