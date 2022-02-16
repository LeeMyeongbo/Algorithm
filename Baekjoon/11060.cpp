#include <iostream>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

queue<pair<int, int>> q;			// (현재 위치, 점프 횟수)
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
			if (cur + i >= N)												// 점프 뛴 거리가 범위를 벗어나면 break
				break;
			if (visited[cur + i] == -1 || visited[cur + i] > jump + 1) {	// 방문한 적 없거나 더 적은 점프 횟수로 갈 수 있다면 큐 삽입
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