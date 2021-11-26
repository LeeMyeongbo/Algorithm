#include <iostream>
#include <vector>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, v1, v2;
vector<int> graph[2000];
bool visited[2000], complete;

bool dfs(int cur, int depth)
{
	visited[cur] = true;
	if (depth == 4)
		return true;
	for (int i : graph[cur])
		if (!visited[i] && dfs(i, depth + 1))
			return true;
	visited[cur] = false;		// 탐색하고 다시 재귀 빠져나올 때 방문을 풀어줘야 함 (같은 정점 탐색해서 깊이가 4가 될 수도 있으므로)
	return false;				// 깊이가 4가 되면 무조건 종료하므로 중복을 허락해도 됨 (더군다나 정점 수도 최대 2000 이므로)
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int e = 0; e < M; e++) {
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}
	for (int i = 0; i < N; i++) {
		if (dfs(i, 0)) {
			complete = true;
			break;
		}
	}
	if (complete)
		cout << 1;
	else
		cout << 0;
	return 0;
}