#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int T, n, d, c, a, b, s, di[10001];
vector<pair<int, int>> graph[10001];
priority_queue<pair<int, int>> q;

void Dijkstra()
{
	int num = 0, time = 0;

	fill(di, di + 10001, -1);
	di[c] = 0;
	q.push({ 0, c });

	while (!q.empty()) {				// ���ͽ�Ʈ�� ���� �� ��ǻ�ͱ��� ���̷����� �����Ǵ� �ּ� �ð� �����ذ��� ��
		int cur = q.top().second;
		int sum = -q.top().first;
		q.pop();

		if (sum > di[cur])
			continue;

		for (auto p : graph[cur]) {
			if (di[p.second] == -1 || di[p.second] > di[cur] + p.first) {
				di[p.second] = di[cur] + p.first;
				q.push({ -di[p.second], p.second });
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		if (di[i] != -1)
			num++;						// �ּ� �ð��� -1�� �ƴϸ� ������ �����ȴٴ� �Ҹ�
		time = max(time, di[i]);		// ���� �ʰ� �����Ǵ� ��ǻ�Ͱ� �ɸ��� �ð� ����
	}
	cout << num << " " << time << "\n";
}

int main()
{
	FAST;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> n >> d >> c;

		for (int e = 0; e < d; e++) {
			cin >> a >> b >> s;
			graph[b].push_back({ s, a });
		}
		Dijkstra();
		for (int i = 1; i <= n; i++)
			graph[i].clear();
	}
	return 0;
}