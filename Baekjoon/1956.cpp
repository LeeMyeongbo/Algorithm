#include <iostream>
#include <algorithm>
#include <cstring>
#define MAX 1000000000
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int V, E, graph[401][401], a, b, c, ans = MAX;

int Solve()
{
	for (int pass = 1; pass <= V; pass++) {					// ���İ��� ����
		for (int start = 1; start <= V; start++) {			// ��� ����
			for (int end = 1; end <= V; end++) {			// ���� ����
				graph[start][end] = min(graph[start][end], graph[start][pass] + graph[pass][end]);
			}
		}
	}
	for (int v = 1; v <= V; v++)
		ans = min(ans, graph[v][v]);
	
	if (ans == MAX)
		return -1;
	return ans;
}

int main()
{
	FAST;
	cin >> V >> E;
	for (int i = 1; i <= V; i++)
		for (int j = 1; j <= V; j++)
			graph[i][j] = MAX;

	for (int i = 0; i < E; i++) {
		cin >> a >> b >> c;
		graph[a][b] = c;
	}
	
	cout << Solve();
	return 0;
}