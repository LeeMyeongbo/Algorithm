#include <iostream>
#include <queue>
#include <cmath>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

pair<double, double> start, dest, canon[102];
priority_queue<int, vector<int>, greater<int>> q;
double times[102][102], di[102];
int n;

void get_time()			// 출발 지점과 각 대포 & 각 대포끼리 걸리는 시간의 최솟값 저장
{
	for (int j = 1; j <= n + 1; j++)		// 출발 지점에서는 각 대포까지 뛰어갈 수밖에 없으므로 뛰어가는 데 걸리는 시간만 저장
		times[0][j] = times[j][0] = sqrt(pow(canon[0].first - canon[j].first, 2) + pow(canon[0].second - canon[j].second, 2)) / 5;
	
	for (int i = 1; i <= n + 1; i++) {		// 한 대포에서 다른 대포까지 or 도착 지점까지는
		for (int j = 1; j <= n + 1; j++) {	// 대포타고 뛰어가는데 걸리는 시간과 뛰어서만 가는 데 걸리는 시간의 최솟값을 저장
			if (i == j)
				continue;
			double distance = sqrt(pow(canon[i].first - canon[j].first, 2) + pow(canon[i].second - canon[j].second, 2));
			times[i][j] = min(distance / 5, 2 + abs(distance - 50) / 5);
		}
	}
}

double Dijkstra()
{
	get_time();

	fill(di, di + 102, -1);
	q.push(0);
	di[0] = 0;

	while (!q.empty()) {			// 다익스트라로 출발지점에서 도착지점까지 최소 시간 도출
		int cur = q.top();
		q.pop();

		for (int i = 1; i <= n + 1; i++) {
			if (di[i] == -1 || di[i] > di[cur] + times[cur][i]) {
				di[i] = di[cur] + times[cur][i];
				q.push(i);
			}
		}
	}
	return di[n + 1];
}

int main()
{
	FAST;
	cin >> start.first >> start.second >> dest.first >> dest.second >> n;
	canon[0] = start;
	for (int i = 1; i <= n; i++)
		cin >> canon[i].first >> canon[i].second;
	canon[n + 1] = dest;
	
	cout << Dijkstra();
	return 0;
}