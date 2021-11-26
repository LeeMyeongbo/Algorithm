#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, start, dest, cost, Start_city, End_city, dijkstra[1001];
vector<pair<int, int>> graph[1001];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

int Solve()
{
	fill(dijkstra, dijkstra + 1001, -1);
	dijkstra[Start_city] = 0;
	q.push({ 0, Start_city });

	while (!q.empty()) {
		int cur = q.top().second;
		q.pop();

		if (cur == End_city)
			continue;
		for (auto p : graph[cur]) {
			if (dijkstra[p.second] == -1 || dijkstra[p.second] > p.first + dijkstra[cur]) {
				dijkstra[p.second] = p.first + dijkstra[cur];
				q.push({ dijkstra[p.second], p.second });
			}
		}
	}
	return dijkstra[End_city];
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> start >> dest >> cost;
		graph[start].push_back({ cost, dest });		// graph[출발지]에 (비용, 도착지) 형태로 저장
	}
	cin >> Start_city >> End_city;
	for (int i = 1; i <= N; i++)
		sort(graph[i].begin(), graph[i].end());

	cout << Solve();
	return 0;
}