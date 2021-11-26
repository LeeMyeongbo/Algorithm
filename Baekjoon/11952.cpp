#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M, K, S, p, q, z, u, graph, weight[100001];
bool impossible[100001];
long long dij[100001];
vector<int> graph[100001];
queue<pair<int, int>> zombie_city;
priority_queue<pair<long long, int>> pq;

long long dijkstra()
{
	fill(dij, dij + N + 1, -1);
	pq.push({ 0, 1 });
	dij[1] = 0;

	while (!pq.empty()) {
		long long dist = -pq.top().first;
		int cur = pq.top().second;
		pq.pop();

		if (dist > dij[cur])
			continue;

		for (int& i : graph[cur]) {		// ����� ���õ� ��� ���Ǹ� ���ɴ����� ���� ���õ鸸 ���ͽ�Ʈ�� ����
			if (!impossible[i] && (dij[i] == -1 || dij[i] > dij[cur] + weight[i])) {
				dij[i] = dij[cur] + weight[i];
				pq.push({ -dij[i], i });
			}
		}
	}
	return dij[N];
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N >> M >> K >> S >> p >> q;
	fill(weight, weight + N, p);		// 1�� ~ N-1�� ���õ� ��� ���ڷ� p������ (N�� ���ô� 0)

	for (int i = 0; i < K; i++) {		// ���� ������ ���õ� üũ�ϰ� BFS ���� ť�� ����
		cin >> z;
		impossible[z] = true;
		zombie_city.push({ z, 0 });
	}
	for (int i = 0; i < M; i++) {
		cin >> u >> graph;
		graph[u].push_back(graph);
		graph[graph].push_back(u);
	}
	while (!zombie_city.empty()) {		// ���� ���ɵ� ���õ�κ��� BFS ������ �ִ� �Ÿ��� S�̳��� �ִ� ������ ���õ� ��� ���ڷ� q�� ��ȯ
		int cur = zombie_city.front().first;
		int dist = zombie_city.front().second;
		zombie_city.pop();

		for (int& i : graph[cur]) {
			if (!impossible[i] && weight[i] == p && dist + 1 <= S) {
				zombie_city.push({ i, dist + 1 });
				weight[i] = q;
			}
		}
	}

	cout << dijkstra();
	return 0;
}