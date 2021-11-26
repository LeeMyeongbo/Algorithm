#include <iostream>
#include <vector>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define MAX 17
using namespace std;

int n, a, b, c, ant[100001], energy[100001], parent[100001][MAX];
bool visited[100001];
vector<pair<int, int>> tree[100001];

void dfs(int cur, int pre, int E)			// �� ������ ù ��° ����� 1�������� ��� ���� �� ����
{
	visited[cur] = true;
	parent[cur][0] = pre;
	energy[cur] = E;

	for (auto& p : tree[cur])
		if (!visited[p.first])
			dfs(p.first, cur, E + p.second);
}

void set_Parent()							// �� ������ 2^1���� 2^16��°�� ���� ����
{
	dfs(1, 0, 0);
	for (int j = 1; j < MAX; j++)
		for (int i = 1; i <= n; i++)
			parent[i][j] = parent[parent[i][j - 1]][j - 1];
}

void Solve()
{
	for (int i = 1; i <= n; i++) {					// 1�� ���̺��� n�� ���̱���
		int cur = i;
		for (int j = MAX - 1; j >= 0; j--) {
			// �� ������ 2^j ��°�� ������ �����ϸ鼭 �ش� ���������� �ű������ ��� ���̰� ���� ������ ���� �������� ������ ���
			if (parent[cur][j] && energy[cur] - energy[parent[cur][j]] <= ant[i]) { 
				ant[i] -= energy[cur] - energy[parent[cur][j]];		// �ű������ ��� ���̸�ŭ ������ ����
				cur = parent[cur][j];								// �ű�� �̵�
			}
		}
		cout << cur << "\n";
	}
}

int main()
{
	FAST;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> ant[i];

	for (int i = 0; i < n - 1; i++) {
		cin >> a >> b >> c;
		tree[a].push_back({ b, c });
		tree[b].push_back({ a, c });
	}
	set_Parent();

	Solve();
	return 0;
}