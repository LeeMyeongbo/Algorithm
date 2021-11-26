#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define MAX 500000
using namespace std;

int N, M, a, sa, b, sb, order, seq[2 * MAX + 1], scc_num, scc_index[2 * MAX + 1];
bool complete[2 * MAX + 1];
vector<int> graph[2 * MAX + 1];		// 꺼져 있는 거는 MAX 보다 작고 켜져 있는 거는 MAX 보다 큼
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

bool determine()
{
	for (int i = 1; i <= M; i++)
		if (scc_index[MAX - i] == scc_index[MAX + i])
			return false;
	return true;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> a >> sa >> b >> sb;
		if (!sa && !sb) {							// 두 스위치가 모두 꺼져 있어야 문이 닫힌다면
			graph[MAX + a].push_back(MAX - b);		// a가 켜져 있을 땐 b는 꺼져야 함
			graph[MAX + b].push_back(MAX - a);		// b가 켜져 있을 땐 a는 꺼져야 함
		}
		else if (!sa && sb) {						// a는 꺼져 있어야 닫히고 b는 켜져 있어야 닫힌다면
			graph[MAX + a].push_back(MAX + b);		// a가 켜져 있을 땐 b도 켜져 있어야 함
			graph[MAX - b].push_back(MAX - a);		// b가 꺼져 있을 땐 a도 꺼져 있어야 함
		}
		else if (sa && !sb) {						// a는 켜져 있어야 닫히고 b는 꺼져 있어야 닫힌다면
			graph[MAX - a].push_back(MAX - b);		// a가 꺼져 있을 땐 b도 꺼져 있어야 함
			graph[MAX + b].push_back(MAX + a);		// b가 켜져 있을 땐 a도 켜져 있어야 함
		}
		else {										// 두 스위치가 모두 켜져 있어야 문이 닫힌다면
			graph[MAX - a].push_back(MAX + b);		// a가 꺼져 있을 땐 b는 켜져야 함
			graph[MAX - b].push_back(MAX + a);		// b가 꺼져 있을 땐 a는 켜져야 함
		}
	}
	for (int i = MAX - M; i <= MAX + M; i++)
		if (i != MAX && !complete[i])
			dfs(i);
	if (determine()) {
		for (int i = 1; i <= M; i++) {
			if (scc_index[MAX - i] < scc_index[MAX + i])
				cout << 0 << "\n";
			else
				cout << 1 << "\n";
		}
	}
	else
		cout << "IMPOSSIBLE\n";
	return 0;
}