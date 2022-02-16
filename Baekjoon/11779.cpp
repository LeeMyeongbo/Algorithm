#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

struct Info {
	vector<int> path;				// 거쳐온 경로 저장
	int sum;						// 비용 합
};
int n, m, graph[1001][1001], Start, End, visited_sum[1001], ans = -1;
queue<Info> q;
vector<int> ans_list;

void Solve()
{
	vector<int> path;
	path.push_back(Start);

	q.push({ path, 0 });
	visited_sum[Start] = 0;
	while (!q.empty()) {
		Info info = q.front();
		int cur = info.path.back();
		q.pop();

		if (cur == End) {								// 목적지에 도착했을 경우
			if (ans == -1 || ans > info.sum) {			// 목적지에 처음 도달하거나 합이 더 작아지는 경우 갱신
				ans = info.sum;
				ans_list = info.path;
			}
			continue;
		}
		for (int i = 1; i <= n; i++) {					// 연결된 정점들 중 방문한 적 없거나 합이 더 작은 정점 향해서 BFS 때림
			if (graph[cur][i] != -1 && (visited_sum[i] == -1 || info.sum + graph[cur][i] < visited_sum[i])) {
				vector<int> new_path = info.path;
				new_path.push_back(i);					// 경로에 현재 도시 추가하고 저장

				int new_sum = info.sum + graph[cur][i];
				visited_sum[i] = new_sum;
				q.push({ new_path, new_sum });
			}
		}
	}
	printf("%d\n%d\n", ans, ans_list.size());
	for (int i : ans_list)
		printf("%d ", i);
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