#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
using namespace std;

struct Bus {
	int x1, y1, x2, y2;
};
int m, n, k, sx, sy, dx, dy;
bool visited[5001];					// 방문 여부 (중복된 버스는 타지 않도록 함)
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
		if (sx >= bus[i].x1 && sx <= bus[i].x2 && sy >= bus[i].y1 && sy <= bus[i].y2) {		// 출발지를 지나는 버스들 모두 큐에 넣고 방문체크
			q.push({ i, 1 });
			visited[i] = true;
		}
	}
	while (!q.empty()) {					// BFS 방식 활용
		int cur = q.front().first;			// 현재 큐에서 빼낸 버스 번호
		int num = q.front().second;			// 버스 탄 횟수
		q.pop();

		if (dx >= bus[cur].x1 && dx <= bus[cur].x2 && dy >= bus[cur].y1 && dy <= bus[cur].y2)
			return num;

		for (int i = 1; i <= k; i++) {
			// 큐에서 빼낸 버스의 운행 구간이랑 겹치는 버스들 모두 방문한 적 없으면 큐에 넣고 방문체크 (두 선분이 겹칠 때의 조건 잊지말기!)
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
			Swap(x1, x2);				// 항상 x2가 x1 이상이 되도록
		if (y1 > y2)
			Swap(y1, y2);				// 항상 y2가 y1 이상이 되도록
		bus[b] = { x1, y1, x2, y2 };
	}
	if (!scanf("%d %d %d %d", &sx, &sy, &dx, &dy))
		return 1;

	printf("%d\n", Solve());

	return 0;
}