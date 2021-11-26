#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, cost[101], seq[101], num, ans;
bool complete[101];
char connected[100][101];
vector<int> graph[101];
vector<vector<int>> SCC;
stack<int> s;

int dfs(int cur)
{
	seq[cur] = ++num;
	int parent = num;
	s.push(cur);

	for (int& i : graph[cur]) {
		if (!seq[i])
			parent = min(parent, dfs(i));
		else if (!complete[i])
			parent = min(parent, seq[i]);
	}
	if (parent == seq[cur]) {
		vector<int> scc;
		while (!s.empty()) {
			int v = s.top();
			s.pop();

			complete[v] = true;
			scc.push_back(v);
			if (cur == v)
				break;
		}
		SCC.push_back(scc);
	}
	return parent;
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> cost[i];

	for (int i = 0; i < N; i++) {
		cin >> connected[i];
		for (int j = 0; j < N; j++) {
			if (connected[i][j] == '1')
				graph[i + 1].push_back(j + 1);
		}
	}
	for (int i = 1; i <= N; i++)
		if (!complete[i])
			dfs(i);

	for (auto& scc : SCC) {
		int Min = 1000001;
		for (int& i : scc)
			Min = min(Min, cost[i]);
		ans += Min;
	}
	
	cout << ans;
	return 0;
}