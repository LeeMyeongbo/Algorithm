#include <iostream>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

struct Node {
	int A, B, cnt;
};
int a, b, c, d;
bool A_visited[2][100001], B_visited[2][100001];		// A_visited[0][i] : B�� ������� ��, [1][i] : B�� ���� á�� �� A�� ���� �� i
queue<Node> q;											// B_visited[0][i] : A�� ������� ��, [1][i] : A�� ���� á�� �� B�� ���� �� i

int BFS()											// �� �� ���� A, B �� �� �ϳ��� �ݵ�� ��� �ְų� ���� �� ����!
{
	q.push({ 0, 0, 0 });
	A_visited[0][0] = B_visited[0][0] = true;

	while (!q.empty()) {
		Node node = q.front();
		q.pop();

		if (node.A == c && node.B == d)
			return node.cnt;

		if (!B_visited[1][node.B]) {				// A�� ���� ���� ä�� ��
			B_visited[1][node.B] = true;
			q.push({ a, node.B, node.cnt + 1 });
		}
		if (!B_visited[0][node.B]) {				// A�� ���� ��� ��
			B_visited[0][node.B] = true;
			q.push({ 0, node.B, node.cnt + 1 });
		}
		if (!A_visited[1][node.A]) {				// B�� ���� ���� ä�� ��
			A_visited[1][node.A] = true;
			q.push({ node.A, b, node.cnt + 1 });
		}
		if (!A_visited[0][node.A]) {				// B�� ���� ��� ��
			A_visited[0][node.A] = true;
			q.push({ node.A, 0, node.cnt + 1 });
		}
		if (node.A + node.B <= a && !A_visited[0][node.A + node.B]) {		// B ���� A�� ��� �ξ ��ġ�� ���� ��� (B�� ��� ��)
			A_visited[0][node.A + node.B] = true;
			q.push({ node.A + node.B, 0, node.cnt + 1 });
		}
		else if (node.A + node.B > a && !B_visited[1][node.A + node.B - a]) {	// B ���� A�� ��� ������ ��ĥ ��� (A�� ���� ��)
			B_visited[1][node.A + node.B - a] = true;
			q.push({ a, node.A + node.B - a, node.cnt + 1 });
		}
		if (node.A + node.B <= b && !B_visited[0][node.A + node.B]) {		// A ���� B�� ��� �ξ ��ġ�� ���� ��� (A�� ��� ��)
			B_visited[0][node.A + node.B] = true;
			q.push({ 0, node.A + node.B, node.cnt + 1 });
		}
		else if (node.A + node.B > b && !A_visited[1][node.A + node.B - b]) {	// A ���� B�� ��� ������ ��ĥ ��� (B�� ���� ��)
			A_visited[1][node.A + node.B - b] = true;
			q.push({ node.A + node.B - b, b, node.cnt + 1 });
		}
	}
	return -1;
}

int main()
{
	FAST;
	cin >> a >> b >> c >> d;
	cout << BFS();
	return 0;
}