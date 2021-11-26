#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
using namespace std;

struct Bus {
	int x1, y1, x2, y2;
};
int m, n, k, sx, sy, dx, dy;
bool visited[5001];					// �湮 ���� (�ߺ��� ������ Ÿ�� �ʵ��� ��)
Bus bus[5001];

void Swap(int& n1, int& n2)
{
	int tmp = n1;
	n1 = n2;
	n2 = tmp;
}

int Solve()
{
	queue<pair<int, int>> q;
	for (int i = 1; i <= k; i++) {
		if (sx >= bus[i].x1 && sx <= bus[i].x2 && sy >= bus[i].y1 && sy <= bus[i].y2) {		// ������� ������ ������ ��� ť�� �ְ� �湮üũ
			q.push({ i, 1 });
			visited[i] = true;
		}
	}
	while (!q.empty()) {					// BFS ��� Ȱ��
		int cur = q.front().first;			// ���� ť���� ���� ���� ��ȣ
		int num = q.front().second;			// ���� ź Ƚ��
		q.pop();

		if (dx >= bus[cur].x1 && dx <= bus[cur].x2 && dy >= bus[cur].y1 && dy <= bus[cur].y2)
			return num;

		for (int i = 1; i <= k; i++) {
			// ť���� ���� ������ ���� �����̶� ��ġ�� ������ ��� �湮�� �� ������ ť�� �ְ� �湮üũ (�� ������ ��ĥ ���� ���� ��������!)
			if(!visited[i] && !(bus[i].x1 > bus[cur].x2 || bus[i].x2 < bus[cur].x1 || bus[i].y1 > bus[cur].y2 || bus[i].y2 < bus[cur].y1)){
				q.push({ i, num + 1 });
				visited[i] = true;
			}
		}
	}
	return -1;
}

int main()
{
	int b, x1, y1, x2, y2;
	if (!scanf("%d %d %d", &m, &n, &k))
		return 1;
	for (int i = 0; i < k; i++) {
		if (!scanf("%d %d %d %d %d", &b, &x1, &y1, &x2, &y2))
			return 1;
		if (x1 > x2)
			Swap(x1, x2);				// �׻� x2�� x1 �̻��� �ǵ���
		if (y1 > y2)
			Swap(y1, y2);				// �׻� y2�� y1 �̻��� �ǵ���
		bus[b] = { x1, y1, x2, y2 };
	}
	if (!scanf("%d %d %d %d", &sx, &sy, &dx, &dy))
		return 1;

	printf("%d\n", Solve());

	return 0;
}