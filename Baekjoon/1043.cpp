#include <iostream>
#include <algorithm>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, t, truth[50], party[50][50], ans;
bool adjacent[51][51], visited[51];
queue<int> q;

int Solve()
{
	for (int p : truth) {
		q.push(p);
		visited[p] = true;
	}
	while (!q.empty()) {			// BFS로 진실을 아는 사람과 연결된 사람들 모두 탐색 ㄱㄱ
		int cur = q.front();
		q.pop();

		for (int i = 1; i <= N; i++) {
			if (adjacent[cur][i] && !visited[i]) {
				visited[i] = true;
				q.push(i);
			}
		}
	}

	for (int i = 0; i < M; i++) {
		if (!visited[party[i][0]])
			ans++;
	}
	return ans;
}

int main()
{
	FAST;
	cin >> N >> M >> t;

	for (int i = 0; i < t; i++)
		cin >> truth[i];						// 진실을 아는 사람들 목록 저장

	for (int i = 0; i < M; i++) {
		cin >> t;
		for (int j = 0; j < t; j++)
			cin >> party[i][j];
		for (int j = 0; j < t - 1; j++)
			for (int k = j + 1; k < t; k++)		// 파티 참석한 사람끼리 서로서로 모두 인접행렬에다 연결된 걸로 표시
				adjacent[party[i][j]][party[i][k]] = adjacent[party[i][k]][party[i][j]] = true;
	}

	cout << Solve();
	return 0;
}