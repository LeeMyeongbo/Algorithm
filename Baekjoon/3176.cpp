#include <iostream>
#include <vector>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define MAX 17
using namespace std;

int N, a, b, c, K, d, e;
int depth[100001];				// depth[i] : 정점 i의 깊이 (정점 1을 1로 둠)
int parent[100001][MAX];		// parent[i][j] : 정점 i의 2^j번째 조상
int Max_weight[100001][MAX];	// Max_weight[i][j] : i에서 i의 2^j번째 조상까지의 도로들 중 최대 길이 저장
int Min_weight[100001][MAX];	// Min_weight[i][j] : i에서 i의 2^j번째 조상까지의 도로들 중 최소 길이 저장
vector<pair<int, int>> tree[100001];

void dfs(int d, int cur, int par, int length)
{
	depth[cur] = d;
	parent[cur][0] = par;
	Min_weight[cur][0] = Max_weight[cur][0] = length;

	for (auto& p : tree[cur])
		if (!depth[p.first])
			dfs(d + 1, p.first, cur, p.second);
}

void set_Parent()			// 2^1부터 2^(MAX-1)번째 조상까지 저장 + 최대,최소 길이 갱신
{
	dfs(1, 1, 0, 0);

	for (int j = 1; j < MAX; j++)
		for (int i = 1; i <= N; i++) {
			parent[i][j] = parent[parent[i][j - 1]][j - 1];
			Min_weight[i][j] = min(Min_weight[i][j - 1], Min_weight[parent[i][j - 1]][j - 1]);
			Max_weight[i][j] = max(Max_weight[i][j - 1], Max_weight[parent[i][j - 1]][j - 1]);
		}
}

void Solve()
{
	int Min = 1000001, Max = 0;
	if (depth[d] < depth[e])			// d의 깊이를 더 깊게 설정
		swap(d, e);

	int gap = depth[d] - depth[e];
	for (int i = 0; gap; i++) {
		if (gap % 2) {
			Min = min(Min, Min_weight[d][i]);
			Max = max(Max, Max_weight[d][i]);
			d = parent[d][i];
		}
		gap /= 2;
	}
	if (d == e) {
		cout << Min << " " << Max << "\n";
		return;
	}
	for (int i = MAX - 1; i >= 0; i--)
		if (parent[d][i] != parent[e][i]) {
			Min = min(Min, min(Min_weight[d][i], Min_weight[e][i]));
			Max = max(Max, max(Max_weight[d][i], Max_weight[e][i]));
			d = parent[d][i];
			e = parent[e][i];
		}
	Min = min(Min, min(Min_weight[d][0], Min_weight[e][0]));
	Max = max(Max, min(Max_weight[d][0], Max_weight[e][0]));

	cout << Min << " " << Max << "\n";
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 1; i <= N; i++)
		fill(Min_weight[i], Min_weight[i] + MAX, 1000001);

	for (int i = 0; i < N - 1; i++) {
		cin >> a >> b >> c;
		tree[a].push_back({ b, c });
		tree[b].push_back({ a, c });
	}
	set_Parent();

	cin >> K;
	for (int i = 0; i < K; i++) {
		cin >> d >> e;
		Solve();
	}
	return 0;
}