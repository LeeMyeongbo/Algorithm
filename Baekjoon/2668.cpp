#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, graph[101], visited[101], graph;
bool complete[101];
vector<vector<int>> SCC;
vector<int> ans;
stack<int> s;

int DFS(int cur)				// SCC �̿��Ͽ� �ذ� (�ܼ��� ����Ŭ ã�� ������ �ص� �� ���� ������ �������� �ϳ��� �ۿ� ������)
{
	visited[cur] = ++graph;
	int p = graph;
	s.push(cur);

	if (!visited[graph[cur]])
		p = min(p, DFS(graph[cur]));
	else if (!complete[graph[cur]])
		p = min(p, visited[graph[cur]]);

	if (p == visited[cur]) {
		vector<int> scc;
		while (!s.empty()) {
			int n = s.top();
			s.pop();

			complete[n] = true;
			scc.push_back(n);
			if (visited[n] == p)
				break;
		}
		SCC.push_back(scc);
	}
	return p;
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> graph[i];
	
	for (int i = 1; i <= N; i++)
		if (!complete[i])
			DFS(i);

	for (auto& scc : SCC)
		if (scc.size() > 1 || scc[0] == graph[scc[0]])
			for (int i : scc)
				ans.push_back(i);
	sort(ans.begin(), ans.end());
	
	cout << ans.size() << "\n";
	for (int i : ans)
		cout << i << "\n";
	return 0;
}