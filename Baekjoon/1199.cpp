#include <iostream>
#include <stack>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

stack<pair<int, int>> graph[1000];
int N, idx, e;
bool possible = true, used[10000000];			// ����� ���� ��ȣ �����

void DFS(int i)
{
	while (true) {
		while (!graph[i].empty() && used[graph[i].top().second])
			graph[i].pop();							// �̹� ����� ���� �����ϴ� ����

		if (graph[i].empty())						// ���� �������� �� �̻� ����� ���� ������ ��� ��������
			break;

		pair<int, int> p = graph[i].top();
		graph[i].pop();

		used[p.second] = true;						// ���� ����ߴٴ� ǥ��
		DFS(p.first);
	}
	cout << i + 1 << " ";
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			cin >> e;
			if (i < j) {
				while (e--) {
					graph[i].push({ j, idx });
					graph[j].push({ i, idx++ });
				}
			}
		}
	for (int i = 0; i < N; i++)
		if (graph[i].size() % 2)
			possible = false;						// ���� �ϳ��� ������ Ȧ���� ���Ϸ� ȸ�� x

	if (possible)
		DFS(0);
	else
		cout << -1;

	return 0;
}