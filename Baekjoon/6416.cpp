#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int u, v, k, indegree[101];
bool node[101];
vector<int> tree[101];

bool BFS(int root)							// ��Ʈ�κ��� ��� ���� �湮 �������� üũ
{
	bool visited[101] = { false, };
	queue<int> q;

	q.push(root);
	visited[root] = true;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (int i : tree[cur]) {
			if (!visited[i]) {
				visited[i] = true;
				q.push(i);
			}
		}
	}
	for (int i = 1; i <= 100; i++)
		if (!visited[i] && node[i])
			return false;
	return true;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	while (true) {
		while (true) {
			cin >> u >> v;
			if (u < 0 && v < 0)
				return 0;

			if (!u && !v)
				break;

			indegree[v]++;
			node[u] = true;
			node[v] = true;
			tree[u].push_back(v);
		}
		
		int root = 0, rootnum = 0, edges = 0, vertex = 0;		// ���� ��Ʈ ���, ��Ʈ ����, ���� ����, ���� ����
		bool flag = false;

		for (int i = 1; i <= 100; i++) {
			if (node[i]) {
				vertex++;										// ���� ���� üũ
				if (!indegree[i])
					root = i, rootnum++;						// ���԰����� ���� ��� = ��Ʈ
			}
			if (indegree[i] > 1) {								// ���԰����� 2�� �̻��̸� Ʈ�� �ƴ�
				flag = true;
				break;
			}
			else if (indegree[i] == 1)
				edges++;
		}
		
		if (vertex && (rootnum != 1 || edges != vertex - 1))	// ������ 0�� �̻��ε� ��Ʈ�� �ϳ��� �ƴϰų� ���� ���� - 1 != ���� �����̸� Ʈ�� �ƴ�
			flag = true;
		
		if (!flag && BFS(root))
			cout << "Case " << ++k << " is a tree.\n";
		else
			cout << "Case " << ++k << " is not a tree.\n";

		fill(indegree, indegree + 101, 0);
		fill(node, node + 101, false);
		for (int i = 1; i <= 100; i++)
			tree[i].clear();
	}
}