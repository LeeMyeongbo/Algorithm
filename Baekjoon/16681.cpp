#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define MAX 5000000000000
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, D, E, a, b, n, h[100001];
long long house[100001], korea[100001];		// house : ��(1)����, korea : �����(N)���� ����Ͽ� �� ���������� �ִ� �Ÿ�
priority_queue<pair<long long, int>> q;		// �׻� �ڷ��� �����ֱ� (�ִ� �Ÿ��� int�� ���� �Ѿ ���� �����Ƿ� �װ� �����ؼ�...)
vector<pair<int, int>> graph[100001];

void dijkstra(int start, long long di[])
{
	fill(di, di + N + 1, MAX);
	di[start] = 0;
	q.push({ 0, start });

	while (!q.empty()) {
		int cur = q.top().second;
		long long sum = -q.top().first;
		q.pop();

		if (sum > di[cur])					// ���� ����Ǿ� �ִ� ���� ���� ��ġ������ �ִܰŸ����� ũ�ٸ� ���� �ʿ� x
			continue;

		for (auto p : graph[cur]) {
			if (di[p.second] > di[cur] + p.first) {
				di[p.second] = di[cur] + p.first;
				q.push({ -di[p.second], p.second });
			}
		}
	}
}

void Solve()
{
	dijkstra(1, house);
	dijkstra(N, korea);
	
	long long Max = -MAX;
	for (int i = 2; i < N; i++)
		if (house[i] < MAX && korea[i] < MAX)		// ������ ��ǥ�������� & ��ǥ�������� �������� ��ΰ� �����Ѵٸ�
			Max = max(Max, (long long)h[i] * E - (house[i] + korea[i]) * D);	// ��ġ �ִ� ����
	if (Max > -MAX)
		cout << Max;
	else
		cout << "Impossible";
}

int main()
{
	FAST;
	cin >> N >> M >> D >> E;
	for (int i = 1; i <= N; i++)
		cin >> h[i];
	for (int i = 0; i < M; i++) {					// ����� ����������
		cin >> a >> b >> n;
		if (h[a] < h[b])
			graph[a].push_back({ n, b });			// ���̰� �� ���� �����θ� ���� �ܹ��� ������� ���� �׷��� ����
		else if (h[a] > h[b])
			graph[b].push_back({ n, a });
	}
	for (int i = 1; i <= N; i++)
		sort(graph[i].begin(), graph[i].end());		// �� ������� ����� �������� ����ġ ������������ ����
	
	Solve();
	return 0;
}