#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, a, b, parent[1001];
pair<double, double> p[1001];
vector<pair<double, pair<int, int>>> edges;

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

double Solve()
{
	double sum = 0.0;
	for (int i = 1; i < N; i++) {
		for (int j = i + 1; j <= N; j++) {
			if (Find(i) == Find(j))
				continue;
			double distance = sqrt(pow(p[i].first - p[j].first, 2) + pow(p[i].second - p[j].second, 2));
			edges.push_back({ distance, {i, j} });
		}
	}
	sort(edges.begin(), edges.end());		// ����ġ (�� ��ǥ ���� �Ÿ�) ������������ ���� ����

	for (auto &e : edges) {
		bool complete = true;
		if (Union(e.second.first, e.second.second)) {	// Union�� ���� �� ������ ����Ǿ��� �� �Ÿ� �� �����ϰ� ��� ���� ����Ǿ����� ����
			sum += e.first;
			for (int v = 1; v <= N; v++)
				if (Find(v) != 1) {
					complete = false;
					break;
				}
		}
		else continue;						// �̹� ����Ǿ� �ִٸ� skip
		if (complete) break;
	}
	return sum;
}

int main()
{
	FAST;
	cout << fixed;
	cout.precision(2);

	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		parent[i] = i;
		cin >> p[i].first >> p[i].second;
	}
	for (int i = 1; i <= M; i++) {
		cin >> a >> b;
		Union(a, b);			// �̹� ����� ��ǥ�� ����
	}

	cout << Solve();
	return 0;
}