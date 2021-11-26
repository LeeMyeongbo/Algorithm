#include <iostream>
#include <vector>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, X, Y, A, B, pre[100101];
bool visited[100101];
vector<int> graph[100101];		// 1 ~ N : √˛, N + 1 ~ N + M : ø§∏Æ∫£¿Ã≈Õ
queue<pair<int, int>> q;		// («ˆ¿Á ¡§¡°, ø§∏Æ∫£¿Ã≈Õ ≈∫ »Ωºˆ)

void backtrack(int cur)
{
	if (cur == A)
		return;
	backtrack(pre[cur]);
	if (cur > N)
		cout << cur - N << "\n";
}

void BFS()
{
	q.push({ A, 0 });
	visited[A] = true;

	while (!q.empty()) {
		int cur = q.front().first;
		int num = q.front().second;
		q.pop();

		if (cur == B) {
			cout << num << "\n";
			backtrack(B);
			return;
		}
		for (int& i : graph[cur]) {
			if (!visited[i]) {
				i > N ? q.push({ i, num + 1 }) : q.push({ i, num });
				visited[i] = true;
				pre[i] = cur;
			}
		}
	}
	cout << -1;
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 1; i <= M; i++) {
		cin >> X >> Y;
		while (X <= N) {
			graph[N + i].push_back(X);
			graph[X].push_back(N + i);
			X += Y;
		}
	}
	cin >> A >> B;

	BFS();
	return 0;
}