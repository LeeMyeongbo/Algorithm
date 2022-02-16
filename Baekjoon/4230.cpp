#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define MAX 30
using namespace std;

int N, M, n1, n2, order, seq[2 * MAX + 1], scc_num, scc_index[2 * MAX + 1];
bool complete[2 * MAX + 1];
char h_w1, h_w2;
vector<int> graph[2 * MAX + 1];		// h일 경우에는 MAX보다 크고 w일 경우에는 MAX보다 작음
stack<int> s;

int dfs(int cur)				    // 같은 진리값을 가지는 요소끼리 SCC로 묶어줌
{
	seq[cur] = ++order;
	int par = order;
	s.push(cur);

	for (int& i : graph[cur]) {
		if (!seq[i])
			par = min(par, dfs(i));
		else if (!complete[i])
			par = min(par, seq[i]);
	}
	if (par == seq[cur]) {
		scc_num++;
		while (!s.empty()) {
			int v = s.top();
			s.pop();

			complete[v] = true;
			scc_index[v] = scc_num;
			if (v == cur)
				break;
		}
	}
	return par;
}

bool chk()			// -x와 x가 같은 scc에 속하는지 체크 (속하면 성립x)
{
	for (int i = 1; i <= N; i++)
		if (scc_index[MAX - i] && scc_index[MAX + i] && scc_index[MAX - i] == scc_index[MAX + i])
			return false;
	return true;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	while (1) {
		cin >> N >> M;
		if (!N && !M)
			return 0;

		for (int i = 0; i < M; i++) {			// 여기서 간과하면 안될 것 : 철승이와 보람이도 불륜 저지를 수 있음!
			cin >> n1 >> h_w1 >> n2 >> h_w2;	// 입력으로 주어지는 값의 절댓값 + 1을 하고 그래프 형성 (0->1, 1->2, ...  (n-1)->n)
			n1++, n2++;
			if (h_w1 == 'w')
				n1 *= -1;
			if (h_w2 == 'w')
				n2 *= -1;
			graph[MAX + n1].push_back(MAX - n2);	// 불륜끼린 같이 있으면 안되므로
			graph[MAX + n2].push_back(MAX - n1);
		}
		graph[MAX - 1].push_back(MAX + 1);		// 철승이를 무조건 뽑는다 가정 (1 ▽ 1) (항상 뽑고 싶은 게 있으면 이렇게 하는 거 기억!)

		for (int i = MAX - N; i <= MAX + N; i++)
			if (i != MAX && !complete[i])
				dfs(i);

		if (chk()) {
			for (int i = 2; i <= N; i++) {		// 원래는 +x의 scc 번호가 -x보다 클 경우 x번째를 false(='w')로 처리하는 게 국룰 (철승이 줄)
				cout << i - 1;
				scc_index[MAX - i] < scc_index[MAX + i] ? cout << "h " : cout << "w ";		// 보람이 줄 : 철승이가 앉은 줄의 반대로 처리
			}
			cout << "\n";
		}
		else
			cout << "bad luck\n";

		order = scc_num = 0;
		fill(seq, seq + 2 * MAX + 1, 0);
		fill(scc_index, scc_index + 2 * MAX + 1, 0);
		fill(complete, complete + 2 * MAX + 1, false);
		for (int i = MAX - N; i <= MAX + N; i++)
			graph[i].clear();
	}
}
