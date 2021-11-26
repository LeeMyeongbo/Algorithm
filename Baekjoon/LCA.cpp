#include <iostream>
#include <vector>
#include <cmath>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, v1, v2, n1, n2, parent[50001][16], depth[50001], n;		// parent[i][k] : i�� 2^k��° �θ�
vector<int> tree[50001];

void dfs(int d, int cur, int par)				// �� �������� �ٷ� ��(2^0��°) �θ� �� ���� ����
{
	parent[cur][0] = par;
	depth[cur] = d;

	for (int& i : tree[cur]) {
		if (!depth[i])
			dfs(d + 1, i, cur);
	}
}

void set_Parent()
{
	for (int j = 1; j < n; j++)					// 2^1��° ����, 2^2��° ���� ������ 
		for (int i = 1; i <= N; i++)			// 1������ N������ �ݺ�
			parent[i][j] = parent[parent[i][j - 1]][j - 1];
}

int LCA()
{
	if (depth[n1] < depth[n2])					// n1�� ���̰� �� ���� ����
		swap(n1, n2);

	int diff = depth[n1] - depth[n2];
	for(int i = 0; diff; i++) {					// n1�� ���̰� n2�� ���� ������ ���� �÷��� ����
		if (diff % 2)
			n1 = parent[n1][i];
		diff /= 2;
	}

	if (n1 == n2)
		return n1;
	for (int i = n - 1; i >= 0; i--) {			// �ֻ�� ���κ��� ������ �������� ������ 2^i�� �̵�
		if (parent[n1][i] != parent[n2][i]) {
			n1 = parent[n1][i];
			n2 = parent[n2][i];
		}
	}
	return parent[n1][0];
}

int main()
{
	FAST;
	cin >> N;
	n = (int)log2(N) + 1;
	for (int i = 0; i < N - 1; i++) {
		cin >> v1 >> v2;
		tree[v1].push_back(v2);
		tree[v2].push_back(v1);
	}
	dfs(1, 1, 0);
	set_Parent();
	
	cin >> M;
	while (M--) {
		cin >> n1 >> n2;
		cout << LCA() << "\n";
	}
	return 0;
}