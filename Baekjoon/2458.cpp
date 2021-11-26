#include <iostream>
#include <vector>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, a, b, num[501], ans;
vector<int> graph[501], reversed_graph[501];
bool visited[501];

void dfs(int cur, int init, vector<int> g[]) 
{
	num[init]++;
	visited[cur] = true;
	for (int i : g[cur])
		if (!visited[i])
			dfs(i, init, g);
}

int Solve()
{
	for (int i = 1; i <= N; i++) {
		dfs(i, i, graph);					// 현 정점에서 정방향으로 DFS 실행하며 방문한 정점 수 저장 (키 큰 놈들 수)
		dfs(i, i, reversed_graph);			// 현 정점에서 역방향으로 DFS 실행하며 방문한 정점 수 저장 (키 작은 놈들 수)

		if (num[i] == N + 1)				// 모든 정점 방문했다면(현 정점 제외한 모든 정점들이 키가 크거나 작다는 것이 확실하다면)
			ans++;							// 자신의 키가 몇 번째인지 알 수 있음
		fill(visited, visited + N + 1, false);
	}

	return ans;
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		graph[a].push_back(b);
		reversed_graph[b].push_back(a);
	}

	cout << Solve();
	return 0;
}