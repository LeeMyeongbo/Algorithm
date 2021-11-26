#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int N, M, u, graph, T, t[200000], order, seq[200001], scc_num, sccid[200001], scc_indegree[200000], starting_scc;
bool complete[200001], visited_scc[200000];
vector<int> graph[200001];
stack<int> s;

int dfs(int cur)
{
	seq[cur] = ++order;
	int par = order;
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
			sccid[v] = scc_num;
			if (v == cur)
				break;
		}
	}
	return par;
}

int find()
{
	int Found = 0;
	for (int i = 1; i <= N; i++)
		for(int& j : graph[i])
			if (sccid[i] != sccid[j])
				scc_indegree[sccid[j]]++;

	for (int i = 1; i <= scc_num; i++)
		if (!scc_indegree[i])
			starting_scc++;				// ���������� 0�� scc ���� üũ (�ּ��� ���԰����� ���� scc�������� �����ؾ� �ϱ� ����)

	for (int i = 0; i < T; i++) {		// �ش� t[i]�� ���� scc�� ���������� 0�̰� �湮�� �� ���� scc��� �湮 üũ + ���� ����
		if (!scc_indegree[sccid[t[i]]] && !visited_scc[sccid[t[i]]]) {
			visited_scc[sccid[t[i]]] = true;
			Found++;
		}
	}
	if (Found < starting_scc)	// ���� ��Ʒ��� ���������� 0�� scc�� �������� �۴ٸ�
		return -1;				// ��ó ��Ƹ��� ����, �� �ٸ� ���������� 0�� scc�� �Լ����� ȣ��� �� ���ٴ� �ǹ�
	else
		return Found;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N >> M;
	while (M--) {
		cin >> u >> graph;
		graph[u].push_back(graph);
	}
	cin >> T;
	for (int i = 0; i < T; i++)
		cin >> t[i];

	for (int i = 1; i <= N; i++)
		if (!complete[i])
			dfs(i);

	cout << find();
	return 0;
}