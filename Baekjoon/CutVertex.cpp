#include <iostream>
#include <vector>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int V, E, v1, v2, num, visited[10001];
vector<int> graph[10001], ans;
bool isCutVertex[10001];

int dfs(int cur, bool Root)
{
	visited[cur] = ++num;
	int order = visited[cur];					// �� ó���� order�� ���� ����� �湮 ������ �ʱ�ȭ
	int child = 0;								// �� ����� �ڽ� ��� ��

	for (int i : graph[cur]) {
		if (visited[i])							// �̹� �湮�� ����� ���
			order = min(order, visited[i]);		// ���� �湮 ������ ���� ������ order ����
		else {									// ���� �湮�� �� ���� �����
			child++;							// �װ� �ٷ� �ڽ� ���
			int pre = dfs(i, false);			// �ش� �ڽ� ���� ����� ������ �湮 ���� �� �ּڰ��� pre�� ����

			if (!Root && pre >= visited[cur])	// pre���� �� ����� �湮 �������� ���� �ʴٸ� ���� ������ �������� ��
				isCutVertex[cur] = true;
			order = min(order, pre);			// order �ּڰ� ����
		}
	}
	if (Root && child >= 2)						// �� ������ ��Ʈ�� ��쿣 �ڽ��� �� �̻� �Ǹ� ������ ������
		isCutVertex[cur] = true;

	return order;
}

int main()
{
	FAST;
	cin >> V >> E;
	for (int e = 0; e < E; e++) {
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}
	for (int i = 1; i <= V; i++)
		if (!visited[i])
			dfs(i, true);
	
	for (int i = 1; i <= V; i++)
		if (isCutVertex[i])
			ans.push_back(i);

	cout << ans.size() << "\n";
	for (int i : ans)
		cout << i << " ";
	return 0;
}