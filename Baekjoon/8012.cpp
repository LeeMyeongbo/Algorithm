#include <iostream>
#include <vector>
#define LOG 15
using namespace std;

int n, u, graph, m, city[5000], depth[30001], parent[30001][LOG], ans;
vector<int> tree[30001];

void make_Tree(int d, int pre, int cur)
{
	depth[cur] = d;
	parent[cur][0] = pre;

	for (int& i : tree[cur])
		if (!depth[i])
			make_Tree(d + 1, cur, i);
}

int LCA(int x, int y) 
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

	for(int i = LOG - 1; i >= 0; i--)
		if (parent[x][i] != parent[y][i]) {
			x = parent[x][i];
			y = parent[y][i];
		}
	return parent[x][0];
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		cin >> u >> graph;
		tree[u].push_back(graph);
		tree[graph].push_back(u);
	}
	make_Tree(1, 0, 1);
	for (int j = 1; j < LOG; j++)
		for (int i = 1; i <= n; i++)
			parent[i][j] = parent[parent[i][j - 1]][j - 1];

	cin >> m;
	for (int i = 0; i < m; i++)
		cin >> city[i];

	for (int i = 0; i < m - 1; i++) {
		int lca = LCA(city[i], city[i + 1]);
		if (!i)
			ans += depth[lca] - 1;				// 맨 처음에는 무적권 1번에서부터 여행 시작
		ans += depth[city[i]] - depth[lca] + depth[city[i + 1]] - depth[lca];	// 두 도시에서 lca까지의 거리를 더해가면 됨
	}

	cout << ans;
	return 0;
}