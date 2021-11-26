#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define STD 10000
using namespace std;

int N, M, i, j, num, seq[2 * STD + 1], scc[2 * STD + 1], scc_num;
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
		scc_num++;
		while (!s.empty()) {
			int v = s.top();
			s.pop();

			complete[v] = true;
			scc[v] = scc_num;
			if (cur == v)
				break;
		}
	}
	return parent;
}

int Determine()
{
	for (int v = 1; v <= N; v++)
		if (scc[STD + v] == scc[STD - v])		// ���� v�� ~v�� ���� scc�� ���Ѵٸ� ~v �� v & v �� ~v�� ���ÿ� �����ϰ� �� (���� �ȵ���)
			return 0;
	return 1;
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
	cout << Determine();
	return 0;
}