#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, v1, v2, seq[100000], num, scc_index[100000], scc_num, scc_indegree[100000], ans;
bool complete[100000];
vector<int> graph[100000];
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
			scc_index[v] = scc_num;
			if (cur == v)
				break;
		}
	}
	return parent;
}

int Solve()
{
	for (int i = 0; i < N; i++)
		for (int& j : graph[i])
			if (scc_index[i] != scc_index[j])
				scc_indegree[scc_index[j]]++;

	for (int i = 1; i <= scc_num; i++)
		if (!scc_indegree[i])
			ans++;
	return ans;
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
	}
	for (int i = 0; i < N; i++)
		if (!complete[i])
			DFS(i);
	
	cout << Solve();
	return 0;
}