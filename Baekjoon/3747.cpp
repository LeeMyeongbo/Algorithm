#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define STD 1000
using namespace std;

int N, M, v1, v2, seq[STD * 2 + 1], num, scc_index[STD * 2 + 1], scc_num;
bool complete[STD * 2 + 1];
vector<int> graph[STD * 2 + 1];
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

int Possible()
{
	for (int i = 1; i <= N; i++)
		if (scc_index[STD - i] == scc_index[STD + i])		// i와 -i가 같은 scc라면 성립 x
			return 0;
	return 1;
}

int main()
{
	FAST;
	while (1) {
		cin >> N >> M;
		if (cin.eof())
			return 0;

		for (int i = 0; i < M; i++) {
			cin >> v1 >> v2;
			graph[STD - v1].push_back(STD + v2);
			graph[STD - v2].push_back(STD + v1);
		}
		for (int i = STD - N; i <= STD + N; i++)
			if (!complete[i] && i != STD)
				DFS(i);
		cout << Possible() << "\n";

		num = scc_num = 0;
		fill(seq, seq + STD * 2 + 1, 0);
		fill(scc_index, scc_index + STD * 2 + 1, 0);
		fill(complete, complete + STD * 2 + 1, false);
		for (int i = STD - N; i <= STD + N; i++)
			graph[i].clear();
	}
}