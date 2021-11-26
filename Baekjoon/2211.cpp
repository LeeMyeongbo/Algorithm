#include <iostream>
#include <vector>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, A, B, C, dijkstra[1001], pre[1001], cnt;		// pre[i] : i번 정점 이전에 어떤 정점을 겨쳤었는지 저장
vector<pair<int, int>> graph[1001], ans;
priority_queue<int, vector<int>, greater<int>> q;

void Solve()
{
	fill(dijkstra, dijkstra + N + 1, -1);
	dijkstra[1] = 0;
	q.push(1);

	while (!q.empty()) {
		int cur = q.top();
		q.pop();

		for (auto p : graph[cur]) {
			if (dijkstra[p.second] == -1 || dijkstra[p.second] > dijkstra[cur] + p.first) {
				pre[p.second] = cur;
				dijkstra[p.second] = dijkstra[cur] + p.first;
				q.push(p.second);
			}
		}
	}
	for (int i = 1; i <= N; i++) {
		if (pre[i]) {				// i번 이전 정점이 존재하면 그 간선을 저장
			cnt++;
			ans.push_back({ pre[i], i });
		}
	}
	cout << cnt << "\n";
	for (auto p : ans)
		cout << p.first << " " << p.second << "\n";
}

int main()
{
	FAST;
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		cin >> A >> B >> C;
		graph[A].push_back({ C, B });
		graph[B].push_back({ C, A });		// (가중치, 정점) 형태로 저장
	}
	
	Solve();
	return 0;
}