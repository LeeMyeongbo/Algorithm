#include <iostream>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

queue<pair<int, int>> q;			// (���� ��ġ, ���� Ƚ��)
int N, A[1000], visited[1000], Min = -1;

int Solve()
{
	fill(visited, visited + 1000, -1);
	q.push({ 0, 0 });
	visited[0] = 0;

	while (!q.empty()) {
		int cur = q.front().first;
		int jump = q.front().second;
		q.pop();

		if (cur == N - 1) {
			if (Min == -1)
				Min = jump;
			Min = Min > jump ? jump : Min;
			continue;
		}
		for (int i = 1; i <= A[cur]; i++) {
			if (cur + i >= N)												// ���� �� �Ÿ��� ������ ����� break
				break;
			if (visited[cur + i] == -1 || visited[cur + i] > jump + 1) {	// �湮�� �� ���ų� �� ���� ���� Ƚ���� �� �� �ִٸ� ť ����
				visited[cur + i] = jump + 1;
				q.push({ cur + i, jump + 1 });
			}
		}
	}
	return Min;
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> A[i];

	cout << Solve();
	return 0;
}