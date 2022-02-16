#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, S, T, A, B, num, seq[10001], scc_num, scc[10001], scc_size[10001], scc_indegree[10001], dp[10001];
bool complete[10001];
vector<int> graph[10001], scc_graph[10001];
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
		scc_num++;
		while (!s.empty()) {
			int v = s.top();
			s.pop();

			complete[v] = true;
			scc[v] = scc_num;
			scc_size[scc_num]++;		// 각 scc마다 정점의 수를 저장
			if (cur == v)
				break;
		}
	}
	return parent;
}

int Topological()
{
	int Ans = 0;
	queue<int> q;

	for (int i = 1; i <= N; i++)
		for (int& j : graph[i])
			if (scc[i] && scc[j] && scc[i] != scc[j]) {
				scc_graph[scc[i]].push_back(scc[j]);
				scc_indegree[scc[j]]++;
			}
	q.push(scc[S]);
	dp[scc[S]] = scc_size[scc[S]];

	while (!q.empty()) {
		int cur_scc = q.front();
		q.pop();

		if (cur_scc == scc[T]) {
			Ans = max(Ans, dp[cur_scc]);		// 도착하고자 하는 정점이 속한 scc에 도달했을 경우 방문 가능한 최대 도시 수 갱신
			continue;
		}
		for (int s : scc_graph[cur_scc]) {
			scc_indegree[s]--;
			dp[s] = max(dp[s], dp[cur_scc] + scc_size[s]);
			if (!scc_indegree[s])
				q.push(s);
		}
	}
	return Ans;
}

int main()
{
	FAST;
	cin >> N >> M >> S >> T;
	for (int i = 0; i < M; i++) {
		cin >> A >> B;
		graph[A].push_back(B);
	}

	DFS(S);					// 마찬가지로 시작점이 정해져 있기 때문에 S에서부터 시작해서 방문할 수 있는 정점만 탐색해서 scc그래프 형성
	cout << Topological();
	return 0;
}