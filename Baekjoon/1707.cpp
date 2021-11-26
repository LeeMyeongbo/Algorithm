#include <iostream>
#include <queue>
#include <vector>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int K, V, E, v1, v2, visited[20001];
vector<int> graph[20001];
queue<int> q;

bool Solve()
{
	for (int v = 1; v <= V; v++) {						// 연결 그래프가 아니어도 이분 그래프일 수 있으므로 모든 정점에 대해서 확인!
		if (visited[v])
			continue;
		visited[v] = 1;
		q.push(v);

		while (!q.empty()) {
			int cur = q.front();
			q.pop();

			for (int i : graph[cur]) {
				if (visited[i] == visited[cur])			// 현재 부분 그래프가 이분 그래프가 아니면 현 그래프는 이분 그래프가 아님!
					return false;
				if (!visited[i]) {
					visited[i] = visited[cur] * -1;
					q.push(i);
				}
			}
		}
	}
	return true;		// 모든 부분 그래프(들)이 이분 그래프라면 현재 그래프는 이분 그래프
}

int main()
{
	FAST;
	cin >> K;
	for (int i = 0; i < K; i++) {
		cin >> V >> E;
		for (int e = 0; e < E; e++) {
			cin >> v1 >> v2;
			graph[v1].push_back(v2);
			graph[v2].push_back(v1);
		}
		if (Solve())
			cout << "YES\n";
		else
			cout << "NO\n";

		fill(visited, visited + V + 1, 0);
		for (int v = 1; v <= V; v++)
			graph[v].clear();

		while (!q.empty())
			q.pop();
	}
	return 0;
}