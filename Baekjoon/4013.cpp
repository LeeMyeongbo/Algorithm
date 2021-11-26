#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, v1, v2, ATM[500001], S, P, rest, seq[500001], num, scc[500001], scc_num, scc_indegree[500001], scc_sum[500001], Ans[500001];
bool is_restaurant[500001], complete[500001], scc_restaurant[500001];
vector<int> graph[500001], DAG[500001];		// DAG : scc�� �ϳ��� �������� ��� ������ �׷���
stack<int> s;
queue<int> q;

int DFS(int cur)				// �׷����κ��� scc�׷��� ���� & �� scc ������ �� �������� ���� ���� �׼� �� ���� & ������� �ִ� ��� üũ
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
			scc_sum[scc_num] += ATM[v];			// �� scc�� ���� ������ ��� ���ذ�
			if (is_restaurant[v])				// �� ������ ������� ������ ���
				scc_restaurant[scc[v]] = true;	// �� ������ ���� scc���� ��������� ����!
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
			if (scc[i] && scc[j] && scc[i] != scc[j]) {		// ���� i�� j�� �湮�� �� �ְ� �� ������ ���� scc�� ������ ���� ���
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
			Ans[s] = max(Ans[s], Ans[cur_scc] + scc_sum[s]);	// �������� �ϸ鼭 �� scc���� ��� �� �ִ� ����
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

	DFS(S);					// ������ S�� ������ �����Ƿ� S�κ��� �� �� �ִ� �����鸸 Ž���ؼ� scc�׷��� �������ָ� ��!
	cout << Determine();
	return 0;
}