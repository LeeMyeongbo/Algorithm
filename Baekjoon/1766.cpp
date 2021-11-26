#include <iostream>
#include <queue>
#include <vector>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, v1, v2, edge[32001];		// edge[i] : i�� ������ ���� ���� ��
vector<int> graph[32001];
priority_queue<int, vector<int>, greater<int>> q;		// �ּ� �� (�ǵ��� ���� �������� Ǯ��� �ϹǷ�)

void Solve()
{
	for (int i = 1; i <= N; i++)
		if (!edge[i])
			q.push(i);

	while (!q.empty()) {
		int cur = q.top();
		q.pop();

		cout << cur << " ";
		for (int i : graph[cur]) {
			edge[i]--;					// �� ����(cur)������ ���� ������ ��� ����
			if (!edge[i])				// ���� i���� ���� �������� ��� ���ŵǸ� ���� i ����
				q.push(i);
		}
	}
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
		edge[v2]++;
	}

	Solve();
	return 0;
}