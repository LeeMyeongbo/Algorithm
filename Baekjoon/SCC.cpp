#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int V, E, a, b, order[10001], n;		// order[i] : i�� ������ �湮�� ���� ����
bool complete[10001];					// complete[i] : i�� ���� Ž���� �Ϸ�Ǿ����� ����
vector<int> graph[10001];
vector<vector<int>> SCC;
stack<int> s;

int dfs(int cur)
{
	order[cur] = ++n;					// ���� ������ �湮�� ���� ����
	int p = order[cur];
	s.push(cur);

	for (int i : graph[cur]) {			// p�� �ּڰ����� ����
		if (!order[i])					// ���� �ش� ������ �湮���� �ʾ��� ���
			p = min(p, dfs(i));
		else if (!complete[i])			// �湮�� �ߴµ� ������ ��� Ž���� �Ϸ���� �ʾ��� ���
			p = min(p, order[i]);
	}

	if (p == order[cur]) {
		vector<int> scc;
		while (!s.empty()) {
			int v = s.top();
			s.pop();

			complete[v] = true;
			scc.push_back(v);

			if (order[v] == p)			// �ڱ� �ڽ��� ���� ������ �ݺ��ؼ� pop
				break;
		}
		sort(scc.begin(), scc.end());
		SCC.push_back(scc);
	}
	return p;
}

int main()
{
	FAST;
	cin >> V >> E;
	for (int e = 0; e < E; e++) {
		cin >> a >> b;
		graph[a].push_back(b);
	}
	for (int i = 1; i <= V; i++)
		if (!complete[i])
			dfs(i);

	cout << SCC.size() << "\n";
	sort(SCC.begin(), SCC.end());

	for (auto& scc : SCC) {
		for (int v : scc)
			cout << v << " ";
		cout << "\n";
	}
	return 0;
}