#include <iostream>
#include <vector>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, map[200][200], C, M, parent[200];
vector<pair<int, pair<int, int>>> edges, ans;

int Find(int n)
{
	if (parent[n] == n)
		return n;
	return parent[n] = Find(parent[n]);
}

bool Union(int n1, int n2)
{
	n1 = Find(n1);
	n2 = Find(n2);
	if (n1 == n2)
		return false;

	if (n1 > n2)
		swap(n1, n2);
	parent[n2] = n1;
	return true;
}

void Solve()
{
	sort(edges.begin(), edges.end());

	for (auto& e : edges) {
		if (Union(e.second.first, e.second.second)) {
			C += e.first;
			M++;
			ans.push_back(e);
		}
	}

	cout << C << " " << M << "\n";
	for (auto& e : ans)
		cout << e.second.first + 1 << " " << e.second.second + 1 << "\n";
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 0; i < N; i++)
		parent[i] = i;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];

	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			if (map[i][j] < 0) {			// 이미 연결되어 있는 정점끼리는 Union 연산으로 결합
				Union(i, j);
				C += map[i][j] * -1;
			}
			else
				edges.push_back({ map[i][j], {i, j} });
		}
	}
	
	Solve();
	return 0;
}