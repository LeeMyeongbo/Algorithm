#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define STD 999
using namespace std;

int n, m, a, b, seq[2 * STD + 1], num, scc_index[2 * STD + 1], scc_num;
bool complete[2 * STD + 1];
vector<int> graph[2 * STD + 1];
stack<int> s;

int DFS(int cur)
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
			scc_index[v] = scc_num;
			if (cur == v)
				break;
		}
		scc_num++;
	}
	return parent;
}

bool Possible()
{
	for (int i = 1; i <= n; i++)		// -N ~ N (0은 제외) 정점들을 방문한 적이 있고 i와 -i가 같은 scc라면 진출 목록 형성 불가!
		if (scc_index[STD + i] > -1 && scc_index[STD - i] > -1 && scc_index[STD + i] == scc_index[STD - i])
			return false;
	return true;
}

int main()
{
	FAST;
	while (1) {
		cin >> n >> m;
		if (cin.eof())
			return 0;

		fill(seq, seq + 2 * STD + 1, 0);
		fill(scc_index, scc_index + 2 * STD + 1, -1);
		fill(complete, complete + 2 * STD + 1, false);
		num = scc_num = 0;

		for (int i = 0; i < m; i++) {
			cin >> a >> b;
			graph[STD - a].push_back(STD + b);
			graph[STD - b].push_back(STD + a);
		}
		graph[STD - 1].push_back(STD + 1);			// 상근이는 항상 true여야 하므로 (x1 ▽ x1)라는 절 추가 (x1이 참이라는 의미)
		for (int v = STD - n; v <= STD + n; v++)
			if (!complete[v] && v != STD)
				DFS(v);

		if (Possible())
			cout << "yes\n";
		else
			cout << "no\n";

		for (int i = STD - n; i <= STD + n; i++)
			graph[i].clear();
	}
}