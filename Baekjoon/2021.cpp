#include <iostream>
#include <vector>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, L, n, Start, End;
bool visited[200001];
vector<int> graph[200001];			// �� ���� ����� �뼱�� �ϳ��ϳ� �� �������� �����ϱ⿣ �ʹ� ���� -> �뼱�� �ϳ��� �������� ��!
queue<pair<int, int>> q;			// (���� ����, �뼱 �̿� Ƚ��)

int Solve()
{
	q.push({ Start, 0 });
	visited[Start] = true;

	while (!q.empty()) {
		int cur = q.front().first;
		int num = q.front().second;
		q.pop();

		if (cur == End) {			// Start�� End�� ���� ��쵵 ���� ����
			if (!num)
				return 0;
			return num - 1;
		}

		for (int i : graph[cur]) {
			if (!visited[i]) {		// N������ ū �������� ���� �� �뼱 �̿��ϴ� ���̹Ƿ� +1, �׷��� ������ �뼱���� ������ ���̹Ƿ� �״��
				i > N ? q.push({ i, num + 1 }) : q.push({ i, num });
				visited[i] = true;
			}
		}
	}
	return -1;
}

int main()
{
	FAST;
	cin >> N >> L;
	for (int i = N + 1; i <= N + L; i++) {		// 1������ N�� ������ ��, N + 1������ N + L�� ���������� �뼱
		while (1) {
			cin >> n;
			if (n == -1)
				break;
			graph[n].push_back(i);
			graph[i].push_back(n);
		}
	}
	cin >> Start >> End;

	cout << Solve();
	return 0;
}