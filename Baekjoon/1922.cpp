#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M, a, b, c, Ans, idx, U[1001];
vector<pair<int, pair<int, int>>> edges;		// (가중치(=비용), (정점 1, 정점 2))로 저장

int Find(int v)
{
	if (U[v] == v)
		return v;
	return U[v] = Find(U[v]);
}

void Union(int v1, int v2)
{
	v1 = Find(v1);
	v2 = Find(v2);
	U[v1] = v2;
}

int Kruskal()
{
	sort(edges.begin(), edges.end());							// 간선을 비용 오름차순으로 정렬
	
	for (pair<int, pair<int, int>>& e : edges) {
		if (Find(e.second.first) != Find(e.second.second)) {	// 만약 두 정점이 연결되어 있지 않다면
			Union(e.second.first, e.second.second);				// 연결하고
			idx++, Ans += e.first;								// 비용 추가
		}
		if (idx == N - 1)
			break;												// 간선 N - 1개 연결 시 MST 형성 완료!
	}

	return Ans;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;
	for (int i = 1; i <= N; i++)
		U[i] = i;

	while (M--) {
		cin >> a >> b >> c;
		edges.push_back({ c, {a, b} });
	}
	
	cout << Kruskal();
	return 0;
}