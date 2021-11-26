#include <iostream>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

struct Node {
	int a, b, c;
};
int A, B, C;
bool visited[201][201][201], c_bottle[201];		// [A][B][C]�� �湮üũ
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

		// A ���뿡 ���� ���� �� ���� B���뿡 ���� �ξ� ��
		if (node.a && node.a + node.b <= B && !visited[0][node.a + node.b][node.c]) {		// B���뿡 A������ ���� ��� �ξ �� ��ĥ ���
			visited[0][node.a + node.b][node.c] = true;
			q.push({ 0, node.a + node.b, node.c });
		}
		else if (node.a && node.a + node.b > B && !visited[node.a - (B - node.b)][B][node.c]) {		// ��ĥ ���
			visited[node.a - (B - node.b)][B][node.c] = true;
			q.push({ node.a - (B - node.b), B, node.c });
		}

		// A ���뿡�� C���뿡 ���� �ξ� ��
		if (node.a && node.a + node.c <= C && !visited[0][node.b][node.a + node.c]) {		// C���뿡 A������ ���� ��� �ξ �� ��ĥ ���
			visited[0][node.b][node.a + node.c] = true;
			q.push({ 0, node.b, node.a + node.c });
		}
		else if (node.a && node.a + node.c > C && !visited[node.a - (C - node.c)][node.b][C]) {		// ��ĥ ���
			visited[node.a - (C - node.c)][node.b][C] = true;
			q.push({ node.a - (C - node.c), node.b, C });
		}

		// B ���뿡�� A���뿡 �� �ξ� ��
		if (node.b && node.b + node.a <= A && !visited[node.b + node.a][0][node.c]) {		//A���뿡 B������ ���� ��� �ξ �� ��ĥ ���
			visited[node.b + node.a][0][node.c] = true;
			q.push({ node.b + node.a, 0, node.c });
		}
		else if (node.b && node.b + node.a > A && !visited[A][node.b - (A - node.a)][node.c]) {		// ��ĥ ���
			visited[A][node.b - (A - node.a)][node.c] = true;
			q.push({ A, node.b - (A - node.a), node.c });
		}

		// B ���뿡�� C���뿡 �� �ξ� ��
		if (node.b && node.b + node.c <= C && !visited[node.a][0][node.b + node.c]) {
			visited[node.a][0][node.b + node.c] = true;
			q.push({ node.a, 0, node.b + node.c });
		}
		else if (node.b && node.b + node.c > C && !visited[node.a][node.b - (C - node.c)][C]) {
			visited[node.a][node.b - (C - node.c)][C] = true;
			q.push({ node.a, node.b - (C - node.c), C });
		}
		
		// C ���뿡�� A���뿡 �� �ξ� ��
		if (node.c && node.c + node.a <= A && !visited[node.c + node.a][node.b][0]) {
			visited[node.c + node.a][node.b][0] = true;
			q.push({ node.c + node.a, node.b, 0 });
		}
		else if (node.c && node.c + node.a > A && !visited[A][node.b][node.c - (A - node.a)]) {
			visited[A][node.b][node.c - (A - node.a)] = true;
			q.push({ A, node.b, node.c - (A - node.a) });
		}

		// C ���뿡�� B���뿡 �� �ξ� ��
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