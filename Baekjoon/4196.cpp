#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int T, N, M, x, y, seq[100001], num, scc[100001], scc_index, indegree[100001], ans;
bool complete[100001];
vector<int> graph[100001];		// seq[i] : i�� ������ �湮�� ����, scc[i] : i�� ������ ���� scc ��ȣ, indegree[i] : i�� scc�� ��������
stack<int> s;

int dfs(int cur)				// �� �������� �� ��° scc�� ���ϴ��� ����
{
	seq[cur] = ++num;
	int min_s = num;
	s.push(cur);

	for (int i : graph[cur]) {
		if (!seq[i])
			min_s = min(min_s, dfs(i));
		else if (!complete[i])
			min_s = min(min_s, seq[i]);
	}
	if (min_s == seq[cur]) {
		scc_index++;
		while (!s.empty()) {
			int v = s.top();
			s.pop();

			complete[v] = true;
			scc[v] = scc_index;
			if (seq[v] == min_s)
				break;
		}
	}
	return min_s;
}

int Define_new_Graph()			// ��� scc�� ���� ���� ����
{
	for (int i = 1; i <= N; i++)
		for (int v : graph[i])
			if (scc[i] != scc[v])
				indegree[scc[v]]++;

	for (int i = 1; i <= scc_index; i++)
		if (!indegree[i])		// ���� ������ 0�� scc�� �ٷ� �Ѿ�߸� ���̳밡 ��!
			ans++;

	return ans;
}

int main()
{
	FAST;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N >> M;
		for (int e = 0; e < M; e++) {
			cin >> x >> y;
			graph[x].push_back(y);
		}
		for (int i = 1; i <= N; i++)
			if (!complete[i])
				dfs(i);
		cout << Define_new_Graph() << "\n";

		fill(seq, seq + N + 1, 0);
		fill(scc, scc + N + 1, 0);
		fill(indegree, indegree + N + 1, 0);
		fill(complete, complete + N + 1, false);
		for (int i = 1; i <= N; i++)
			graph[i].clear();
		num = scc_index = ans = 0;
	}
	return 0;
}