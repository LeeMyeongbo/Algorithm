#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, E, a, b, c, v1, v2;
long long one_start[801], v1_start[801], v2_start[801];		// ����ġ �� ������ �� int�� ���� �Ѿ ���� ������..
vector<pair<int, int>> graph[801];
priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;

void Dijkstra(int start, long long shortest[])
{
	fill(shortest, shortest + N + 1, -1);
	q.push({ 0, start });
	shortest[start] = 0;

	while (!q.empty()) {
		int cur = q.top().second;
		q.pop();

		/*if (cur == N)			// N�� ������ ���ľ� �ִ� �Ÿ��� ���� ��쵵 ���� �� ����!
			continue;*/
		for (auto p : graph[cur]) {
			if (shortest[p.second] == -1 || shortest[p.second] > shortest[cur] + p.first) {
				shortest[p.second] = shortest[cur] + p.first;
				q.push({ shortest[p.second], p.second });
			}
		}
	}
}

long long Solve()
{
	Dijkstra(1, one_start);
	Dijkstra(v1, v1_start);
	Dijkstra(v2, v2_start);			// 1�� ����, v1, v2���� �����Ͽ� �� ���������� �ִ� �Ÿ� ����

	if (one_start[v1] > -1 && v1_start[v2] > -1 && v2_start[N] > -1 && one_start[v2] > -1 && v2_start[v1] > -1 && v1_start[N] > -1)
		return min(one_start[v1] + v1_start[v2] + v2_start[N], one_start[v2] + v2_start[v1] + v1_start[N]);
	else if (one_start[v1] > -1 && v1_start[v2] > -1 && v2_start[N] > -1)
		return one_start[v1] + v1_start[v2] + v2_start[N];
	else if (one_start[v2] > -1 && v2_start[v1] > -1 && v1_start[N] > -1)
		return one_start[v2] + v2_start[v1] + v1_start[N];
	else
		return -1;
}

int main()
{
	FAST;
	cin >> N >> E;
	for (int e = 0; e < E; e++) {
		cin >> a >> b >> c;
		graph[a].push_back({ c, b });
		graph[b].push_back({ c, a });
	}
	for (int i = 1; i <= N; i++)
		sort(graph[i].begin(), graph[i].end());
	cin >> v1 >> v2;

	cout << Solve();
	return 0;
}