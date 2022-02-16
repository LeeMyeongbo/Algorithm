#include <iostream>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

struct Node {
	int A, B, cnt;
};
int a, b, c, d;
bool A_visited[2][100001], B_visited[2][100001];	// A_visited[0][i] : B가 비어있을 때, [1][i] : B가 가득 찼을 때 A의 물의 양 i
queue<Node> q;										// B_visited[0][i] : A가 비어있을 때, [1][i] : A가 가득 찼을 때 B의 물의 양 i

int BFS()											// 매 번 마다 A, B 둘 중 하나는 반드시 비어 있거나 가득 차 있음!
{
	q.push({ 0, 0, 0 });
	A_visited[0][0] = B_visited[0][0] = true;

	while (!q.empty()) {
		Node node = q.front();
		q.pop();

		if (node.A == c && node.B == d)
			return node.cnt;

		if (!B_visited[1][node.B]) {				// A에 물을 가득 채울 때
			B_visited[1][node.B] = true;
			q.push({ a, node.B, node.cnt + 1 });
		}
		if (!B_visited[0][node.B]) {				// A에 물을 비울 때
			B_visited[0][node.B] = true;
			q.push({ 0, node.B, node.cnt + 1 });
		}
		if (!A_visited[1][node.A]) {				// B에 물을 가득 채울 때
			A_visited[1][node.A] = true;
			q.push({ node.A, b, node.cnt + 1 });
		}
		if (!A_visited[0][node.A]) {				// B에 물을 비울 때
			A_visited[0][node.A] = true;
			q.push({ node.A, 0, node.cnt + 1 });
		}
		if (node.A + node.B <= a && !A_visited[0][node.A + node.B]) {		// B 물을 A에 모두 부어도 넘치지 않을 경우 (B가 비게 됨)
			A_visited[0][node.A + node.B] = true;
			q.push({ node.A + node.B, 0, node.cnt + 1 });
		}
		else if (node.A + node.B > a && !B_visited[1][node.A + node.B - a]) {	// B 물을 A에 모두 부으면 넘칠 경우 (A가 가득 참)
			B_visited[1][node.A + node.B - a] = true;
			q.push({ a, node.A + node.B - a, node.cnt + 1 });
		}
		if (node.A + node.B <= b && !B_visited[0][node.A + node.B]) {		// A 물을 B에 모두 부어도 넘치지 않을 경우 (A가 비게 됨)
			B_visited[0][node.A + node.B] = true;
			q.push({ 0, node.A + node.B, node.cnt + 1 });
		}
		else if (node.A + node.B > b && !A_visited[1][node.A + node.B - b]) {	// A 물을 B에 모두 부으면 넘칠 경우 (B가 가득 참)
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
