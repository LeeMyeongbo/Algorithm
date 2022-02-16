#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int T, N, M, A, B, seq[100000], num, scc[100000], scc_index, indegree[100000], start_num, start_scc;
bool complete[100000];
vector<int> graph[100000];
stack<int> s;

int DFS(int cur)							// DFS 이용해 각 정점이 몇 번째 scc에 속하는지 get
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
		while (!s.empty()) {
			int v = s.top();
			s.pop();

			complete[v] = true;
			scc[v] = scc_index;
			if (seq[v] == parent)
				break;
		}
		scc_index++;
	}
	return parent;
}

void Determine()							// 각 scc마다 진입 차수가 0인 것의 개수를 헤아려 봄
{
	for (int i = 0; i < N; i++)
		for (int& j : graph[i])
			if (scc[i] != scc[j])
				indegree[scc[j]]++;

	for (int i = 0; i < scc_index; i++)
		if (!indegree[i]) {
			start_num++;
			start_scc = i;
		}

	if (start_num == 1) {
		for (int i = 0; i < N; i++)
			if (scc[i] == start_scc)
				cout << i << "\n";
	}
	else
		cout << "Confused\n";
}

int main()
{
	FAST;
	cin >> T;
	for (int test = 1; test <= T; test++) {
		cin >> N >> M;
		for (int e = 0; e < M; e++) {
			cin >> A >> B;
			graph[A].push_back(B);
		}

		for (int v = 0; v < N; v++)
			if (!complete[v])
				DFS(v);
		Determine();
		cout << "\n";

		num = scc_index = start_num = start_scc = 0;
		fill(seq, seq + N, 0);
		fill(scc, scc + N, 0);
		fill(indegree, indegree + N, 0);
		fill(complete, complete + N, false);

		for (int i = 0; i < N; i++)
			graph[i].clear();
	}
	return 0;
}