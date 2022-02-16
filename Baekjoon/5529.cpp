#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>
using namespace std;

int M, N, K, x, y;
pair<int, int> Switch[200000];
vector<tuple<int, int, int>> S_x, S_y, Start;	// S_x : (x, y, 스위치 번호)로, S_y : (y, x, 스위치 번호)로 저장
vector<pair<int, int>> graph[200001][2];		// (연결된 스위치 번호, 간선 길이)로 저장
long long dij[200001][2], ans = -1;				// dij[i][0] : i번 스위치에 위아래로 이동해서 갈 수 있는 최단 시간
												// dij[i][1] : i번 스위치에 좌우로 이동해서 갈 수 있는 최단 시간
void make_Graph()
{
	sort(S_x.begin(), S_x.end());
	sort(S_y.begin(), S_y.end());
	
	for (int i = 0; i < S_x.size() - 1; i++) {
		if (get<0>(S_x[i]) == 1)
			Start.push_back(S_x[i]);
		if (get<0>(S_x[i]) == get<0>(S_x[i + 1])) {			// 상하로 왔다갔다 하는 경로 저장
			graph[get<2>(S_x[i])][0].push_back({get<2>(S_x[i + 1]), get<1>(S_x[i + 1]) - get<1>(S_x[i])});
			graph[get<2>(S_x[i + 1])][0].push_back({get<2>(S_x[i]), get<1>(S_x[i + 1]) - get<1>(S_x[i])});
		}
		if (get<0>(S_y[i]) == get<0>(S_y[i + 1])) {			// 좌우로 왔다갔다 하는 경로 저장
			graph[get<2>(S_y[i])][1].push_back({get<2>(S_y[i + 1]), get<1>(S_y[i + 1]) - get<1>(S_y[i])});
			graph[get<2>(S_y[i + 1])][1].push_back({get<2>(S_y[i]), get<1>(S_y[i + 1]) - get<1>(S_y[i])});
		}
	}
	if (get<0>(S_x.back()) == 1) 
		Start.push_back(S_x.back());
}

long long dijkstra()
{
	priority_queue<tuple<long long, int, int>> pq;		// (소요 시간, 문 열린 방향, 현재 스위치 번호)로 저장
	if (!Start.empty()){
		dij[get<2>(Start[0])][0] = get<1>(Start[0]) - 1;
		pq.push({-dij[get<2>(Start[0])][0], 0, get<2>(Start[0])});
	}

	while(!pq.empty()) {
		long long sum = -get<0>(pq.top());
		int open = get<1>(pq.top());
		int cur = get<2>(pq.top());
		pq.pop();

		if (sum > dij[cur][open])
			continue;

		if (Switch[cur].first == M || Switch[cur].second == N) {
			sum = !open ? sum + M - Switch[cur].first + 1 : sum + N - Switch[cur].second + 1;
			if (ans == -1)
				ans = sum;
			ans = min(ans, sum);
			continue;
		}
		
		for (auto& p : graph[cur][open]) {
			if (!dij[p.first][open] || dij[p.first][open] > sum + p.second) {
				dij[p.first][open] = sum + p.second;
				pq.push({-dij[p.first][open], open, p.first});
			}
		}
		if (!dij[cur][1 - open] || dij[cur][1 - open] > sum + 1) {
			dij[cur][1 - open] = sum + 1;
			pq.push({-dij[cur][1 - open], 1 - open, cur});
		}
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> M >> N >> K;
	for (int i = 0; i < K; i++) {
		cin >> x >> y;
		S_x.push_back({ x, y, i });
		S_y.push_back({ y, x, i });
		Switch[i] = {x, y};
	}
	make_Graph();

	cout << dijkstra();
	return 0;
}