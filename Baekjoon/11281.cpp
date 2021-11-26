#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define STD 10000
using namespace std;

int N, M, i, j, num, seq[2 * STD + 1], scc_index[2 * STD + 1], scc_indegree[2 * STD + 1], truth[STD + 1];
bool complete[2 * STD + 1];
vector<int> graph[2 * STD + 1], scc_graph[2 * STD + 1];
vector<vector<int>> SCC;
stack<int> s;

int DFS(int cur)			// SCC로 묶어 같은 진리값을 가지는 정점들 저장
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
		vector<int> scc;
		while (!s.empty()) {
			int v = s.top();
			s.pop();

			complete[v] = true;
			scc_index[v] = SCC.size();
			scc.push_back(v);
			if (cur == v)
				break;
		}
		SCC.push_back(scc);
	}
	return parent;
}

int Determine()
{
	for (int v = 1; v <= N; v++)
		if (scc_index[STD + v] == scc_index[STD - v])
			return 0;
	return 1;
}

void Topological()
{
	queue<int> q;
	for (int u = 1; u <= N; u++) {
		for (int& v : graph[STD + u])
			if (scc_index[STD + u] != scc_index[v]) {
				scc_graph[scc_index[STD + u]].push_back(scc_index[v]);
				scc_indegree[scc_index[v]]++;
			}
		for (int& v : graph[STD - u])
			if (scc_index[STD - u] != scc_index[v]) {
				scc_graph[scc_index[STD - u]].push_back(scc_index[v]);
				scc_indegree[scc_index[v]]++;
			}
	}
	for (int n = 0; n < SCC.size(); n++)
		if (!scc_indegree[n]) {
			for (int& v : SCC[n])
				v > STD ? truth[v - STD] = -1 : truth[STD - v] = 1;		// 맨 처음 시작할 scc의 정점들은 모두 false로 둠
			q.push(n);													// 음수일 땐 1, 양수일 땐 -1
		}
	
	while (!q.empty()) {
		int cur_scc = q.front();
		q.pop();

		for (int& s : scc_graph[cur_scc]) {
			scc_indegree[s]--;
			if (!scc_indegree[s]) {					// 위상 정렬 진행하면서 판별하지 않은 scc의 정점들은 모두 false로
				for (int& v : SCC[s]) {
					int x = v > STD ? v - STD : STD - v;
					if (!truth[x])
						truth[x] = v > STD ? -1 : 1;
				}
				q.push(s);
			}
		}
	}
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int m = 0; m < M; m++) {
		cin >> i >> j;								// i ▽ j 임을 나타낼 때
		graph[STD + -i].push_back(STD + j);			// ~i → j (i가 거짓일 때 j는 반드시 참이여야 함)
		graph[STD + -j].push_back(STD + i);			// ~j → i (j가 거짓일 때 i는 반드시 참이여야 함)
	}
	for (int v = 1; v <= N; v++) {					// 1, -1, 2, -2... 순으로 scc 형성
		if (!complete[STD + v])
			DFS(STD + v);
		if (!complete[STD - v])
			DFS(STD - v);
	}
	int d = Determine();
	cout << d << "\n";
	
	if (d) {
		Topological();
		for (int i = 1; i <= N; i++)
			truth[i] > 0 ? cout << "1 " : cout << "0 ";
	}
	return 0;
}