#include <iostream>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

struct Node {
	int a, b, c;
};
int A, B, C;
bool visited[201][201][201], c_bottle[201];		// [A][B][C]로 방문체크
queue<Node> q;

void Solve()
{
	q.push({ 0, 0, C });
	visited[A][B][C] = true;

	while (!q.empty()) {
		Node node = q.front();
		q.pop();

		if (!node.a && !c_bottle[node.c])
			c_bottle[node.c] = true;

		// A 물통에 물이 있을 때 먼저 B물통에 물을 부어 봄
		if (node.a && node.a + node.b <= B && !visited[0][node.a + node.b][node.c]) {		// B물통에 A물통의 물을 모두 부어도 안 넘칠 경우
			visited[0][node.a + node.b][node.c] = true;
			q.push({ 0, node.a + node.b, node.c });
		}
		else if (node.a && node.a + node.b > B && !visited[node.a - (B - node.b)][B][node.c]) {		// 넘칠 경우
			visited[node.a - (B - node.b)][B][node.c] = true;
			q.push({ node.a - (B - node.b), B, node.c });
		}

		// A 물통에서 C물통에 물을 부어 봄
		if (node.a && node.a + node.c <= C && !visited[0][node.b][node.a + node.c]) {		// C물통에 A물통의 물을 모두 부어도 안 넘칠 경우
			visited[0][node.b][node.a + node.c] = true;
			q.push({ 0, node.b, node.a + node.c });
		}
		else if (node.a && node.a + node.c > C && !visited[node.a - (C - node.c)][node.b][C]) {		// 넘칠 경우
			visited[node.a - (C - node.c)][node.b][C] = true;
			q.push({ node.a - (C - node.c), node.b, C });
		}

		// B 물통에서 A물통에 물 부어 봄
		if (node.b && node.b + node.a <= A && !visited[node.b + node.a][0][node.c]) {		//A물통에 B물통의 물을 모두 부어도 안 넘칠 경우
			visited[node.b + node.a][0][node.c] = true;
			q.push({ node.b + node.a, 0, node.c });
		}
		else if (node.b && node.b + node.a > A && !visited[A][node.b - (A - node.a)][node.c]) {		// 넘칠 경우
			visited[A][node.b - (A - node.a)][node.c] = true;
			q.push({ A, node.b - (A - node.a), node.c });
		}

		// B 물통에서 C물통에 물 부어 봄
		if (node.b && node.b + node.c <= C && !visited[node.a][0][node.b + node.c]) {
			visited[node.a][0][node.b + node.c] = true;
			q.push({ node.a, 0, node.b + node.c });
		}
		else if (node.b && node.b + node.c > C && !visited[node.a][node.b - (C - node.c)][C]) {
			visited[node.a][node.b - (C - node.c)][C] = true;
			q.push({ node.a, node.b - (C - node.c), C });
		}
		
		// C 물통에서 A물통에 물 부어 봄
		if (node.c && node.c + node.a <= A && !visited[node.c + node.a][node.b][0]) {
			visited[node.c + node.a][node.b][0] = true;
			q.push({ node.c + node.a, node.b, 0 });
		}
		else if (node.c && node.c + node.a > A && !visited[A][node.b][node.c - (A - node.a)]) {
			visited[A][node.b][node.c - (A - node.a)] = true;
			q.push({ A, node.b, node.c - (A - node.a) });
		}

		// C 물통에서 B물통에 물 부어 봄
		if (node.c && node.c + node.b <= B && !visited[node.a][node.c + node.b][0]) {
			visited[node.a][node.c + node.b][0] = true;
			q.push({ node.a, node.c + node.b, 0 });
		}
		else if (node.c && node.c + node.b > B && !visited[node.a][B][node.c - (B - node.b)]) {
			visited[node.a][B][node.c - (B - node.b)] = true;
			q.push({ node.a, B, node.c - (B - node.b) });
		}
	}
	for (int i = 0; i <= 200; i++)
		if (c_bottle[i])
			cout << i << " ";
}

int main()
{
	FAST;
	cin >> A >> B >> C;
	Solve();
	return 0;
}