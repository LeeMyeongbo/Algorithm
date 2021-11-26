#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define STD 10000
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, x, y, num, seq[2 * STD + 1], scc_num, scc_index[2 * STD + 1];
bool complete[2 * STD + 1];
vector<int> graph[2 * STD + 1];
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

bool possible()
{
	for (int i = 1; i <= M; i++)
		if (scc_index[STD + i] && scc_index[STD - i] && scc_index[STD + i] == scc_index[STD - i])
			return false;
	return true;
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> x >> y;
		graph[STD - x].push_back(STD + y);
		graph[STD - y].push_back(STD + x);
	}
	for (int i = STD - M; i <= STD + M; i++)
		if (!complete[i] && i != STD)
			DFS(i);

	if (possible())
		cout << "^_^";
	else
		cout << "OTL";
	return 0;
}