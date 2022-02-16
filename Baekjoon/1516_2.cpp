#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, pre, t[501], indegree[501], dp[501];			// dp[i] : i번 건물 완료하는 데 걸리는 최소 시간
vector<int> graph[501];
queue<int> q;

void solve()
{
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		
		for (int v : graph[cur]) {					// cur(현재 정점)과 연결된 모든 정점들 한 번씩 살핌
			indegree[v]--;
			dp[v] = max(dp[v], dp[cur] + t[v]);
			if (!indegree[v])
				q.push(v);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> t[i];

		while (true) {
			cin >> pre;
			if (pre == -1)
				break;
			graph[pre].push_back(i);
			indegree[i]++;
		}
	}

	for (int i = 1; i <= N; i++) {
		if (!indegree[i]) {
			dp[i] = t[i];
			q.push(i);
		}
	}
	solve();

	for (int i = 1; i <= N; i++)
		cout << dp[i] << "\n";

	return 0;
}