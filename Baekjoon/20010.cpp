#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N, K, a, b, c, parent[1000], farthest, ans1, ans2;
bool visited[1000];
vector<pair<int, pair<int, int>>> edges;			// (가중치, (v1, v2))로 저장
vector<pair<int, int>> graph[1000];					// (연결된 정점, 가중치)로 저장
queue<pair<int, int>> q;							// (현재 정점, 가중치 합)으로 저장

int find(int v) 
{
	if (parent[v] == v)
		return v;
	return parent[v] = find(parent[v]);
}

bool Union(int v1, int v2)
{
	v1 = find(v1);
	v2 = find(v2);

	if (v1 == v2)
		return false;
	parent[v2] = v1;
	return true;
}

void BFS(int start)
{
	fill(visited, visited + N, false);
	q.push({ start, 0 });
	visited[start] = true;

	while (!q.empty()) {
		int cur = q.front().first;
		int sum = q.front().second;
		q.pop();

		if (ans2 < sum) {
			farthest = cur;
			ans2 = sum;
		}
		for (pair<int, int>& p : graph[cur]) {
			if (!visited[p.first]) {
				visited[p.first] = true;
				q.push({ p.first, sum + p.second });
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N >> K;
	for (int i = 0; i < N; i++)
		parent[i] = i;

	for (int i = 0; i < K; i++) {
		cin >> a >> b >> c;
		edges.push_back({ c, {min(a, b), max(a, b)} });
	}
	sort(edges.begin(), edges.end(), greater<pair<int, pair<int, int>>>());		// 간선들을 가중치 내림차순으로 정렬

	int connect = N - 1;
	while (connect) {									// 크루스칼 알고리즘
		auto e = edges.back();
		edges.pop_back();

		if (Union(e.second.first, e.second.second)) {
			ans1 += e.first;
			connect--;
			graph[e.second.first].push_back({ e.second.second, e.first });
			graph[e.second.second].push_back({ e.second.first, e.first });
		}
	}
	BFS(0);
	BFS(farthest);										// bfs 2번만 돌리면 바로 트리 지름 알 수 있음

	cout << ans1 << "\n" << ans2;
	return 0;
}