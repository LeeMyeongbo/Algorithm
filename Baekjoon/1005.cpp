#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int T, N, K, X, Y, W, Time[1001], edge[1001], ans[1001];
vector<int> graph[1001];
queue<int> q;

int Solve()
{
	for (int i = 1; i <= N; i++)
		if (!edge[i]) {
			q.push(i);
			ans[i] = Time[i];
		}
	
	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (int i : graph[cur]) {
			edge[i]--;
			ans[i] = max(ans[i], ans[cur] + Time[i]);
			if (!edge[i])
				q.push(i);
		}
	}
	return ans[W];
}

int main()
{
	FAST;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N >> K;
		for (int n = 1; n <= N; n++)
			cin >> Time[n];
		for (int k = 0; k < K; k++) {
			cin >> X >> Y;
			graph[X].push_back(Y);
			edge[Y]++;
		}
		cin >> W;
		cout << Solve() << "\n";

		for (int i = 1; i <= N; i++)
			graph[i].clear();
		fill(ans, ans + N + 1, 0);
	}
	return 0;
}