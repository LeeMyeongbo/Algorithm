#include <iostream>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, map[1500][1500];
priority_queue<pair<int, pair<int, int>>> q;

int Solve()
{
	for (int i = 0; i < N; i++)
		q.push({ map[N - 1][i], {N - 1, i} });
	
	for (int i = 0; i < N - 1; i++) {
		pair<int, int> p = q.top().second;
		q.pop();
		q.push({ map[p.first - 1][p.second], {p.first - 1, p.second} });
	}
	return q.top().first;
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];

	cout << Solve();
	return 0;
}