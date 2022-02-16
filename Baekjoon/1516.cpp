#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, Time[501], edge[501], ans[501], graph;		// edge[i] : i번 정점으로 향하는 진입 간선 수
vector<int> graph[501];
queue<int> q;

void Solve()
{
	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (int i : graph[cur]) {
			edge[i]--;
			ans[i] = max(ans[i], Time[i] + ans[cur]);
			if (!edge[i])
				q.push(i);
		}
	}
	for (int i = 1; i <= N; i++)
		cout << ans[i] << "\n";
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> Time[i];
		while (1) {
			cin >> graph;
			if (graph == -1)
				break;
			graph[graph].push_back(i);
			edge[i]++;
		}
		if (!edge[i]) {
			q.push(i);
			ans[i] = Time[i];
		}
	}

	Solve();
	return 0;
}