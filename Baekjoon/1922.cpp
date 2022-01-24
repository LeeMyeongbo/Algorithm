#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M, a, b, c, Ans, idx, U[1001];
vector<pair<int, pair<int, int>>> edges;		// (����ġ(=���), (���� 1, ���� 2))�� ����

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
	sort(edges.begin(), edges.end());							// ������ ��� ������������ ����
	
	for (pair<int, pair<int, int>>& e : edges) {
		if (Find(e.second.first) != Find(e.second.second)) {	// ���� �� ������ ����Ǿ� ���� �ʴٸ�
			Union(e.second.first, e.second.second);				// �����ϰ�
			idx++, Ans += e.first;								// ��� �߰�
		}
		if (idx == N - 1)
			break;												// ���� N - 1�� ���� �� MST ���� �Ϸ�!
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