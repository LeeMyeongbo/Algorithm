#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int N, graph[50][50], order, seq[50], scc_num, scc_index[50];
bool visited[150001], complete[50];
vector<int> edge;
stack<int> s;

int dfs(int cur, int& from, int& to)
{
	seq[cur] = ++order;
	int parent = order;
	s.push(cur);

	for (int i = 0; i < N; i++) {
		if (i != cur && graph[cur][i] >= from && graph[cur][i] <= to) {
			if (!seq[i])
				parent = min(parent, dfs(i, from, to));
			else if (!complete[i])
				parent = min(parent, seq[i]);
		}
	}
	if (parent == seq[cur]) {
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
	return parent;
}

bool determine(int& from, int& to)
{
	for (int i = 0; i < N; i++)
		if (!complete[i])
			dfs(i, from, to);		// ��� ������ ���� scc Ž��

	for (int i = 0; i < N; i++)		// ��� �� ���� ���� ����� ��ΰ� �־�� �ϹǷ�
		if (scc_index[i] != 1)		// �׷��� �� ��� ������ ���� scc�� ������ ���� ��� false
			return false;
	return true;
}

int Solve()							// �������͸� �̿�
{
	int left = 0, right = 0, Min = 150001;
	while (left <= right) {
		if (right == edge.size())	
			break;
		if (determine(edge[left], edge[right])) {
			Min = min(Min, edge[right] - edge[left]);
			left++;
		}
		else
			right++;
		order = scc_num = 0;
		fill(seq, seq + N, 0);
		fill(scc_index, scc_index + N, 0);
		fill(complete, complete + N, false);
	}
	return Min;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			cin >> graph[i][j];
			if (!visited[graph[i][j]]) {			// �ڱ� �ڽ����� ���� self loop�� �� �־���� ��!
				visited[graph[i][j]] = true;
				edge.push_back(graph[i][j]);
			}
		}

	sort(edge.begin(), edge.end());
	cout << Solve();

	return 0;
}