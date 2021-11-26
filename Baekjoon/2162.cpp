#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N, group, num = -1, X1, Y1, X2, Y2;
pair<pair<int, int>, pair<int, int>> line[3000];
bool visited[3000];

int CCW(pair<int, int>& p1, pair<int, int>& p2, pair<int, int>& p3)		// p1, p2 : 선분, p3 : 점
{
	int val1 = p1.first * p2.second + p2.first * p3.second + p3.first * p1.second;
	int val2 = p1.second * p2.first + p2.second * p3.first + p3.second * p1.first;
	if (val1 - val2 < 0)												// CCW : x1y2 + x2y3 + x3y1 - y1x2 - y2x3 - y3x1
		return -1;
	else if (val1 - val2 > 0)
		return 1;
	return 0;
}

bool is_Cross(int l, int c)
{
	int t1 = CCW(line[c].first, line[c].second, line[l].first);
	int t2 = CCW(line[c].first, line[c].second, line[l].second);
	int t3 = CCW(line[l].first, line[l].second, line[c].first);
	int t4 = CCW(line[l].first, line[l].second, line[c].second);

	if (t1 * t2 == 0 && t3 * t4 == 0) {												// 두 선분의 기울기가 일치할 경우
		if (line[c].first > line[c].second)
			swap(line[c].first, line[c].second);									// second가 first보다 크도록 함
		if (line[l].first > line[l].second)
			swap(line[l].first, line[l].second);
		if (line[c].first <= line[l].second && line[l].first <= line[c].second)		// 두 선분이 서로 만나면 true
			return true;															// 그게 아니라면 false
	}
	else if (t1 * t2 <= 0 && t3 * t4 <= 0)											// 기울기가 일치하지 않으면서 만나면 true
		return true;
	return false;																	// 그렇지 않으면 false
}

void Solve()
{
	queue<int> q;
	for (int i = 0; i < N; i++) {						// 방문하지 않은 선분을 찾으면 BFS로 인접한 선분 최대한 탐색
		if (visited[i])
			continue;
		int n = 0;
		group++;

		q.push(i);
		visited[i] = true;
		while (!q.empty()) {
			int c = q.front();
			q.pop();

			n++;
			for (int l = 0; l < N; l++) {
				if (!visited[l] && is_Cross(l, c)) {	// 현재 선분과 만나면서 방문한 적 없는 선분이라면 큐에 삽입
					q.push(l);
					visited[l] = true;
				}
			}
		}
		num = max(num, n);								// BFS 끝나면 그룹 내 선분 최대 개수 갱신
	}
	printf("%d\n%d", group, num);
}

int main()
{
	if (!scanf("%d", &N))
		return 1;

	for (int i = 0; i < N; i++) {
		if (!scanf("%d %d %d %d", &X1, &Y1, &X2, &Y2))
			return 1;
		line[i] = { {X1, Y1}, {X2, Y2} };
	}
	Solve();
	return 0;
}