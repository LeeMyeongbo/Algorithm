#include <iostream>
#include <queue>
using namespace std;

int N, M, map[10][10], visited[10][10], dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 }, Ans = -1;
struct Node {
	int r, c, time;			// ��, ��, �ҿ� �ð�
};
queue<Node> q;

int BFS()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j])					// ���۱��� �ݵ�� �ϳ� �̻� ���� �� �ִٰ� �����Ƿ� BFS ��� �� ���� ������ ����
				continue;

			map[i][j] = M;					// ����ִ� ���� �߰� �� �ϴ� ���۱� ��ġ (���� �����ϴ� ���� ���� �� ������ �� �信�� ���� x)
			for (int i = 0; i < N; i++)
				fill(visited[i], visited[i] + N, -1);	// visited�� �Ϲ����� �湮 üũ�� �ƴ� �̵� �ð��� �ּڰ��� �����ؾ� ��

			q.push({ 0, 0, 0 });
			visited[0][0] = 0;

			while (!q.empty()) {
				Node node = q.front();
				q.pop();

				if (node.r == N - 1 && node.c == N - 1) {
					if (Ans == -1)
						Ans = visited[node.r][node.c];
					Ans = Ans > visited[node.r][node.c] ? visited[node.r][node.c] : Ans;
					continue;
				}

				for (int d = 0; d < 4; d++) {
					int R = node.r + dr[d];
					int C = node.c + dc[d];
					if (R >= 0 && R < N && C >= 0 && C < N && map[R][C]) {
						if (map[node.r][node.c] > 1 && map[R][C] > 1)			// ���۱��� 2�� �������� �ǳʴ� ��� skip (���� �� �б�!)
							continue;
						// �̵��� ���ÿ� �ǳʷ��� ���۱� �ֱ��� ����̸鼭 node.time �̻��� �ڿ��� �� �ּڰ� ���� (�Ϲ� ������ �Ȱ��� �����)
						if (visited[R][C] == -1 || visited[R][C] > node.time + map[R][C] - node.time % map[R][C]) {
							visited[R][C] = node.time + map[R][C] - node.time % map[R][C];
							q.push({ R, C, visited[R][C] });
						}
					}
				}
			}
			map[i][j] = 0;		// BFS ������ ��ġ�ߴ� ���۱� �ٽ� ��������� ��
		}
	}
	return Ans;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];
	
	cout << BFS();

	return 0;
}