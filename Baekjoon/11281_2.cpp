#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define STD 10000
using namespace std;

int N, M, i, j, num, seq[2 * STD + 1], scc_num, scc_index[2 * STD + 1];
bool complete[2 * STD + 1];
vector<int> graph[2 * STD + 1];
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

int Determine()        // x�� ~x�� ���� scc�� ���ϴ��� �Ǵ�
{
	for (int v = 1; v <= N; v++)
		if (scc_index[STD + v] == scc_index[STD - v])
			return 0;
	return 1;
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int m = 0; m < M; m++) {
		cin >> i >> j;
		graph[STD + -i].push_back(STD + j);
		graph[STD + -j].push_back(STD + i);
	}
	for (int v = STD - N; v <= STD + N; v++)
		if (!complete[v] && v)
			DFS(v);

	int d = Determine();
	cout << d << "\n";

	if (d)
		for (int i = 1; i <= N; i++)	// i�� scc��ȣ�� -i���� ���� ��� �� �����(?) ���� �� �ִٴ� �ǹ� -> i�� true�� ��
			scc_index[STD + i] < scc_index[STD - i] ? cout << "1 " : cout << "0 ";

	return 0;
}