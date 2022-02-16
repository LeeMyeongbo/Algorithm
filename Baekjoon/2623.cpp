#include <iostream>
#include <vector>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, K, pre, cur, edge[1001];
vector<int> graph[1001], ans;
queue<int> q;

void Solve()
{
	for (int i = 1; i <= N; i++)
		if (!edge[i])
			q.push(i);

	while (!q.empty()) {
		int cur = q.front();
		ans.push_back(cur);
		q.pop();

		for (int i : graph[cur]) {
			edge[i]--;
			if (!edge[i])
				q.push(i);
		}
	}

	if (ans.size() == N)			// 그래프에 사이클이 존재하여 위상 정렬을 통해 모든 정점이 정렬되지 못한 경우
		for (int i : ans)
			cout << i << "\n";
	else
		cout << 0;
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> K >> pre;
		for (int j = 1; j < K; j++) {
			cin >> cur;
			graph[pre].push_back(cur);
			edge[cur]++;
			pre = cur;
		}
	}

	Solve();
	return 0;
}