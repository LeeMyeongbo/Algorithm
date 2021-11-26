#include <iostream>
#include <vector>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, v1, v2;
vector<int> graph[2000];
bool visited[2000], complete;

bool dfs(int cur, int depth)
{
	visited[cur] = true;
	if (depth == 4)
		return true;
	for (int i : graph[cur])
		if (!visited[i] && dfs(i, depth + 1))
			return true;
	visited[cur] = false;		// Ž���ϰ� �ٽ� ��� �������� �� �湮�� Ǯ����� �� (���� ���� Ž���ؼ� ���̰� 4�� �� ���� �����Ƿ�)
	return false;				// ���̰� 4�� �Ǹ� ������ �����ϹǷ� �ߺ��� ����ص� �� (�����ٳ� ���� ���� �ִ� 2000 �̹Ƿ�)
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int e = 0; e < M; e++) {
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}
	for (int i = 0; i < N; i++) {
		if (dfs(i, 0)) {
			complete = true;
			break;
		}
	}
	if (complete)
		cout << 1;
	else
		cout << 0;
	return 0;
}