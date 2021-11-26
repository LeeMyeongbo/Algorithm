#include <iostream>
#include <vector>
#include <queue>
#define MAX 1000000000
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, S, D, U, V, P, di[500];				// di[i] : S���� i�� ���������� �ִ� �Ÿ�
vector<pair<int, int>> graph[500], pre[500];	// pre[i] : i�� ���� ������ ��ģ �������� (����ġ, ����� ����)�� ����
priority_queue<pair<int, int>> pq;				// (�ִ� �Ÿ�, �� ��ġ)
bool deleted_edge[500][500];					// ���� ���� i���� ���� j�� ���� ������ �������� [i][j] = true�� ��

void Dijkstra()
{
	fill(di, di + N, MAX);
	di[S] = 0;
	pq.push({ 0, S });

	while (!pq.empty()) {
		int cur = pq.top().second;
		int sum = -pq.top().first;
		pq.pop();

		if (sum > di[cur] || cur == D)
			continue;

		for (auto p : graph[cur]) {
			if (!deleted_edge[cur][p.second] && di[p.second] >= di[cur] + p.first) {	// ������ ������ �ƴϸ鼭 �� �� ���� ���
				if (di[p.second] > di[cur] + p.first) {									// �ִ� �Ÿ� ����
					di[p.second] = di[cur] + p.first;
					pq.push({ -di[p.second], p.second });
				}
				// ó�� �湮�ϴ� �����̰ų� �̹� ����Ǿ� �ִ� �ִ� �Ÿ��� ���� ��쿣 �״�� �߰�
				if (pre[p.second].empty() || pre[p.second][0].first == di[p.second])
					pre[p.second].push_back({ di[p.second], cur });
				// �� ���� �ִ� �Ÿ��� ���ŵǸ� ������ ����� �͵��� ��� �����ϰ� ���Ӱ� ���ŵ� �ִ� �Ÿ� �� ���� ���� ����
				else if (pre[p.second][0].first > di[p.second]) {
					pre[p.second].clear();
					pre[p.second].push_back({ di[p.second], cur });
				}
			}
		}
	}
}

void Delete_Edges(int now)
{
	for (auto e : pre[now]) {
		if (!deleted_edge[e.second][now]) {			// �ߺ� �湮 ����!! (�׻� �߿�! �������� ����)
			deleted_edge[e.second][now] = true;
			Delete_Edges(e.second);
		}
	}
}

int Solve()
{
	Dijkstra();					// ������������� �ִ� ��� ��� ���ϰ�
	if (di[D] == MAX)
		return -1;

	Delete_Edges(D);			// �ִ� ��ε� ��� �����ش�

	for (int i = 0; i < N; i++)
		pre[i].clear();

	Dijkstra();					// �׸��� ���� ������ �����ϰ� ������ ������� �ٽ� �� �� �ִ� ��� ����
	if (di[D] == MAX)
		return -1;
	return di[D];
}

int main()
{
	FAST;
	while (1) {
		cin >> N >> M;
		if (!N && !M)
			return 0;

		cin >> S >> D;
		for (int i = 0; i < M; i++) {
			cin >> U >> V >> P;
			graph[U].push_back({ P, V });
		}
		cout << Solve() << "\n";
		for (int i = 0; i < N; i++) {
			graph[i].clear();
			pre[i].clear();
		}
		for (int i = 0; i < N; i++)
			fill(deleted_edge[i], deleted_edge[i] + N, false);
	}
}