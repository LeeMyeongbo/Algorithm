#include <iostream>
#include <vector>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int n, m, k, a, b, c;
vector<pair<int, int>> graph[1001];
priority_queue<pair<int, int>> pq;			// (��, ���� ����)���� ����
priority_queue<int> dest[1001];				// �� �������� 1 ~ k��° �ִ� �Ÿ� ����

void Dijkstra()
{
	pq.push({ 0, 1 });
	dest[1].push(0);

	while (!pq.empty()) {
		int sum = -pq.top().first;
		int cur = pq.top().second;
		pq.pop();

		for (auto& p : graph[cur]) {
			if (dest[p.first].size() < k) {				// ���� ���ǰ� �ִ� ������ �� ũ�Ⱑ k���� ������ �״�� push
				dest[p.first].push(sum + p.second);
				pq.push({ -(sum + p.second), p.first });
			}
			// ũ�Ⱑ k�̰� ���� ����� �ִ��� ������� ���� �Ÿ� �պ��� ũ�ٸ� �� �ִ� ����
			else if (dest[p.first].size() == k && sum + p.second < dest[p.first].top()) {
				dest[p.first].pop();
				dest[p.first].push(sum + p.second);
				pq.push({ -(sum + p.second), p.first });
			}
		}
	}
}

int main()
{
	FAST;
	cin >> n >> m >> k;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		graph[a].push_back({ b, c });
	}
	Dijkstra();
	
	for (int i = 1; i <= n; i++) {
		if (dest[i].size() < k)
			cout << "-1\n";
		else
			cout << dest[i].top() << "\n";
	}
	return 0;
}