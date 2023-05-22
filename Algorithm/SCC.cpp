#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int V, E, a, b, order[10001], n;		// order[i] : i번 정점을 방문한 순서 저장
bool complete[10001];					// complete[i] : i번 정점 탐색이 완료되었는지 여부
vector<int> graph[10001];
vector<vector<int>> SCC;
stack<int> s;

int dfs(int cur)
{
	order[cur] = ++n;					// 현재 정점의 방문한 순서 저장
	int p = order[cur];
	s.push(cur);

	for (int i : graph[cur])            // p를 최솟값으로 갱신
    {
		if (!order[i])					// 아직 해당 정점을 방문하지 않았을 경우
			p = min(p, dfs(i));
		else if (!complete[i])			// 방문은 했는데 강결합 요소 탐색이 완료되지 않았을 경우
			p = min(p, order[i]);
	}

	if (p == order[cur]) 
    {
		vector<int> scc;
		while (!s.empty()) 
        {
			int v = s.top();
			s.pop();

			complete[v] = true;
			scc.push_back(v);

			if (order[v] == p)			// 자기 자신이 나올 때까지 반복해서 pop
				break;
		}

		sort(scc.begin(), scc.end());
		SCC.push_back(scc);
	}

	return p;
}

int main()
{
	FAST;
	cin >> V >> E;
	for (int e = 0; e < E; e++) 
    {
		cin >> a >> b;
		graph[a].push_back(b);
	}

	for (int i = 1; i <= V; i++)
		if (!complete[i])
			dfs(i);

	cout << SCC.size() << "\n";
	sort(SCC.begin(), SCC.end());

	for (auto& scc : SCC) 
    {
		for (int v : scc)
			cout << v << " ";
		cout << "\n";
	}

	return 0;
}
