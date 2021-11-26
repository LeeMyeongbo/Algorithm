#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define MAX 1000000000000
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

template <class T = void>
struct compare {
	bool operator()(const T& n1, const T& n2) const {
		return n1.sum > n2.sum;
	}
};

struct Node {
	long long sum;
	int cur, flight;
};
int n, m, f, s, t, i, j, c;
long long di[2][50000];			// [0][i] : �������� ��ġ�� ����, [1][i] : �������� 1�� ��ģ ���¿��� i ���������� �ִ� �Ÿ�
vector<pair<int, int>> graph[50000];
priority_queue<Node, vector<Node>, compare<Node>> q;

long long Solve()
{
	for (int i = 0; i < 2; i++)
		fill(di[i], di[i] + n, MAX);
	di[0][s] = di[1][s] = 0;
	q.push({ 0, s, 0 });

	while (!q.empty()) {
		Node node = q.top();
		q.pop();

		if (node.sum > di[node.flight][node.cur] || node.cur == t)
			continue;
		for (auto p : graph[node.cur]) {
			// ���θ� ���İ��� �ش� �������� �� �� �ִ� ���
			if (p.first && di[node.flight][p.second] > di[node.flight][node.cur] + p.first) {
				di[node.flight][p.second] = di[node.flight][node.cur] + p.first;
				q.push({ di[node.flight][p.second], p.second, node.flight });
			}
			// �������� ���İ� �� �ְ� �ش� �������� �� �� �ִ� ��� (�������� �� ���� �̿��� ���� ����� ����)
			else if (!p.first && !node.flight && di[1][p.second] > di[0][node.cur]) {
				di[1][p.second] = di[0][node.cur];
				q.push({ di[1][p.second], p.second, 1 });
			}
		}
	}
	return min(di[0][t], di[1][t]);		// t���������� �ִ� �Ÿ�(������ 0�� or 1�� ��ģ �� �� �ּڰ�) ����
}

int main()
{
	FAST;
	cin >> n >> m >> f >> s >> t;
	for (int e = 0; e < m; e++) {
		cin >> i >> j >> c;
		graph[i].push_back({ c, j });
		graph[j].push_back({ c, i });
	}
	for (int fl = 0; fl < f; fl++) {
		cin >> i >> j;
		graph[i].push_back({ 0, j });
	}

	cout << Solve();
	return 0;
}