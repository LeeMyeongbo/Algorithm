#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

int N, v1, v2, visited[100000];
bool v[100001];
vector<int> graph[100001];
queue<int> q;

bool BFS()
{
	int n = 0;

	v[1] = true;
	q.push(1);
	if (visited[n++] != 1)						// ���������� ������ 1
		return false;

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		set<int> orders;
		for (int i : graph[cur])
			if (!v[i]) {
				v[i] = true;
				orders.insert(i);				// �ϴ� ���� ������ ����Ǿ� �ִ� ������ ��� set���ٰ� �ӽ� ����
			}
		
		for (int i = n; i < n + orders.size(); i++) {
			if (orders.count(visited[i]))		// �Է¹��� BFS �湮�������� setũ�⸸ŭ ���Ǹ� ������ set�� ���������
				q.push(visited[i]);				// �� �� ť�� ����!
			else
				return false;
		}
		n += orders.size();
	}
	return true;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N - 1; i++) {
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}
	for (int i = 0; i < N; i++)
		cin >> visited[i];
	
	if (BFS())
		cout << 1;
	else
		cout << 0;

	return 0;
}