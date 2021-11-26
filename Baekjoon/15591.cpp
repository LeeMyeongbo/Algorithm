#include <iostream>
#include <vector>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, Q, p, q, r, k, graph, ans[5001], parent[5001], num[5001];
vector<pair<int, pair<int, int>>> edges;						// (usado, (p, q)) �� ����
vector<pair<pair<int, int>, int>> query;						// ((k, v), ���� ��ȣ) �� ����

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
	for (auto& q : query) {									// �������� �տ������� �ϳ��� ���Ǹ鼭
		while (!edges.empty() && edges.back().first >= q.first.first) {		// ������ �ڿ������� USADO r�� �� ������ k �̻��� �����ϸ�
			Union(edges.back().second.first, edges.back().second.second);	// ���Ͽ� ���ε带 ���� p�� q�� ��ħ
			edges.pop_back();												// ��ģ ������ �����ϰ� �ٽ� �ݺ�
		}
		ans[q.second] = num[Find(q.first.second)] - 1;		// �� ������ ��ȣ�� �ش��ϴ� �� = ������� v�� ����� �������� ����
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
	sort(edges.begin(), edges.end());			// �������� USADO r ������������ ����

	for (int i = 0; i < Q; i++) {				// �������� ������ �̿� (���� ������ BFS �̿��ؼ� �ذ� �� O(NQ) -> TLE!)
		cin >> k >> graph;
		query.push_back({ {k, graph}, i });
	}
	sort(query.begin(), query.end(), greater<pair<pair<int, int>, int>>());		// �������� k ������������ ����

	solve();
	for (int i = 0; i < Q; i++)
		cout << ans[i] << "\n";

	return 0;
}