#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, v1, v2, ATM[500001], S, P, rest, seq[500001], num, scc[500001], scc_num, scc_indegree[500001], scc_sum[500001], Ans[500001];
bool is_restaurant[500001], complete[500001], scc_restaurant[500001];
vector<int> graph[500001], DAG[500001];		// DAG : scc를 하나의 정점으로 묶어서 형성한 그래프
stack<int> s;
queue<int> q;

int DFS(int cur)				// 그래프로부터 scc그래프 형성 & 각 scc 내부의 각 정점들의 현금 보유 액수 합 저장 & 레스토랑 있는 요소 체크
{
	seq[cur] = ++num;
	int parent = num;
	s.push(cur);

	for (int& v : graph[cur]) {
		if (!seq[v])
			parent = min(parent, DFS(v));
		else if (!complete[v])
			parent = min(parent, seq[v]);
	}
	if (parent == seq[cur]) {
		scc_num++;
		while (!s.empty()) {
			int v = s.top();
			s.pop();

			complete[v] = true;
			scc[v] = scc_num;
			scc_sum[scc_num] += ATM[v];			// 현 scc에 속한 정점의 비용 더해감
			if (is_restaurant[v])				// 현 정점에 레스토랑 존재할 경우
				scc_restaurant[scc[v]] = true;	// 이 정점이 속한 scc에도 레스토랑이 존재!
			if (cur == v)
				break;
		}
	}
	return parent;
}

int Determine()
{
	int ans = 0;
	for (int i = 1; i <= N; i++)
		for (int& j : graph[i])
			if (scc[i] && scc[j] && scc[i] != scc[j]) {		// 정점 i와 j를 방문할 수 있고 두 정점이 같은 scc에 속하지 않을 경우
				DAG[scc[i]].push_back(scc[j]);
				scc_indegree[scc[j]]++;
			}

	q.push(scc[S]);
	Ans[scc[S]] = scc_sum[scc[S]];
	while (!q.empty()) {
		int cur_scc = q.front();
		q.pop();

		if (scc_restaurant[cur_scc])
			ans = max(ans, Ans[cur_scc]);
		for (int s : DAG[cur_scc]) {
			scc_indegree[s]--;
			Ans[s] = max(Ans[s], Ans[cur_scc] + scc_sum[s]);	// 위상정렬 하면서 각 scc마다 비용 합 최댓값 갱신
			if (!scc_indegree[s])
				q.push(s);
		}
	}
	return ans;
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int e = 0; e < M; e++) {
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
	}
	for (int i = 1; i <= N; i++)
		cin >> ATM[i];
	cin >> S >> P;
	for (int p = 0; p < P; p++) {
		cin >> rest;
		is_restaurant[rest] = true;
	}

	DFS(S);					// 시작점 S가 정해져 있으므로 S로부터 갈 수 있는 정점들만 탐색해서 scc그래프 형성해주면 됨!
	cout << Determine();
	return 0;
}