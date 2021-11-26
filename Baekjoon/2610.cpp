#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, v1, v2, K, group[101], length[101];		// group[i] : i번 정점이 몇 번 그룹에 속하는지
vector<int> graph[101], ans;						// length[i] : i번 정점이 그룹 내의 각 정점까지의 최단 거리 중 최댓값
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
		if (!group[i]) {						// 아예 탐색한 적 없는 정점일 경우
			length[i] = BFS(i, ++K, true);		// 몇 번 그룹에 속하는지 체크하면서 BFS
			ans.push_back(i);
		}
		else {
			length[i] = BFS(i, K, false);		// 현 정점이 몇 번 그룹에 속하는지 체크되어 있을 경우 BFS로 최대 거리만 구함
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