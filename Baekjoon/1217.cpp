#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define MAX 20000
using namespace std;

int N, M, s1, s2, order, seq[2 * MAX + 1], scc_num, scc_index[2 * MAX + 1];
bool complete[2 * MAX + 1];
vector<int> graph[2 * MAX + 1];
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
			scc_index[v] = scc_num;
			if (v == cur)
				break;
		}
	}
	return par;
}

bool chk()					// 2-SAT로 간단히 해결 가능
{
	for (int i = 1; i <= M; i++)
		if (scc_index[MAX - i] == scc_index[MAX + i])
			return false;
	return true;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	while (1) {
		cin >> N >> M;
		if (!N && !M)
			return 0;

		for (int i = 1; i <= N; i++) {
			cin >> s1 >> s2;
			graph[MAX + s1].push_back(MAX - s2);
			graph[MAX + s2].push_back(MAX - s1);
		}
		for (int i = MAX - M; i <= MAX + M; i++)
			if (i != MAX && !complete[i])
				dfs(i);
		if (chk())
			cout << 1 << "\n";
		else
			cout << 0 << "\n";

		order = scc_num = 0;
		fill(seq, seq + 2 * MAX + 1, 0);
		fill(scc_index, scc_index + 2 * MAX + 1, 0);
		fill(complete, complete + 2 * MAX + 1, false);
		for (int i = MAX - M; i <= MAX + M; i++)
			graph[i].clear();
	}
}