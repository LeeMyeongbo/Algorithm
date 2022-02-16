#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

int n, jump, start, order, seq[100001], scc_num, sccid[100001], scc_size[100001], dij[100001];
bool complete[100001];
vector<int> graph[100001], scc_graph[100001];
stack<int> s;

int dfs(int cur)					// 각 정점마다 dfs 돌리며 scc 탐색
{
	seq[cur] = ++order;
	int p = order;
	s.push(cur);

	for (int& i : graph[cur]) {
		if (!seq[i])
			p = min(p, dfs(i));
		else if (!complete[i])
			p = min(p, seq[i]);
	}
	if (p == seq[cur]) {
		scc_num++;
		while (!s.empty()) {
			int v = s.top();
			s.pop();

			complete[v] = true;
			sccid[v] = scc_num;
			scc_size[scc_num]++;
			if (v == cur)
				break;
		}
	}
	return p;
}

int solve()
{
	int ans = 0;
	priority_queue<pair<int, int>> q;

	for (int i = 1; i <= n; i++)
		for (int& v : graph[i])
			if (sccid[v] != sccid[i])
				scc_graph[sccid[i]].push_back(sccid[v]);

	dij[sccid[start]] = scc_size[sccid[start]];
	q.push({ dij[sccid[start]], sccid[start] });
	while (!q.empty()) {								// 역(?) 다익스트라 방식으로 최댓값을 갱신해 나감
		int cur_scc = q.top().second;
		int sum = q.top().first;
		ans = max(ans, sum);
		q.pop();

		if (dij[cur_scc] > sum)
			continue;

		for (int& i : scc_graph[cur_scc]) {
			if (dij[i] < dij[cur_scc] + scc_size[i]) {
				dij[i] = dij[cur_scc] + scc_size[i];
				q.push({ dij[i], i });
			}
		}
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> jump;
		if (i - jump > 0)
			graph[i].push_back(i - jump);
		if (i + jump <= n)
			graph[i].push_back(i + jump);
	}
	cin >> start;
	for (int i = 1; i <= n; i++)
		if (!complete[i])
			dfs(i);

	cout << solve();
	return 0;
}