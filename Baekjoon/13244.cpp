#include <iostream>
#include <queue>
#include <cstring>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int T, N, M, A, B;
bool graph[1001][1001], visited[1001];
queue<int> q;

bool is_connected()			// BFS로 모든 정점을 방문 가능한지 살핌
{
	q.push(1);
	visited[1] = true;

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (int i = 1; i <= N; i++) {
			if (graph[cur][i] && !visited[i]) {
				q.push(i);
				visited[i] = true;
			}
		}
	}
	for (int i = 1; i <= N; i++)
		if (!visited[i])
			return false;
	return true;
}

int main()
{
	FAST;
	cin >> T;
	for (int t = 0; t < T; t++) {
		cin >> N >> M;
		for (int e = 0; e < M; e++) {
			cin >> A >> B;
			graph[A][B] = graph[B][A] = true;
		}
		if (M != N - 1)				// 간선 개수 = 정점 개수 - 1이 아니면 무조건 그래프임
			cout << "graph\n";
		else {
			if (is_connected())		// 모든 정점이 서로 연결되어 있으면 트리, 아니면 그래프
				cout << "tree\n";
			else
				cout << "graph\n";
		}
		memset(graph, false, sizeof(graph));
		memset(visited, false, sizeof(visited));
	}
	return 0;
}