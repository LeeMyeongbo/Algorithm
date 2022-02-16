#include <iostream>
#include <vector>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int p, w, c, graph, v1, v2, width, parent[1000];
vector<pair<int, pair<int, int>>> edges;

int Find(int n)
{
	if (parent[n] == n)
		return n;
	return parent[n] = Find(parent[n]);
}

void Union(int n1, int n2) 
{
	n1 = Find(n1);
	n2 = Find(n2);
	if (n1 == n2)
		return;
	if (n1 > n2)
		swap(n1, n2);
	parent[n2] = n1;
}

int Solve()
{
	for (auto& e : edges) {
		Union(e.second.first, e.second.second);		// 간선 가중치가 가장 큰 것부터 차례대로 연결
		if (Find(c) == Find(graph))					// 그러다가 c와 v가 연결되었을 때 추가한 간선의 가중치 리턴
			return e.first;
	}
	return -1;
}

int main()
{
	FAST;
	cin >> p >> w >> c >> graph;
	for (int i = 0; i < p; i++)
		parent[i] = i;

	for (int i = 0; i < w; i++) {
		cin >> v1 >> v2 >> width;
		edges.push_back({ width, {v1, v2} });
	}
	sort(edges.begin(), edges.end(), greater<pair<int, pair<int, int>>>());
	
	cout << Solve();
	return 0;
}
