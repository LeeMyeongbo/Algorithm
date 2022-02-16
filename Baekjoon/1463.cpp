#include <iostream>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, visited[1000001];
queue<pair<int, int>> q;

int Solve()
{
	fill(visited, visited + N + 1, -1);
	q.push({ N, 0 });
	visited[N] = 0;

	while (!q.empty()) {
		int cur = q.front().first;
		int cal = q.front().second;
		q.pop();

		if (cur == 1)
			return cal;

		if (cur % 3 == 0 && (visited[cur / 3] == -1 || visited[cur / 3] > cal + 1)) {
			visited[cur / 3] = cal + 1;
			q.push({ cur / 3, cal + 1 });
		}
		if (cur % 2 == 0 && (visited[cur / 2] == -1 || visited[cur / 2] > cal + 1)) {
			visited[cur / 2] = cal + 1;
			q.push({ cur / 2, cal + 1 });
		}
		if (visited[cur - 1] == -1 || visited[cur - 1] > cal + 1) {
			visited[cur - 1] = cal + 1;
			q.push({ cur - 1, cal + 1 });
		}
	}
	return -1;
}

int main()
{
	FAST;
	cin >> N;
	cout << Solve();
	return 0;
}