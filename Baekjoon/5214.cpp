#include <iostream>
#include <vector>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, K, M, station;
vector<int> graph[101001];
queue<pair<int, int>> q;		// (현재 정점, 거친 역 개수)
bool visited[101001];

int Solve()
{
	q.push({ 1, 1 });
	visited[1] = true;

	while (!q.empty()) {
		int cur = q.front().first;
		int num = q.front().second;
		q.pop();

		if (cur == N)
			return num;

		for (int i : graph[cur]) {
			if (!visited[i]) {
				i > N ? q.push({ i, num }) : q.push({ i, num + 1 });	// 역에서 하이퍼튜브로 이동 시 그대로, 하이퍼튜브에서 역으로 이동 시 +1
				visited[i] = true;
			}
		}
	}
	return -1;
}

int main()
{
	FAST;
	cin >> N >> K >> M;
	for (int i = 1; i <= M; i++) {
		for (int j = 0; j < K; j++) {			// 역은 1부터 N, 하이퍼튜브를 N + 1부터 N + M까지 둠
			cin >> station;
			graph[station].push_back(N + i);
			graph[N + i].push_back(station);
		}
	}

	cout << Solve();
	return 0;
}