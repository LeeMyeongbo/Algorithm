#include <iostream>
#include <vector>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int V, E, v1, v2, visited[100001], num;
vector<int> graph[100001];
vector<pair<int, int>> ans;

int dfs(int cur, int parent)
{
	visited[cur] = ++num;
	int seq = num;

	for (int& i : graph[cur]) {
		if (i == parent)						// �θ� ���� skip
			continue;
		else if (visited[i])					// �θ� ��尡 �ƴѵ� �湮�� �� �ִ� ���� �߿����� �湮 ������ ���� ���� ������ seq ����
			seq = min(seq, visited[i]);
		else {									// �湮�� �� ���� ����� ��� �ش� ��尡 �湮�� �� �ִ� �ּ� �湮 ������ ���� ���ϰ�
			int pre = dfs(i, cur);				// �װ� �� ����(cur)�� �湮 �������� ũ�ٸ� cur�� �ش� ��� ������ ������ �������� ��
			if (pre > visited[cur])
				ans.push_back({ min(i, cur), max(i, cur) });

			seq = min(seq, pre);				// seq �ּڰ� ����
		}
	}
	return seq;
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
			dfs(i, 0);
	sort(ans.begin(), ans.end());

	cout << ans.size() << "\n";
	for (auto& p : ans)
		cout << p.first << " " << p.second << "\n";
	return 0;
}