#include <iostream>
#include <vector>
#include <queue>
#include <set>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int T, n, m, a, b, team[500], indegree[501];
set<int> graph[501];

void Solve()
{
	vector<int> ans;
	queue<int> q;

	for (int i = 1; i <= n; i++)
		if (!indegree[i])
			q.push(i);

	while (!q.empty()) {
		if (q.size() > 1) {
			cout << "?\n";				// ť�� �� �̻��� ��尡 �����Ѵٸ� ��Ȯ�� ���� �ޱ� �� ����
			return;
		}
		int cur = q.front();
		ans.push_back(cur);
		q.pop();

		for (int v : graph[cur]) {
			indegree[v]--;
			if (!indegree[v])
				q.push(v);
		}
	}
	if (ans.size() != n)
		cout << "IMPOSSIBLE";			// ����Ŭ�� �����Ͽ� ��� ������ ���ĵ��� ���ߴٸ� impossible
	else
		for (int i : ans)
			cout << i << " ";
	cout << "\n";
}

int main()
{
	FAST;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> team[i];
		for (int i = 0; i < n - 1; i++)
			for (int j = i + 1; j < n; j++) {			// ������ �� nC2(== n*(n - 1)/2)�� �����ؾ� ��!
				graph[team[i]].insert(team[j]);
				indegree[team[j]]++;
			}

		cin >> m;
		for (int i = 0; i < m; i++) {					// �켱������ �ٲ� ���� ������Ʈ
			cin >> a >> b;
			if (graph[a].count(b)) {
				graph[a].erase(b);
				indegree[b]--;
				graph[b].insert(a);
				indegree[a]++;
			}
			else {
				graph[b].erase(a);
				indegree[a]--;
				graph[a].insert(b);
				indegree[b]++;
			}
		}
		Solve();

		fill(indegree, indegree + n + 1, 0);
		for (int i = 1; i <= n; i++)
			graph[i].clear();
	}
	return 0;
}