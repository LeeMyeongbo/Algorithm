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
long long di[2][50000];			// [0][i] : 비행편을 거치지 않은, [1][i] : 비행편을 1번 거친 상태에서 i 정점까지의 최단 거리
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
			// 도로를 거쳐가고 해당 정점으로 갈 수 있는 경우
			if (p.first && di[node.flight][p.second] > di[node.flight][node.cur] + p.first) {
				di[node.flight][p.second] = di[node.flight][node.cur] + p.first;
				q.push({ di[node.flight][p.second], p.second, node.flight });
			}
			// 비행편을 거쳐갈 수 있고 해당 정점으로 갈 수 있는 경우 (비행편을 한 번도 이용한 적이 없어야 가능)
			else if (!p.first && !node.flight && di[1][p.second] > di[0][node.cur]) {
				di[1][p.second] = di[0][node.cur];
				q.push({ di[1][p.second], p.second, 1 });
			}
		}
	}
	return min(di[0][t], di[1][t]);		// t정점까지의 최단 거리(비행편 0번 or 1번 거친 것 중 최솟값) 리턴
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