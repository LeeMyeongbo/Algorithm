#include <iostream>
#include <vector>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define MAX 16
using namespace std;

int N, M, v1, v2, w, x, y, depth[40001], parent[40001][MAX], dest[40001];
vector<pair<int, int>> tree[40001];

void dfs(int d, int cur, int par, int dist)
{
	depth[cur] = d;
	parent[cur][0] = par;
	dest[cur] = dist;

	for (auto& p : tree[cur])
		if (!depth[p.first])
			dfs(d + 1, p.first, cur, dist + p.second);
}

void set_Parent()
{
	dfs(1, 1, 0, 0);
	for (int j = 1; j < MAX; j++)
		for (int i = 1; i <= N; i++)
			parent[i][j] = parent[parent[i][j - 1]][j - 1];
}

int get_Distance()
{
	int ans = 0;

	if (depth[x] < depth[y])
		swap(x, y);

	int gap = depth[x] - depth[y];
	for (int i = 0; gap; i++) {
		if (gap % 2) {
			ans += dest[x] - dest[parent[x][i]];
			x = parent[x][i];
		}
		gap /= 2;
	}
	if (x == y)
		return ans;

	for (int i = MAX - 1; i >= 0; i--)
		if (parent[x][i] != parent[y][i]) {
			ans += dest[x] - dest[parent[x][i]] + dest[y] - dest[parent[y][i]];
			x = parent[x][i];
			y = parent[y][i];
		}
	
	return ans + dest[x] - dest[parent[x][0]] + dest[y] - dest[parent[y][0]];
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 0; i < N - 1; i++) {
		cin >> v1 >> v2 >> w;
		tree[v1].push_back({ v2, w });
		tree[v2].push_back({ v1, w });
	}
	set_Parent();

	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> x >> y;
		cout << get_Distance() << "\n";
	}
	return 0;
}