#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, info[50][50], island, edge[2501], height[2501], ans[51];	// info : ������ ��ȣ ����, edge[i] : i�� ������ ���ϴ� ���� ���� ��
const int dr[] = { 0, 0, 1, -1, -1, 1, 1, -1 }, dc[] = { 1, -1, 0, 0, 1, 1, -1, -1 };
char map[50][51];
bool visited_ocean[50][50], visited_island[2501];
vector<vector<pair<int, int>>> islands;									// islands[i] : i�� ���� �̷�� �ִ� ĭ���� ��ǥ ����
vector<int> graph[2501];
queue<pair<int, int>> q;

void Get_island_num()					// �� ���� ��ȣ �ο� �� ��ġ ����
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

void Check(int r, int c)			// ���� [r][c]�� ��ġ�� �ٴٷκ��� BFS ���� ����� �ٴ� �� �� �ٴٿ� ���ϴ� ���� Ž��
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

void Find_Outer_island()				// ���� �ܺο� �ִ� ���� �� �ٴ� Ž��
{
	for (int i = 0; i < N; i++) {		// 0���� M - 1���� �湮�� �� ���� �ٴ� ������ Ž��
		if (!visited_ocean[i][0])
			Check(i, 0);
		if (!visited_ocean[i][M - 1])
			Check(i, M - 1);
	}
	for (int j = 0; j < M; j++) {		// 0��� N - 1�࿡ �湮�� �� ���� �ٴ� ������ Ž��
		if (!visited_ocean[0][j])
			Check(0, j);
		if (!visited_ocean[N - 1][j])
			Check(N - 1, j);
	}
}

void Make_Graph()			// �� ������ ���ο� �ִ� �� Ž���ϰ� ���� �׷��� ���� (�ܺ� ���系�� �� ����, �ܺ� �� ��ȣ < ���� �� ��ȣ)
{
	for (int i = 0; i < island; i++) {
		for (auto& p : islands[i]) {
			for (int d = 0; d < 4; d++) {
				int R = p.first + dr[d];
				int C = p.second + dc[d];
				// ���� �� ��ó���� �湮�� �� ���� �ٴ� �����ϸ� �� �ٴٰ� ���� ���� ���� �ٴ�
				if (R >= 0 && R < N && C >= 0 && C < M && map[R][C] == '.' && !visited_ocean[R][C]) { 
					q.push({ R, C });
					visited_ocean[R][C] = true;
				}
			}
			while (!q.empty()) {				// �� ���� �ٴٿ��� BFS�� ���鼭 ���� �ٸ� �� = ���� ���� ������ ��
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

void topological()		// ���� ���ķ� �� ���� �ִ� ���� ����
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