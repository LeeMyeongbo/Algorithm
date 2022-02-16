#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, v1, v2, edges[3001], ans[3001];
vector<int> graph[3001];

void topological()
{
	queue<int> q;
	for (int i = 1; i <= N; i++)
		if (edges[i] == 1)				// 연결된 간선이 하나인 정점만 저장
			q.push(i);

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (int i : graph[cur]) {
			if (!edges[i])				// 이미 위상정렬이 완료된 점은 skip
				continue;
			edges[cur]--, edges[i]--;

			if (edges[i] == 1)
				q.push(i);
		}
	}
}

void find()
{
	queue<pair<int, int>> q;
	for (int i = 1; i <= N; i++) {
		if (!edges[i])
			continue;

		q.push({ i, 0 });				// 순환선의 각 역으로부터 지선의 각 역까지 거리 구함
		while (!q.empty()) {
			int cur = q.front().first;
			int dis = q.front().second;
			q.pop();

			for (int v : graph[cur]) {
				if (!edges[v] && !ans[v]) {
					ans[v] = dis + 1;
					q.push({ v, dis + 1 });
				}
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
		edges[v1]++, edges[v2]++;
	}
	topological();
	find();

	for (int i = 1; i <= N; i++)
		cout << ans[i] << " ";

	return 0;
}