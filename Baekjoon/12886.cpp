#include <iostream>
#include <queue>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int A, B, C, Sum;
bool num[2001][2001];			// [제일 큰 숫자][제일 작은 숫자]에 방문 체크 (큰 숫자 작은 숫자 따로따로 말고 쌍으로 방문 체크할 필요 있음)
queue<pair<int, int>> q;

int Solve()
{
	int n[3];
	int M = max(max(A, B), C);
	int m = min(min(A, B), C);
	q.push({ M, m });
	num[M][m] = true;

	while (!q.empty()) {
		n[0] = q.front().first;
		n[1] = q.front().second;
		n[2] = Sum - n[0] - n[1];
		q.pop();

		if (n[0] == n[1] && n[1] == n[2])
			return 1;

		for (int i = 0; i < 3; i++) {
			if (n[i] != n[(i + 1) % 3]) {
				int Y = max(n[i], n[(i + 1) % 3]);
				int X = min(n[i], n[(i + 1) % 3]);
				int Big = max(2 * X, Y - X);
				int Small = min(2 * X, Y - X);

				M = max(Big, n[(i + 2) % 3]);
				m = min(Small, n[(i + 2) % 3]);

				if (!num[M][m]) {
					num[M][m] = true;
					q.push({ M, m });
				}
			}
		}
	}
	return 0;
}

int main()
{
	FAST;
	cin >> A >> B >> C;
	Sum = A + B + C;
	cout << Solve();
	return 0;
}