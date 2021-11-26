#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int N, order, seq[27];
char c[5], choice;
bool complete[27];
vector<int> graph[27];
vector<vector<char>> SCC;
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
		vector<char> scc;
		while (!s.empty()) {
			int v = s.top();
			s.pop();

			complete[v] = true;
			scc.push_back(v + 'A' - 1);
			if (v == cur)
				break;
		}
		SCC.push_back(scc);
	}
	return par;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	while (1) {
		cin >> N;
		if (!N)
			return 0;

		bool input[27] = { false, };
		while (N--) {
			for (int i = 0; i < 5; i++) {
				cin >> c[i];
				input[c[i] - 'A' + 1] = true;
			}
			cin >> choice;
			for (int i = 0; i < 5; i++)
				if (c[i] != choice)
					graph[c[i] - 'A' + 1].push_back(choice - 'A' + 1);
		}
		for (int i = 1; i < 27; i++)
			if (input[i] && !complete[i])
				dfs(i);

		for (auto& scc : SCC)
			sort(scc.begin(), scc.end());
		sort(SCC.begin(), SCC.end());
		for (auto& scc : SCC) {
			for (char& c : scc)
				cout << c << " ";
			cout << "\n";
		}
		cout << "\n";

		order = 0;
		fill(seq, seq + 27, 0);
		fill(complete, complete + 27, false);
		for (int i = 1; i < 27; i++)
			graph[i].clear();
		SCC.clear();
	}
}