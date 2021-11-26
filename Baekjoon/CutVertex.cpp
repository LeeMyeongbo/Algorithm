#include <iostream>
#include <vector>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int V, E, v1, v2, num, visited[10001];
vector<int> graph[10001], ans;
bool isCutVertex[10001];

int dfs(int cur, bool Root)
{
	visited[cur] = ++num;
	int order = visited[cur];					// 맨 처음엔 order를 현재 노드의 방문 순서로 초기화
	int child = 0;								// 현 노드의 자식 노드 수

	for (int i : graph[cur]) {
		if (visited[i])							// 이미 방문한 노드의 경우
			order = min(order, visited[i]);		// 가장 방문 순서가 빠른 놈으로 order 갱신
		else {									// 아직 방문한 적 없는 노드라면
			child++;							// 그게 바로 자식 노드
			int pre = dfs(i, false);			// 해당 자식 노드와 연결된 노드들의 방문 순서 중 최솟값을 pre에 저장

			if (!Root && pre >= visited[cur])	// pre값이 현 노드의 방문 순서보다 작지 않다면 현재 정점이 단절점이 됨
				isCutVertex[cur] = true;
			order = min(order, pre);			// order 최솟값 갱신
		}
	}
	if (Root && child >= 2)						// 현 정점이 루트일 경우엔 자식이 둘 이상만 되면 무적권 단절점
		isCutVertex[cur] = true;

	return order;
}

int main()
{
	FAST;
	cin >> V >> E;
	for (int e = 0; e < E; e++) {
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}
	for (int i = 1; i <= V; i++)
		if (!visited[i])
			dfs(i, true);
	
	for (int i = 1; i <= V; i++)
		if (isCutVertex[i])
			ans.push_back(i);

	cout << ans.size() << "\n";
	for (int i : ans)
		cout << i << " ";
	return 0;
}