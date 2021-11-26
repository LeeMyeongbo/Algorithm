#include <iostream>
#include <vector>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define MAX 14
using namespace std;

int T, N, v1, v2, x, y, Root, depth[10001], parent[10001][MAX];
bool not_root[10001];
vector<int> tree[10001];

void make_Tree(int d, int cur, int par)
{
	depth[cur] = d;
	parent[cur][0] = par;

	for (int& i : tree[cur])
		if (!depth[i])
			make_Tree(d + 1, i, cur);
}

void set_Parent()
{
	make_Tree(1, Root, 0);

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

	for(int i = MAX - 1; i >= 0; i--)
		if (parent[x][i] != parent[y][i]) {
			x = parent[x][i];
			y = parent[y][i];
		}
	return parent[x][0];
}

int main()
{
	FAST;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N;
		for (int i = 0; i < N - 1; i++) {
			cin >> v1 >> v2;
			not_root[v2] = true;
			tree[v1].push_back(v2);
			tree[v2].push_back(v1);
		}
		for(int i = 1; i <= N; i++)
			if (!not_root[i]) {
				Root = i;
				break;
			}
		set_Parent();

		cin >> x >> y;
		cout << LCA() << "\n";

		fill(depth, depth + N + 1, 0);
		fill(not_root, not_root + N + 1, false);
		for (int i = 1; i <= N; i++) {
			fill(parent[i], parent[i] + MAX, 0);
			tree[i].clear();
		}
	}
	return 0;
}