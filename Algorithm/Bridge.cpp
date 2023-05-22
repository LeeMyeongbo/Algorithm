#include <iostream>
#include <vector>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int V, E, v1, v2, visited[100001], num;
vector<int> graph[100001];
vector<pair<int, int>> ans;

int dfs(int cur, int parent)
{
	visited[cur] = ++num;
	int seq = num;

	for (int& i : graph[cur]) 
    {
		if (i == parent)						// 부모 노드는 skip
			continue;
		else if (visited[i])					// 부모 노드가 아닌데 방문한 적 있는 노드들 중에서는 방문 순서가 가장 작은 값으로 seq 갱신
			seq = min(seq, visited[i]);
		else                                    // 방문한 적 없는 노드의 경우 해당 노드가 방문할 수 있는 최소 방문 순서의 정점 구하고
        {
			int pre = dfs(i, cur);				// 그게 현 정점(cur)의 방문 순서보다 크다면 cur과 해당 노드 사이의 간선이 단절선이 됨
			if (pre > visited[cur])
				ans.push_back({ min(i, cur), max(i, cur) });

			seq = min(seq, pre);				// seq 최솟값 갱신
		}
	}

	return seq;
}

int main()
{
	FAST;
	cin >> V >> E;
	for (int e = 0; e < E; e++) 
    {
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}

	for (int i = 1; i <= V; i++)
		if (!visited[i])
			dfs(i, 0);

	sort(ans.begin(), ans.end());

	cout << ans.size() << "\n";
	for (auto& p : ans)
		cout << p.first << " " << p.second << "\n";

	return 0;
}
