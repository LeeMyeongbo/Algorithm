#include <iostream>
#include <queue>
#define MAX 1000000
using namespace std;

struct Node {
	int r, c, cur;
};
int map[2001][2001], a, b, start_r, start_c, pre[MAX + 1];
const int dr[] = { -1, 0, 1, 1, 0, -1 }, dc[] = { 1, 1, 0, -1, -1, 0 };
queue<Node> q;

void make_map()
{
	int r = 1000, c = 1000, hexa = 0, cur = 0;

	while (true) {
		hexa++;
		for (int d = 0; d < 6; d++) {		// �� �� �� �� �� �� ������ ������
			int repeat = hexa - 1;
			if (!d)
				repeat--;					// �� ������ �ٸ� ����麸�� 1���� �� �������� ��
			for (int m = 0; m < repeat; m++) {
				map[r][c] = ++cur;
				if (cur == a)
					start_r = r, start_c = c;
				if (cur == MAX)
					return;

				r += dr[d], c += dc[d];
			}
		}
		map[r][c] = ++cur;
		if (cur == a)
			start_r = r, start_c = c;
		if (cur == MAX)
			return;

		r += dr[5], c += dc[5];				// �׸��� �������� �� �ѹ� ��
	}
}

void show_path(int cur)
{
	if (pre[cur] > 0)
		show_path(pre[cur]);
	cout << cur << " ";
}

void BFS()
{
	q.push({ start_r, start_c, a });
	pre[a] = 0;

	while (!q.empty()) {
		Node node = q.front();
		q.pop();

		if (node.cur == b) {							// ���������κ��� �������ؼ� ���
			show_path(b);
			return;
		}

		for (int d = 0; d < 6; d++) {
			int R = node.r + dr[d];
			int C = node.c + dc[d];
			if (map[R][C] && pre[map[R][C]] == -1) {	// pre[map[R][C]]�� -1�̴�? -> �ش� map[R][C]�� �湮�� �� ����!
				pre[map[R][C]] = node.cur;
				q.push({ R, C, map[R][C] });
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	fill(pre, pre + MAX + 1, -1);

	cin >> a >> b;
	make_map();

	BFS();
	return 0;
}