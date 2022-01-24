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
		// 1. ť���� ����
		int cur = q.front().first;
		int change = q.front().second;
		q.pop();

		// 2. ���������� Ȯ��
		if (K == change)
			continue;

		// 3. ����� �� ��ȸ
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

				// 4. ����� �� �� �� �ִ��� Ȯ��
				if (n[0] != '0') {
					int new_n = atoi(n);
					if (!visited[change + 1][new_n]) {
						// 5. üũ��
						visited[change + 1][new_n] = true;
						// 6. ť ����
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