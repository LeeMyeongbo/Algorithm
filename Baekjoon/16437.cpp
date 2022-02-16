#include <iostream>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, edge[123500], parent[123500];		// edge[i] : i번 정점으로 향하는 진입 간선 수, parent[i] : i번 정점의 부모 정점
long long node[123500];						// int 형 범위 넘어설 수 있음
char c;
queue<int> q;

long long Solve()
{
	for (int i = 1; i <= N; i++)
		if (!edge[i])
			q.push(i);						// 위상 정렬 방식 (bottom-up)
	
	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		edge[parent[cur]]--;
		node[parent[cur]] = node[cur] >= 0 ? node[parent[cur]] + node[cur] : node[parent[cur]];
		if (!edge[parent[cur]])
			q.push(parent[cur]);
	}
	if (node[1] < 0)
		return 0;

	return node[1];
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 2; i <= N; i++) {
		cin >> c >> node[i] >> parent[i];
		if (c == 'W')
			node[i] *= -1;						// 늑대 수만큼 양 수가 줄어드므로 음수로 저장
		edge[parent[i]]++;
	}

	cout << Solve();
	return 0;
}