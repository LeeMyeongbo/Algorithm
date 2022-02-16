#include <iostream>
#include <vector>
#define LOG 17
using namespace std;
																	 // parent[i][j] : i번 정점의 2^j번째 조상
int N, u, graph, w, M, k, query, depth[100001], parent[100001][LOG]; // depth[i] : i번 정점의 깊이(1부터 시작)
long long weight_sum[100001][LOG];									 // weight_sum[i][j] : i번 정점부터 2^j번째 조상까지의 가중치 합
vector<pair<int, int>> tree[100001];

void make_Tree(int d, int pre, int cur, int weight)
{
	depth[cur] = d;
	parent[cur][0] = pre;
	weight_sum[cur][0] = weight;

	for (auto& p : tree[cur])
		if (!depth[p.first])
			make_Tree(d + 1, cur, p.first, p.second);
}

void get()
{
	for (int j = 1; j < LOG; j++)
		for (int i = 1; i <= N; i++) {
			parent[i][j] = parent[parent[i][j - 1]][j - 1];
			weight_sum[i][j] = weight_sum[i][j - 1] + weight_sum[parent[i][j - 1]][j - 1];
		}
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

	for (int i = LOG - 1; i >= 0; i--)
		if (parent[x][i] != parent[y][i]) {
			x = parent[x][i];
			y = parent[y][i];
		}

	return parent[x][0];
}

long long get_sum(int lca)
{
	long long sum = 0;
	int gap_u = depth[u] - depth[lca];
	int gap_v = depth[graph] - depth[lca];

	for (int i = 0; gap_u; i++) {
		if (gap_u % 2) {
			sum += weight_sum[u][i];
			u = parent[u][i];
		}
		gap_u /= 2;
	}
	for (int i = 0; gap_v; i++) {
		if (gap_v % 2) {
			sum += weight_sum[graph][i];
			graph = parent[graph][i];
		}
		gap_v /= 2;
	}
	return sum;
}

int get_kth(int lca)
{
	int u_anc = depth[u] - depth[lca] + 1;	// lca가 u로부터 몇 번째인지
	int v_anc = depth[graph] - depth[lca] + 1;	// lca가 v로부터 몇 번째인지

	if (k > u_anc) {						// k번째가 lca와 v 사이에 있을 경우
		int get = u_anc + v_anc - k - 1;
		for (int i = 0; get; i++) {
			if (get % 2)
				graph = parent[graph][i];
			get /= 2;
		}
		return graph;
	}
	else {									// k번째가 u와 lca 사이에 있을 경우
		int get = k - 1;
		for (int i = 0; get; i++) {
			if (get % 2)
				u = parent[u][i];
			get /= 2;
		}
		return u;
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N;
	for (int i = 0; i < N - 1; i++) {
		cin >> u >> graph >> w;
		tree[u].push_back({ graph, w });
		tree[graph].push_back({ u, w });
	}
	make_Tree(1, 0, 1, 0);
	get();
	
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> query >> u >> graph;
		if (query == 2)
			cin >> k;
		int lca = LCA(u, graph);
		if (query == 1)
			cout << get_sum(lca) << "\n";
		else
			cout << get_kth(lca) << "\n";
	}
	return 0;
}
