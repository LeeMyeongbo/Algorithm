#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

int N, seq[200001], num, scc_index[200001], scc_num, scc_indegree[200001], scc_size[200001], dp[200001], ans;
bool complete[200001];
vector<int> graph[200001], scc_graph[200001];
stack<int> s;

int dfs(int cur)				// scc 탐색
{
	seq[cur] = ++num;
	int par = num;
	s.push(cur);

	for (int& i : graph[cur]) {
		if (!seq[i])
			par = min(par, dfs(i));
		else if (!complete[i])
			par = min(par, seq[i]);
	}
	if (par == seq[cur]) {
		scc_num++;
		while (!s.empty()) {
			int v = s.top();
			s.pop();

			complete[v] = true;
			scc_index[v] = scc_num;
			scc_size[scc_num]++;
			if (v == cur)
				break;
		}
	}
	return par;
}

int Solve()
{
	queue<int> q;
	for (int i = 1; i <= N; i++)
		for (int& j : graph[i])						// scc를 하나의 정점으로 보고 scc_graph 형성
			if (scc_index[i] != scc_index[j]) {
				scc_graph[scc_index[i]].push_back(scc_index[j]);
				scc_indegree[scc_index[j]]++;
			}
	
	for (int i = 1; i <= scc_num; i++)
		if (!scc_indegree[i]) {						// 진입간선 수가 0인 scc 큐에 삽입 + dp테이블에 해당 scc 내의 정점 수 체크
			q.push(i);
			dp[i] = scc_size[i];
		}
	while (!q.empty()) {							// 위상 정렬을 진행하며 방문 가능한 정점 수 최댓값 갱신
		int cur_scc = q.front();
		q.pop();

		ans = max(ans, dp[cur_scc]);
		for (int& scc : scc_graph[cur_scc]) {
			scc_indegree[scc]--;
			dp[scc] = max(dp[scc], dp[cur_scc] + scc_size[scc]);
			if (!scc_indegree[scc])
				q.push(scc);
		}
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N;
	for (int i = 1; i <= N; i++) {		// 1부터 N까지 어느 정점으로 가는지 찾아서 연결하며 그래프 형성
		int s = i, add = 0;
		while (s) {
			add += s % 10;
			s /= 10;
		}
		int e = i + add;
		if (e > N)
			e -= N;
		graph[i].push_back(e);
	}
	for (int i = 1; i <= N; i++)
		if (!complete[i])
			dfs(i);

	cout << Solve();
	return 0;
}