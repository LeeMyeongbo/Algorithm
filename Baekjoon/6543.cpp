#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int n, m, graph, w, seq[5001], num, scc_index[5001], outdegree[5001];
bool complete[5001];
vector<int> graph[5001], ans;
vector<vector<int>> SCC;
stack<int> s;

int DFS(int cur)
{
	seq[cur] = ++num;
	int parent = num;
	s.push(cur);

	for (int& i : graph[cur]) {
		if (!seq[i])
			parent = min(parent, DFS(i));
		else if (!complete[i])
			parent = min(parent, seq[i]);
	}
	if (parent == seq[cur]) {
		vector<int> scc;
		while (!s.empty()) {
			int v = s.top();
			s.pop();

			complete[v] = true;
			scc_index[v] = SCC.size();
			scc.push_back(v);
			if (v == cur)
				break;
		}
		SCC.push_back(scc);
	}
	return parent;
}

void Determine()					// outdegree가 0인 scc가 바로 싱크에 해당!
{
	for (int i = 1; i <= n; i++)
		for (int& j : graph[i]) {
			if (scc_index[i] != scc_index[j])
				outdegree[scc_index[i]]++;
		}

	for (int i = 0; i < SCC.size(); i++)
		if (!outdegree[i])
			for (int v : SCC[i])
				ans.push_back(v);
	
	sort(ans.begin(), ans.end());
	for (int& i : ans)
		cout << i << " ";
}

int main()
{
	FAST;
	while (1) {
		cin >> n;
		if (!n)
			return 0;
		cin >> m;
		for (int i = 0; i < m; i++) {
			cin >> graph >> w;
			graph[graph].push_back(w);
		}
		for (int i = 1; i <= n; i++)
			if (!complete[i])
				DFS(i);
		Determine();
		cout << "\n";

		num = 0;
		fill(seq, seq + n + 1, 0);
		fill(scc_index, scc_index + n + 1, 0);
		fill(outdegree, outdegree + n + 1, 0);
		fill(complete, complete + n + 1, false);

		for (int i = 1; i <= n; i++)
			graph[i].clear();
		SCC.clear();
		ans.clear();
	}
}