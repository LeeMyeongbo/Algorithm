#include <iostream>
#include <vector>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, A, B, edge[32001];
vector<int> graph[32001];
queue<int> q;

void solve()
{
	for (int i = 1; i <= N; i++)
		if (!edge[i])
			q.push(i);

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		cout << cur << " ";
		for (int i : graph[cur]) {
			edge[i]--;
			if (!edge[i])
				q.push(i);
		}
	}
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> A >> B;
		graph[A].push_back(B);
		edge[B]++;
	}

	solve();
	return 0;
}