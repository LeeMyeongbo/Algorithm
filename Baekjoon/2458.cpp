#include <iostream>
#include <vector>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, a, b, num[501], ans;
vector<int> graph[501], reversed_graph[501];
bool visited[501];

void dfs(int cur, int init, vector<int> g[]) 
{
	num[init]++;
	visited[cur] = true;
	for (int i : g[cur])
		if (!visited[i])
			dfs(i, init, g);
}

int Solve()
{
	for (int i = 1; i <= N; i++) {
		dfs(i, i, graph);					// �� �������� ���������� DFS �����ϸ� �湮�� ���� �� ���� (Ű ū ��� ��)
		dfs(i, i, reversed_graph);			// �� �������� ���������� DFS �����ϸ� �湮�� ���� �� ���� (Ű ���� ��� ��)

		if (num[i] == N + 1)				// ��� ���� �湮�ߴٸ�(�� ���� ������ ��� �������� Ű�� ũ�ų� �۴ٴ� ���� Ȯ���ϴٸ�)
			ans++;							// �ڽ��� Ű�� �� ��°���� �� �� ����
		fill(visited, visited + N + 1, false);
	}

	return ans;
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		graph[a].push_back(b);
		reversed_graph[b].push_back(a);
	}

	cout << Solve();
	return 0;
}