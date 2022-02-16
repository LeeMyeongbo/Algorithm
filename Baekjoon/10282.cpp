#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int T, n, d, c, a, b, s, di[10001];
vector<pair<int, int>> graph[10001];
priority_queue<pair<int, int>> q;

void Dijkstra()
{
	int num = 0, time = 0;

	fill(di, di + 10001, -1);
	di[c] = 0;
	q.push({ 0, c });

	while (!q.empty()) {				// 다익스트라를 통해 각 컴퓨터까지 바이러스에 감염되는 최소 시간 갱신해가면 됨
		int cur = q.top().second;
		int sum = -q.top().first;
		q.pop();

		if (sum > di[cur])
			continue;

		for (auto p : graph[cur]) {
			if (di[p.second] == -1 || di[p.second] > di[cur] + p.first) {
				di[p.second] = di[cur] + p.first;
				q.push({ -di[p.second], p.second });
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		if (di[i] != -1)
			num++;						// 최소 시간이 -1이 아니면 무조건 감염된다는 소리
		time = max(time, di[i]);		// 가장 늦게 감염되는 컴퓨터가 걸리는 시간 도출
	}
	cout << num << " " << time << "\n";
}

int main()
{
	FAST;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> n >> d >> c;

		for (int e = 0; e < d; e++) {
			cin >> a >> b >> s;
			graph[b].push_back({ s, a });
		}
		Dijkstra();
		for (int i = 1; i <= n; i++)
			graph[i].clear();
	}
	return 0;
}