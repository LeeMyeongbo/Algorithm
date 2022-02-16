#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

queue<pair<int, int>> q;
int N, K;
bool visited[11][1000001];

int BFS()
{
	q.push({ N, 0 });

	while (!q.empty()) {
		// 1. 큐에서 꺼냄
		int cur = q.front().first;
		int change = q.front().second;
		q.pop();

		// 2. 목적지인지 확인
		if (K == change)
			continue;

		// 3. 연결된 곳 순회
		char n[8] = "";
		int p = (int)log10(cur);
		int pos = p + 1;
		while (cur) {
			int mod = cur % 10;
			n[p--] = mod + '0';
			cur /= 10;
		}

		for (int i = 0; i < pos - 1; i++) {
			for (int j = i + 1; j < pos; j++) {
				swap(n[i], n[j]);

				// 4. 연결된 곳 갈 수 있는지 확인
				if (n[0] != '0') {
					int new_n = atoi(n);
					if (!visited[change + 1][new_n]) {
						// 5. 체크인
						visited[change + 1][new_n] = true;
						// 6. 큐 삽입
						q.push({ new_n, change + 1 });
					}
				}
				swap(n[i], n[j]);
			}
		}
	}
	for (int i = 1000000; i >= 0; i--)
		if (visited[K][i])
			return i;
	return -1;
}

int main()
{
	cin >> N >> K;
	
	cout << BFS();
	return 0;
}