#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, info[50][50], island, edge[2501], height[2501], ans[51];	// info : 섬들의 번호 저장, edge[i] : i번 섬으로 향하는 진입 간선 수
const int dr[] = { 0, 0, 1, -1, -1, 1, 1, -1 }, dc[] = { 1, -1, 0, 0, 1, 1, -1, -1 };
char map[50][51];
bool visited_ocean[50][50], visited_island[2501];
vector<vector<pair<int, int>>> islands;									// islands[i] : i번 섬을 이루고 있는 칸들의 좌표 저장
vector<int> graph[2501];
queue<pair<int, int>> q;

void Get_island_num()					// 각 섬들 번호 부여 및 위치 저장
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (info[i][j] != -1 || map[i][j] == '.')
				continue;

			vector<pair<int, int>> lands;
			q.push({ i, j });
			info[i][j] = island;

			while (!q.empty()) {
				int r = q.front().first;
				int c = q.front().second;
				q.pop();

				lands.push_back({ r, c });
				for (int d = 0; d < 8; d++) {
					int R = r + dr[d];
					int C = c + dc[d];
					if (R >= 0 && R < N && C >= 0 && C < M && map[R][C] == 'x' && info[R][C] == -1) {
						info[R][C] = island;
						q.push({ R, C });
					}
				}
			}
			islands.push_back(lands);
			island++;
		}
	}
}

void Check(int r, int c)			// 현재 [r][c]에 위치한 바다로부터 BFS 돌며 연결된 바다 및 그 바다와 접하는 섬들 탐색
{
	if (map[r][c] == '.') {
		q.push({ r, c });
		visited_ocean[r][c] = true;
	}
	else {
		visited_island[info[r][c]] = true;
		return;
	}

	while (!q.empty()) {
		int cur_r = q.front().first;
		int cur_c = q.front().second;
		q.pop();

		for (int d = 0; d < 4; d++) {
			int R = cur_r + dr[d];
			int C = cur_c + dc[d];
			if (R >= 0 && R < N && C >= 0 && C < M) {
				if (map[R][C] == '.' && !visited_ocean[R][C]) {
					visited_ocean[R][C] = true;
					q.push({ R, C });
				}
				else if (info[R][C] >= 0)
					visited_island[info[R][C]] = true;
			}
		}
	}
}

void Find_Outer_island()				// 가장 외부에 있는 섬들 및 바다 탐색
{
	for (int i = 0; i < N; i++) {		// 0열과 M - 1열에 방문한 적 없는 바다 있으면 탐색
		if (!visited_ocean[i][0])
			Check(i, 0);
		if (!visited_ocean[i][M - 1])
			Check(i, M - 1);
	}
	for (int j = 0; j < M; j++) {		// 0행과 N - 1행에 방문한 적 없는 바다 있으면 탐색
		if (!visited_ocean[0][j])
			Check(0, j);
		if (!visited_ocean[N - 1][j])
			Check(N - 1, j);
	}
}

void Make_Graph()			// 각 섬마다 내부에 있는 섬 탐색하고 방향 그래프 형성 (외부 섬←내부 섬 형식, 외부 섬 번호 < 내부 섬 번호)
{
	for (int i = 0; i < island; i++) {
		for (auto& p : islands[i]) {
			for (int d = 0; d < 4; d++) {
				int R = p.first + dr[d];
				int C = p.second + dc[d];
				// 현재 섬 근처에서 방문한 적 없는 바다 존재하면 그 바다가 현재 섬의 내부 바다
				if (R >= 0 && R < N && C >= 0 && C < M && map[R][C] == '.' && !visited_ocean[R][C]) { 
					q.push({ R, C });
					visited_ocean[R][C] = true;
				}
			}
			while (!q.empty()) {				// 그 내부 바다에서 BFS를 돌면서 만난 다른 섬 = 현재 섬의 내부의 섬
				int cur_r = q.front().first;
				int cur_c = q.front().second;
				q.pop();

				for (int d = 0; d < 4; d++) {
					int R = cur_r + dr[d];
					int C = cur_c + dc[d];
					if (R >= 0 && R < N && C >= 0 && C < M) {
						if (map[R][C] == '.' && !visited_ocean[R][C]) {
							visited_ocean[R][C] = true;
							q.push({ R, C });
						}
						else if (map[R][C] == 'x' && !visited_island[info[R][C]]) {
							visited_island[info[R][C]] = true;
							graph[info[R][C]].push_back(i);
							edge[i]++;
						}
					}
				}
			}
		}
	}
}

void topological()		// 위상 정렬로 각 섬들 최대 높이 갱신
{
	queue<int> tq;
	for (int i = 0; i < island; i++) {
		if (!edge[i])
			tq.push(i);
	}
	while (!tq.empty()) {
		int cur = tq.front();
		tq.pop();

		for (int i : graph[cur]) {
			edge[i]--;
			height[i] = max(height[i], height[cur] + 1);
			if (!edge[i])
				tq.push(i);
		}
	}
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		cin >> map[i];
	for (int i = 0; i < N; i++)
		fill(info[i], info[i] + M, -1);
	Get_island_num();
	Find_Outer_island();
	Make_Graph();
	topological();

	for (int i = 0; i < island; i++)
		ans[height[i]]++;
	if (island)
		for (int i = 0; ans[i]; i++)
			cout << ans[i] << " ";
	else
		cout << -1;
	
	return 0;
}