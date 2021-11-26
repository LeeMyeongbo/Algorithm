#include <iostream>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define MAX 100001
using namespace std;

int N, K, visited[MAX];
priority_queue<pair<int, int>> q;			// (�ɸ� �ð�, ���� ��ġ)�� ���� (+1/-1 �� ���� *2 �� ���� �������� �ð��� �ٸ��Ƿ� ���ͽ�Ʈ�� Ȱ��)

int Solve()
{
	fill(visited, visited + MAX, MAX);
	q.push({ 0, N });
	visited[N] = 0;

	while (!q.empty()) {
		int cur = q.top().second;
		int num = -q.top().first;
		q.pop();

		if (cur == K)
			return num;

		if (cur * 2 < MAX && visited[cur * 2] > num) {			// ���� ��ġ���� *2 �� �� ���� ���
			visited[cur * 2] = num;
			q.push({ -num, cur * 2 });
		}
		if (cur + 1 < MAX && visited[cur + 1] > num + 1) {		// ���� ��ġ���� +1 �� �� ���� ���
			visited[cur + 1] = num + 1;
			q.push({ -(num + 1), cur + 1 });
		}
		if (cur - 1 >= 0 && visited[cur - 1] > num + 1) {		// ���� ��ġ���� -1 �� �� ���� ���
			visited[cur - 1] = num + 1;
			q.push({ -(num + 1), cur - 1 });
		}
	}
}

int main()
{
	FAST;
	cin >> N >> K;

	cout << Solve();
	return 0;
}