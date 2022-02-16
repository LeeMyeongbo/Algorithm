#include <iostream>
#include <vector>
#define MAX 17
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, n, v1, v2, parent[100001][MAX], depth[100001], x, y;
vector<int> tree[100001];

void dfs(int d, int cur, int pre)
{
	parent[cur][0] = pre;
	depth[cur] = d;

	for (int& i : tree[cur])
		if (!depth[i])
			dfs(d + 1, i, cur);
}

void set_Parent()
{
	dfs(1, 1, 0);
	for (int j = 1; j < MAX; j++)
		for (int i = 1; i <= N; i++)
			parent[i][j] = parent[parent[i][j - 1]][j - 1];
}

int LCA()
{
	if (depth[x] < depth[y])
		swap(x, y);

	int gap = depth[x] - depth[y];
	for (int i = 0; gap; i++) {
		if (gap % 2)
			x = parent[x][i];
		gap /= 2;
	}
	if (x == y)
		return x;

	for (int i = MAX - 1; i >= 0; i--)
		if (parent[x][i] != parent[y][i]) {
			x = parent[x][i];
			y = parent[y][i];
		}

	return parent[x][0];
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 0; i < N - 1; i++) {
		cin >> v1 >> v2;
		tree[v1].push_back(v2);
		tree[v2].push_back(v1);
	}
	set_Parent();

	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> x >> y;
		cout << LCA() << "\n";
	}
	return 0;
}