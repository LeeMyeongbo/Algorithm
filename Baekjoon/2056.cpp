#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, Time[10001], num, V, edge[10001], ans[10001], Ans;
vector<int> graph[10001];
queue<int> q;

int Solve()
{
	for(int v = 1; v <= N; v++)
		if (!edge[v]) {
			ans[v] = Time[v];
			q.push(v);
		}

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		Ans = max(Ans, ans[cur]);
		for (int i : graph[cur]) {
			ans[i] = max(ans[i], ans[cur] + Time[i]);
			edge[i]--;
			if (!edge[i])
				q.push(i);
		}
	}
	return Ans;
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> Time[i] >> num;
		for (int j = 0; j < num; j++) {
			cin >> V;
			graph[V].push_back(i);
			edge[i]++;
		}
	}

	cout << Solve();
	return 0;
}