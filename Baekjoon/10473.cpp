#include <iostream>
#include <queue>
#include <cmath>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

pair<double, double> start, dest, canon[102];
priority_queue<int, vector<int>, greater<int>> q;
double times[102][102], di[102];
int n;

void get_time()			// ��� ������ �� ���� & �� �������� �ɸ��� �ð��� �ּڰ� ����
{
	for (int j = 1; j <= n + 1; j++)		// ��� ���������� �� �������� �پ ���ۿ� �����Ƿ� �پ�� �� �ɸ��� �ð��� ����
		times[0][j] = times[j][0] = sqrt(pow(canon[0].first - canon[j].first, 2) + pow(canon[0].second - canon[j].second, 2)) / 5;
	
	for (int i = 1; i <= n + 1; i++) {		// �� �������� �ٸ� �������� or ���� ����������
		for (int j = 1; j <= n + 1; j++) {	// ����Ÿ�� �پ�µ� �ɸ��� �ð��� �پ�� ���� �� �ɸ��� �ð��� �ּڰ��� ����
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

	while (!q.empty()) {			// ���ͽ�Ʈ��� ����������� ������������ �ּ� �ð� ����
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