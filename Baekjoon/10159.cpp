#include <iostream>
#include <vector>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, v1, v2, num[101];
vector<int> graph[101], reversed_graph[101];
bool visited[101];

void dfs(int cur, int init, vector<int> g[])
{
	visited[cur] = true;
	num[init]++;
	for (int i : g[cur])
		if (!visited[i])
			dfs(i, init, g);
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
		reversed_graph[v2].push_back(v1);
	}

	for (int i = 1; i <= N; i++) {		// 1번부터 N번 정점까지 정방향, 역방향 dfs 모두 돌리면서 방문한 정점 수를 전체 정점 수에서 뺌
		dfs(i, i, graph);
		dfs(i, i, reversed_graph);

		cout << N - (num[i] - 1) << "\n";
		fill(visited, visited + N + 1, false);
	}

	return 0;
}