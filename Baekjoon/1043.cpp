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
	while (!q.empty()) {			// BFS�� ������ �ƴ� ����� ����� ����� ��� Ž�� ����
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
		cin >> truth[i];						// ������ �ƴ� ����� ��� ����

	for (int i = 0; i < M; i++) {
		cin >> t;
		for (int j = 0; j < t; j++)
			cin >> party[i][j];
		for (int j = 0; j < t - 1; j++)
			for (int k = j + 1; k < t; k++)		// ��Ƽ ������ ������� ���μ��� ��� ������Ŀ��� ����� �ɷ� ǥ��
				adjacent[party[i][j]][party[i][k]] = adjacent[party[i][k]][party[i][j]] = true;
	}

	cout << Solve();
	return 0;
}