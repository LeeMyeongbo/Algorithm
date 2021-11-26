#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

int n, m, graph[1001][1001], pre[1001], Start, End, visited_sum[1001];
vector<int> ans;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;		// 우선순위 큐로 합이 가장 낮은 것부터 꺼냄

void Backtrack(int n)										// 도착지로부터 경로 역추적
{
	ans.push_back(n);
	if (n == Start)
		return;
	Backtrack(pre[n]);
}

void Solve()
{
	q.push({ 0, Start });
	visited_sum[Start] = 0;
	while (!q.empty()) {
		int sum = q.top().first;
		int cur = q.top().second;
		q.pop();

		if (cur == End)
			continue;
		for (int i = 1; i <= n; i++)
			if (graph[cur][i] > -1 && (visited_sum[i] == -1 || visited_sum[i] > sum + graph[cur][i])) {
				pre[i] = cur;								// i의 이전 정점이 cur이다는 의미
				visited_sum[i] = sum + graph[cur][i];		// 최소 합계 갱신
				q.push({ visited_sum[i], i });
			}
	}
	printf("%d\n", visited_sum[End]);
	Backtrack(End);
	printf("%d\n", ans.size());
	while (!ans.empty()) {
		printf("%d ", ans.back());
		ans.pop_back();
	}
}

int main()
{
	int start, end, cost;
	memset(graph, -1, sizeof(graph));
	memset(visited_sum, -1, sizeof(visited_sum));

	if (!scanf("%d %d", &n, &m))
		return 1;
	for (int i = 0; i < m; i++) {
		if (!scanf("%d %d %d", &start, &end, &cost))
			return 1;
		if (graph[start][end] == -1 || graph[start][end] > cost)	// 두 정점 사이 여러 간선이 존재 가능! -> 두 정점 사이 간선 유일한지 확인!
			graph[start][end] = cost;								// 여러 간선 중 가장 가중치가 작은 것 선택
	}
	if (!scanf("%d %d", &Start, &End))
		return 1;

	Solve();
	return 0;
}