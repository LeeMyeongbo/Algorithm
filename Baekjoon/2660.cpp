#include <iostream>
#include <vector>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, v1, v2, depth[51], Score = 100;
vector<int> graph[51], ans;
queue<pair<int, int>> q;

int BFS(int cur)
{
	int Max = 0;
	bool visited[51] = { false, };

	visited[cur] = true;
	q.push({ cur, 0 });
	
	while (!q.empty()) {
		int cur = q.front().first;
		int num = q.front().second;
		q.pop();

		Max = max(Max, num);
		for (int i : graph[cur]) {
			if (!visited[i]) {
				visited[i] = true;
				q.push({ i, num + 1 });
			}
		}
	}
	return Max;
}

int main()
{
	FAST;
	cin >> N;
	while (1) {
		cin >> v1 >> v2;
		if (v1 == -1)
			break;
		graph[v1].push_back(v2);			// 항상 연결 그래프로 주어짐! (모든 정점끼리 방문 가능)
		graph[v2].push_back(v1);
	}
	for (int v = 1; v <= N; v++) {
		depth[v] = BFS(v);
		Score = min(Score, depth[v]);
	}

	cout << Score << " ";
	for (int i = 1; i <= N; i++)
		if (depth[i] == Score)
			ans.push_back(i);
	cout << ans.size() << "\n";
	for (int i : ans)
		cout << i << " ";

	return 0;
}