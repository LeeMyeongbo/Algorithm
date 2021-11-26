#include <iostream>
#include <queue>
#include <vector>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, v1, v2, edge[32001];		// edge[i] : i번 정점의 진입 간선 수
vector<int> graph[32001];
priority_queue<int, vector<int>, greater<int>> q;		// 최소 힙 (되도록 쉬운 문제부터 풀어야 하므로)

void Solve()
{
	for (int i = 1; i <= N; i++)
		if (!edge[i])
			q.push(i);

	while (!q.empty()) {
		int cur = q.top();
		q.pop();

		cout << cur << " ";
		for (int i : graph[cur]) {
			edge[i]--;					// 현 정점(cur)에서의 진출 간선들 모두 제거
			if (!edge[i])				// 정점 i로의 진입 간선들이 모두 제거되면 힙에 i 저장
				q.push(i);
		}
	}
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
		edge[v2]++;
	}

	Solve();
	return 0;
}