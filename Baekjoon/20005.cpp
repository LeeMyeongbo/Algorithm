#include <iostream>
#include <queue>
using namespace std;

struct Node {
	char id;
	int r, c, time;
};
int m, n, p, dps[26], damage, HP;				// 0���� 25���� a~z�� dps�� dps �迭�� ����
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
char map[1000][1001], id;
bool visited[26][1000][1000], arrived[26];		// a�� ������ ��ġ�� �����ϸ� arrived[0] = true�� ��(b�� 1, c�� 2...)
queue<Node> q;

int solve()
{
	int Time = 0;
	while (!q.empty()) {
		Node node = q.front();
		q.pop();

		if (Time < node.time) {					// �ð��� 1�ʾ� ���� ������ �������� ������ ��� ������ ��
			int total_damage = 0, people = 0;
			for (int i = 0; i < p; i++) {
				if (arrived[i]) {
					total_damage += dps[i];
					people++;
				}
			}
			HP -= total_damage;
			if (HP <= 0)
				return people;					// ������ ������ ���� ���� ��� �� ��Ƹ� �� ����
			Time++;								// �ð��� 1�� �帣���� ��
		}
		
		if (map[node.r][node.c] == 'B') {		// �����ϰ� 1�� �ڿ� ������ �ǰ� ����!(����)
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
	int total_damage = 0, people = 0;			// �������� �������� �ʾҴµ� BFS ����� �� �����Ƿ�
	for (int i = 0; i < p; i++) {				// ������ �ڸ��� ������ ��� �� ��Ʒ��� �����ؾ� ��
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