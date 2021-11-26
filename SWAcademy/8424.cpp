#include <iostream>
#include <vector>
using namespace std;

int test_case, T, N, x, y, pre[1001], cycle_start;		// cycle_start : 사이클이 최초로 시작되는 정점, pre[i] : i번 정점의 이전 정점
bool cycle[1001];							// 사이클을 이루는 정점 true로 표시
vector<int> graph[1001];

bool dfs(int c, int p)						// c : 현재 정점, p : 바로 이전 정점
{
	pre[c] = p;
	bool is_cycle = false;

	for (int i : graph[c]) {
		if (pre[i] == -1) {					// 방문한 적 없는 정점 방문 시
			bool cycling = dfs(i, c);
			if (cycling)
				cycle[c] = is_cycle = true;
		}
		else if (pre[i] > -1 && i != p && !cycle[i]) {	// 방문한 적은 있는데 바로 이전에 방문한 정점은 아닐 때 -> 사이클 발견!
			cycle[c] = is_cycle = true;					// cycle에 속한다고 표시한 적 없는 정점이어야지 cycle_start가 갱신 안됨!
			cycle_start = i;				// 사이클 시작 정점 저장
		}
	}
	if (cycle_start == c)					// 사이클 최초 시작 정점까지 재귀 빠져나오면 사이클 탐색 완료!
		is_cycle = false;
	return is_cycle;
}

int main(int argc, char** argv)
{
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		cin >> N;
		fill(pre, pre + N + 1, -1);
		fill(cycle, cycle + N + 1, false);

		for (int i = 0; i < N; i++) {
			cin >> x >> y;
			graph[x].push_back(y);
			graph[y].push_back(x);
		}
		dfs(1, 0);

		int ans = 0;
		for (int i = 1; i <= N; i++)
			if (cycle[i])
				ans++;

		cout << "#" << test_case << " " << ans << endl;
		cycle_start = 0;
		for (int i = 1; i <= N; i++)
			graph[i].clear();
	}
	return 0;
}