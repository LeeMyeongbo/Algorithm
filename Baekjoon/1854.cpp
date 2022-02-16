#include <iostream>
#include <vector>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int n, m, k, a, b, c;
vector<pair<int, int>> graph[1001];
priority_queue<pair<int, int>> pq;			// (합, 현재 정점)으로 저장
priority_queue<int> dest[1001];				// 각 정점마다 1 ~ k번째 최단 거리 저장

void Dijkstra()
{
	pq.push({ 0, 1 });
	dest[1].push(0);

	while (!pq.empty()) {
		int sum = -pq.top().first;
		int cur = pq.top().second;
		pq.pop();

		for (auto& p : graph[cur]) {
			if (dest[p.first].size() < k) {				// 현재 살피고 있는 정점의 힙 크기가 k보다 작으면 그대로 push
				dest[p.first].push(sum + p.second);
				pq.push({ -(sum + p.second), p.first });
			}
			// 크기가 k이고 힙에 저장된 최댓값이 현재까지 계산된 거리 합보다 크다면 그 최댓값 갱신
			else if (dest[p.first].size() == k && sum + p.second < dest[p.first].top()) {
				dest[p.first].pop();
				dest[p.first].push(sum + p.second);
				pq.push({ -(sum + p.second), p.first });
			}
		}
	}
}

int main()
{
	FAST;
	cin >> n >> m >> k;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		graph[a].push_back({ b, c });
	}
	Dijkstra();
	
	for (int i = 1; i <= n; i++) {
		if (dest[i].size() < k)
			cout << "-1\n";
		else
			cout << dest[i].top() << "\n";
	}
	return 0;
}