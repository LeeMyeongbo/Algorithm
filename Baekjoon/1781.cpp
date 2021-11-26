#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

ll N, deadline, cup, ans;
vector<pair<ll, ll>> graph;
priority_queue<ll> pq;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> deadline >> cup;
		graph.push_back({ deadline, cup });
	}
	sort(graph.begin(), graph.end());

	for (auto p : graph) {
		pq.push(-p.second);
		while (pq.size() > p.first)
			pq.pop();
	}
	while (!pq.empty()) {
		ans += -pq.top();
		pq.pop();
	}
	cout << ans;
	return 0;
}