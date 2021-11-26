#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, v1, v2, K, group[101], length[101];		// group[i] : i�� ������ �� �� �׷쿡 ���ϴ���
vector<int> graph[101], ans;						// length[i] : i�� ������ �׷� ���� �� ���������� �ִ� �Ÿ� �� �ִ�
queue<pair<int, int>> q;

int BFS(int cur, int seq, bool chk)
{
	int Max = 0;
	bool visited[101] = { false, };
	q.push({ cur, 0 });
	visited[cur] = true;

	while (!q.empty()) {
		int cur = q.front().first;
		int num = q.front().second;
		q.pop();

		if (chk)
			group[cur] = seq;
		Max = max(Max, num);
		for (int i : graph[cur]) {
			if (!visited[i]) {
				q.push({ i, num + 1 });
				visited[i] = true;
			}
		}
	}
	return Max;
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}

	for (int i = 1; i <= N; i++) {
		if (!group[i]) {						// �ƿ� Ž���� �� ���� ������ ���
			length[i] = BFS(i, ++K, true);		// �� �� �׷쿡 ���ϴ��� üũ�ϸ鼭 BFS
			ans.push_back(i);
		}
		else {
			length[i] = BFS(i, K, false);		// �� ������ �� �� �׷쿡 ���ϴ��� üũ�Ǿ� ���� ��� BFS�� �ִ� �Ÿ��� ����
			int cur_group = group[i];
			ans[cur_group - 1] = length[ans[cur_group - 1]] > length[i] ? i : ans[cur_group - 1];
		}
	}
	cout << K << "\n";
	sort(ans.begin(), ans.end());
	for (int i : ans)
		cout << i << "\n";

	return 0;
}