#include <iostream>
#include <queue>
using namespace std;

struct Node {
	char id;
	int r, c, time;
};
int m, n, p, dps[26], damage, HP;				// 0부터 25까지 a~z의 dps를 dps 배열에 저장
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
char map[1000][1001], id;
bool visited[26][1000][1000], arrived[26];		// a가 보스몹 위치에 도달하면 arrived[0] = true가 됨(b면 1, c면 2...)
queue<Node> q;

int solve()
{
	int Time = 0;
	while (!q.empty()) {
		Node node = q.front();
		q.pop();

		if (Time < node.time) {					// 시간이 1초씩 지날 때마다 보스몹에 도달한 놈들 때리게 함
			int total_damage = 0, people = 0;
			for (int i = 0; i < p; i++) {
				if (arrived[i]) {
					total_damage += dps[i];
					people++;
				}
			}
			HP -= total_damage;
			if (HP <= 0)
				return people;					// 보스몹 뒤지면 여태 때린 놈들 수 헤아린 거 리턴
			Time++;								// 시간이 1초 흐르도록 함
		}
		
		if (map[node.r][node.c] == 'B') {		// 도착하고 1초 뒤에 때려서 피가 깎임!(주의)
			arrived[node.id - 'a'] = true;
			continue;
		}

		for (int d = 0; d < 4; d++) {
			int R = node.r + dr[d];
			int C = node.c + dc[d];
			if (R >= 0 && R < m && C >= 0 && C < n && map[R][C] != 'X' && !visited[node.id - 'a'][R][C]) {
				visited[node.id - 'a'][R][C] = true;
				q.push({ node.id, R, C, node.time + 1 });
			}
		}
	}
	int total_damage = 0, people = 0;			// 보스몹이 뒤지지도 않았는데 BFS 종료될 수 있으므로
	for (int i = 0; i < p; i++) {				// 보스몹 자리에 도달한 놈들 수 헤아려서 리턴해야 함
		if (arrived[i]) {
			total_damage += dps[i];
			people++;
		}
	}
	HP -= total_damage;
	return people;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> m >> n >> p;
	for (int i = 0; i < m; i++) {
		cin >> map[i];
		for (int j = 0; j < n; j++) {
			if (map[i][j] >= 'a' && map[i][j] <= 'z') {
				visited[map[i][j] - 'a'][i][j] = true;
				q.push({ map[i][j], i, j, 0 });
				map[i][j] = '.';
			}
		}
	}
	for (int i = 0; i < p; i++) {
		cin >> id >> damage;
		dps[id - 'a'] = damage;
	}
	cin >> HP;

	cout << solve();
	return 0;
}