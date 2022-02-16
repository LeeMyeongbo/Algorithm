#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int N, S, E, v1, v2, len, Max, pre[100001], Sum[100001];
vector<pair<int, int>> graph[100001];		// graph[출발 정점] = (도착 정점, 통로 길이)꼴로 저장
priority_queue<pair<int, int>> q;			// (거리 합, 현재 정점)꼴로 저장

int find_Min()
{
	fill(Sum, Sum + N + 1, -1);
	q.push({ 0, S });
	Sum[S] = 0;

	while (!q.empty()) {
		int sum = -q.top().first;
		int cur = q.top().second;
		q.pop();

		if (cur == E)
			return sum;

		for (pair<int, int>& p : graph[cur]) {
			if (Sum[p.first] == -1 || Sum[p.first] > p.second + sum) {
				Sum[p.first] = p.second + sum;
				pre[p.first] = cur;
				q.push({ -Sum[p.first], p.first });
			}
		}
	}
	return 0;
}

void backtrack(int v)						// 로봇 2(목표 지점)가 위치한 지점으로부터 역추적해가며 경로 내 가장 긴 통로 탐색
{
	for (pair<int, int>& p : graph[v]) {
		if (p.first == pre[v]) {
			Max = Max < p.second ? p.second : Max;
			backtrack(pre[v]);
			break;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N >> S >> E;
	for (int i = 0; i < N - 1; i++) {
		cin >> v1 >> v2 >> len;
		graph[v1].push_back({ v2, len });
		graph[v2].push_back({ v1, len });
	}
	int path_len = find_Min();
	backtrack(E);

	cout << path_len - Max;
	return 0;
}