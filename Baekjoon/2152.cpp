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
			scc_size[scc_num]++;		// �� scc���� ������ ���� ����
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
			Ans = max(Ans, dp[cur_scc]);		// �����ϰ��� �ϴ� ������ ���� scc�� �������� ��� �湮 ������ �ִ� ���� �� ����
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

	DFS(S);					// ���������� �������� ������ �ֱ� ������ S�������� �����ؼ� �湮�� �� �ִ� ������ Ž���ؼ� scc�׷��� ����
	cout << Topological();
	return 0;
}