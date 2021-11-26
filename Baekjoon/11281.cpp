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

int DFS(int cur)			// SCC�� ���� ���� �������� ������ ������ ����
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
				v > STD ? truth[v - STD] = -1 : truth[STD - v] = 1;		// �� ó�� ������ scc�� �������� ��� false�� ��
			q.push(n);													// ������ �� 1, ����� �� -1
		}
	
	while (!q.empty()) {
		int cur_scc = q.front();
		q.pop();

		for (int& s : scc_graph[cur_scc]) {
			scc_indegree[s]--;
			if (!scc_indegree[s]) {					// ���� ���� �����ϸ鼭 �Ǻ����� ���� scc�� �������� ��� false��
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
		cin >> i >> j;								// i �� j ���� ��Ÿ�� ��
		graph[STD + -i].push_back(STD + j);			// ~i �� j (i�� ������ �� j�� �ݵ�� ���̿��� ��)
		graph[STD + -j].push_back(STD + i);			// ~j �� i (j�� ������ �� i�� �ݵ�� ���̿��� ��)
	}
	for (int v = 1; v <= N; v++) {					// 1, -1, 2, -2... ������ scc ����
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