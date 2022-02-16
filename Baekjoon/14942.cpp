#include <iostream>
#include <vector>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define MAX 17
using namespace std;

int n, a, b, c, ant[100001], energy[100001], parent[100001][MAX];
bool visited[100001];
vector<pair<int, int>> tree[100001];

void dfs(int cur, int pre, int E)			// 각 정점의 첫 번째 조상과 1번까지의 통로 길이 합 저장
{
	visited[cur] = true;
	parent[cur][0] = pre;
	energy[cur] = E;

	for (auto& p : tree[cur])
		if (!visited[p.first])
			dfs(p.first, cur, E + p.second);
}

void set_Parent()							// 각 정점의 2^1부터 2^16번째의 조상 저장
{
	dfs(1, 0, 0);
	for (int j = 1; j < MAX; j++)
		for (int i = 1; i <= n; i++)
			parent[i][j] = parent[parent[i][j - 1]][j - 1];
}

void Solve()
{
	for (int i = 1; i <= n; i++) {					// 1번 개미부터 n번 개미까지
		int cur = i;
		for (int j = MAX - 1; j >= 0; j--) {
			// 현 정점의 2^j 번째의 조상이 존재하면서 해당 지점까지의 거기까지의 통로 길이가 현재 개미의 남은 에너지량 이하일 경우
			if (parent[cur][j] && energy[cur] - energy[parent[cur][j]] <= ant[i]) { 
				ant[i] -= energy[cur] - energy[parent[cur][j]];		// 거기까지의 통로 길이만큼 에너지 차감
				cur = parent[cur][j];								// 거기로 이동
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