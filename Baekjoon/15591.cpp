#include <iostream>
#include <vector>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, Q, p, q, r, k, graph, ans[5001], parent[5001], num[5001];
vector<pair<int, pair<int, int>>> edges;						// (usado, (p, q)) 로 저장
vector<pair<pair<int, int>, int>> query;						// ((k, v), 쿼리 번호) 로 저장

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
	num[n1] += num[n2];
}

void solve()
{
	for (auto& q : query) {									// 쿼리들을 앞에서부터 하나씩 살피면서
		while (!edges.empty() && edges.back().first >= q.first.first) {		// 간선은 뒤에서부터 USADO r이 현 쿼리의 k 이상을 만족하면
			Union(edges.back().second.first, edges.back().second.second);	// 유니온 파인드를 통해 p와 q를 합침
			edges.pop_back();												// 합친 간선은 삭제하고 다시 반복
		}
		ans[q.second] = num[Find(q.first.second)] - 1;		// 현 쿼리의 번호에 해당하는 답 = 현재까지 v에 연결된 정점들의 개수
	}
}

int main()
{
	FAST;
	cin >> N >> Q;
	for (int i = 1; i <= N; i++)
		parent[i] = i;
	fill(num, num + N + 1, 1);

	for (int i = 0; i < N - 1; i++) {
		cin >> p >> q >> r;
		edges.push_back({ r, {p, q} });
	}
	sort(edges.begin(), edges.end());			// 간선들을 USADO r 오름차순으로 정렬

	for (int i = 0; i < Q; i++) {				// 오프라인 쿼리를 이용 (쿼리 순으로 BFS 이용해서 해결 시 O(NQ) -> TLE!)
		cin >> k >> graph;
		query.push_back({ {k, graph}, i });
	}
	sort(query.begin(), query.end(), greater<pair<pair<int, int>, int>>());		// 쿼리들을 k 내림차순으로 정렬

	solve();
	for (int i = 0; i < Q; i++)
		cout << ans[i] << "\n";

	return 0;
}