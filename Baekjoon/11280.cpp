#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define STD 10000
using namespace std;

int N, M, i, j, num, seq[2 * STD + 1], scc[2 * STD + 1], scc_num;
bool complete[2 * STD + 1];
vector<int> graph[2 * STD + 1];
stack<int> s;

int DFS(int cur)
{
	seq[cur] = ++num;
	int parent = num;
	s.push(cur);

	for (int& v : graph[cur]) {
		if (!seq[v])
			parent = min(parent, DFS(v));
		else if (!complete[v])
			parent = min(parent, seq[v]);
	}
	if (parent == seq[cur]) {
		scc_num++;
		while (!s.empty()) {
			int v = s.top();
			s.pop();

			complete[v] = true;
			scc[v] = scc_num;
			if (cur == v)
				break;
		}
	}
	return parent;
}

int Determine()
{
	for (int v = 1; v <= N; v++)
		if (scc[STD + v] == scc[STD - v])		// 만약 v와 ~v가 같은 scc에 속한다면 ~v → v & v → ~v가 동시에 성립하게 됨 (말도 안되지)
			return 0;
	return 1;
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int m = 0; m < M; m++) {
		cin >> i >> j;								// i ▽ j 임을 나타낼 때
		graph[STD + -i].push_back(STD + j);			// ~i → j (i가 거짓일 때 j는 반드시 참이여야 함)
		graph[STD + -j].push_back(STD + i);			// ~j → i (j가 거짓일 때 i는 반드시 참이여야 함)
	}
	for (int v = 1; v <= N; v++) {					// 1, -1, 2, -2... 순으로 scc 형성
		if (!complete[STD + v])
			DFS(STD + v);
		if (!complete[STD - v])
			DFS(STD - v);
	}
	cout << Determine();
	return 0;
}