#include <iostream>
#include <vector>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, v1, v2, parent[100001];		// 2번 정점부터 N번 정점까지 부모 정점 번호 저장 (1번은 1로 저장)
vector<int> edges[100001];

void dfs(int cur, int par)
{
	parent[cur] = par;
	for (int i : edges[cur]) {
		if (!parent[i])
			dfs(i, cur);
	}
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 0; i < N - 1; i++) {
		cin >> v1 >> v2;
		edges[v1].push_back(v2);
		edges[v2].push_back(v1);
	}
	dfs(1, 1);
	for (int i = 2; i <= N; i++)
		cout << parent[i] << "\n";

	return 0;
}