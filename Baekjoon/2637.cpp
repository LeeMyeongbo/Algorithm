#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M, x, y, k, table[101][101], indegree[101];	// table[a][b] : 부품 a를 만들기 위해 부품 b가 몇 개 필요한지 저장
vector<pair<int, int>> graph[101];
queue<int> q;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		cin >> x >> y >> k;
		graph[y].push_back({ x, k });		// y -> x, 가중치 k
		indegree[x]++;
	}
	for (int i = 1; i <= N; i++)
		if (!indegree[i]) {
			q.push(i);						// 진입 차수가 0인 정점들 큐에 삽입
			table[i][i] = 1;
		}

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (pair<int, int>& p : graph[cur]) {
			for (int i = 1; i <= N; i++)
				table[p.first][i] += table[cur][i] * p.second;		// table의 cur행에다가 가중치(k)만큼 곱해서 연결된 정점 행에 더함

			indegree[p.first]--;
			if (!indegree[p.first])
				q.push(p.first);
		}
	}

	for (int i = 1; i <= N; i++)
		if (table[N][i])
			cout << i << " " << table[N][i] << endl;
	
	return 0;
}