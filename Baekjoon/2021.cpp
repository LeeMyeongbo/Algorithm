#include <iostream>
#include <vector>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, L, n, Start, End;
bool visited[200001];
vector<int> graph[200001];			// 역 마다 연결된 노선을 하나하나 다 간선으로 연결하기엔 너무 벅참 -> 노선도 하나의 정점으로 둠!
queue<pair<int, int>> q;			// (현재 정점, 노선 이용 횟수)

int Solve()
{
	q.push({ Start, 0 });
	visited[Start] = true;

	while (!q.empty()) {
		int cur = q.front().first;
		int num = q.front().second;
		q.pop();

		if (cur == End) {			// Start와 End가 같은 경우도 존재 가능
			if (!num)
				return 0;
			return num - 1;
		}

		for (int i : graph[cur]) {
			if (!visited[i]) {		// N번보다 큰 정점으로 향할 땐 노선 이용하는 것이므로 +1, 그렇지 않으면 노선에서 내리는 것이므로 그대로
				i > N ? q.push({ i, num + 1 }) : q.push({ i, num });
				visited[i] = true;
			}
		}
	}
	return -1;
}

int main()
{
	FAST;
	cin >> N >> L;
	for (int i = N + 1; i <= N + L; i++) {		// 1번부터 N번 정점은 역, N + 1번부터 N + L번 정점까지는 노선
		while (1) {
			cin >> n;
			if (n == -1)
				break;
			graph[n].push_back(i);
			graph[i].push_back(n);
		}
	}
	cin >> Start >> End;

	cout << Solve();
	return 0;
}