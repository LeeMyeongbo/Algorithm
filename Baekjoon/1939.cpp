#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define MAX 1000000000
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, A, B, C, Start, End, Left = MAX, Right, ans;
vector<pair<int, int>> graph[10001];			// (중량, 연결된 정점)으로 저장

bool BFS(int weight)
{
	queue<int> q;
	bool visited[10001] = { false, };
	q.push(Start);
	visited[Start] = true;

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		if (cur == End)
			return true;

		for (auto& p : graph[cur]) {
			if (p.first >= weight && !visited[p.second]) {
				visited[p.second] = true;
				q.push(p.second);
			}
		}
	}
	return false;
}

int Solve()
{
	while (Left <= Right) {
		int middle = (Left + Right) / 2;
		if (BFS(middle)) {					// middle 만큼의 중량으로 도착점까지 다리를 건널 수 있다면 left를 더 크게 조정
			ans = middle;
			Left = middle + 1;
		}
		else								// 건널 수 없다면 right를 작게 조정
			Right = middle - 1;
	}
	return ans;
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> A >> B >> C;
		Left = min(Left, C);
		Right = max(Right, C);
		graph[A].push_back({ C, B });
		graph[B].push_back({ C, A });
	}
	cin >> Start >> End;

	cout << Solve();
	return 0;
}