#include <iostream>
#include <algorithm>
#define MAX 10000000000
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int n, m, a, b;
long long graph[101][101], c;

void Floyd()			// �÷��̵� �ͼ� ���!!
{
	for (int pass = 1; pass <= n; pass++) {			// ��ġ�� ����
		for (int s = 1; s <= n; s++) {				// ��� ����
			for (int d = 1; d <= n; d++) {			// ���� ����
				graph[s][d] = min(graph[s][d], graph[s][pass] + graph[pass][d]);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (graph[i][j] < MAX)
				cout << graph[i][j] << " ";
			else
				cout << 0 << " ";
		}
		cout << "\n";
	}
}

int main()
{
	FAST;
	cin >> n >> m;
	for (int i = 0; i <= n; i++) {
		fill(graph[i], graph[i] + n + 1, MAX);
		graph[i][i] = 0;
	}

	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		graph[a][b] = min(graph[a][b], c);
	}

	Floyd();
	return 0;
}