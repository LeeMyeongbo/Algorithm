#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int T, n, num, seq[301], scc_index[301], graph[301][301], scc_graph[300][300];
bool complete[301];
vector<vector<int>> SCC;
vector<pair<int, int>> ans;
stack<int> s;

int dfs(int cur)			// 먼저 서로 자유롭게 왔다갔다 할 수 있는 지점끼리 찾아서 하나의 scc로 묶어줌
{
	seq[cur] = ++num;
	int par = num;
	s.push(cur);

	for(int i = 1; i <= n; i++) {
		if (!graph[cur][i])
			continue;
		if (!seq[i])
			par = min(par, dfs(i));
		else if (!complete[i])
			par = min(par, seq[i]);
	}
	if (par == seq[cur]) {
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
	return par;
}

void solve()
{
	for (auto& scc : SCC)
		for (int i = 0; i < (int)scc.size(); i++)
			if (scc[i] != scc[(i + 1) % scc.size()])
				ans.push_back({ scc[i], scc[(i + 1) % scc.size()] });	// 같은 scc내에 속한 정점들끼리 연결, 저장

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)									// scc를 하나의 정점으로 하는 scc_graph 형성
			if (graph[i][j] && scc_index[i] != scc_index[j])		// i->j 만족하면서 i와 j가 다른 scc에 속할 경우 연결
				scc_graph[scc_index[i]][scc_index[j]] = 1;

	for (int pass = 0; pass < (int)SCC.size(); pass++)				// 플로이드 와샬로 필요없는 간선 제거
		for (int start = 0; start < (int)SCC.size(); start++)
			for (int end = 0; end < (int)SCC.size(); end++)
				if (scc_graph[start][pass] && scc_graph[pass][end])		// start->pass 경로와 pass->end 경로 모두 존재할 경우
					scc_graph[start][end] = 0;							// start->end 경로 필요 x => 제거!

	for (int i = 0; i < (int)SCC.size(); i++)
		for (int j = 0; j < (int)SCC.size(); j++)
			if (scc_graph[i][j])
				ans.push_back({ SCC[i][0], SCC[j][0] });	// 연결된 두 scc 내 0번(scc 크기가 1일수도 있음) index의 정점끼리 연결, 저장

	printf("%d\n", ans.size());
	while (!ans.empty()) {
		printf("%d %d\n", ans.back().first, ans.back().second);
		ans.pop_back();
	}
}

int main()
{
	scanf_s("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf_s("%d", &n);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				scanf_s("%1d", &graph[i][j]);

		for (int i = 1; i <= n; i++)
			if (!complete[i])
				dfs(i);
		solve();

		num = 0;
		fill(seq, seq + n + 1, 0);
		fill(scc_index, scc_index + n + 1, 0);
		fill(complete, complete + n + 1, false);
		for (int i = 0; i < (int)SCC.size(); i++)
			fill(scc_graph[i], scc_graph[i] + SCC.size(), 0);

		SCC.clear();
	}
	return 0;
}