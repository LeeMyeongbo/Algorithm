#include <iostream>
#include <queue>
#include <set>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

struct Node {
	int A, B, cnt;
};
int a, b, c, d;
queue<Node> q;
set<pair<int, int>> visited;

void Fill_or_Empty(int A, int B, int cnt)
{
	if (!visited.count({ A, B })) {
		visited.insert({ A, B });
		q.push({ A, B, cnt + 1 });
	}
}

int BFS()
{
	visited.insert({ 0, 0 });
	q.push({ 0, 0, 0 });

	while (!q.empty()) {
		Node node = q.front();
		q.pop();

		if (node.A == c && node.B == d)
			return node.cnt;

		Fill_or_Empty(a, node.B, node.cnt);			// A ���� ä��
		Fill_or_Empty(node.A, b, node.cnt);			// B ���� ä��
		Fill_or_Empty(0, node.B, node.cnt);			// A ���
		Fill_or_Empty(node.A, 0, node.cnt);			// B ���

		if (node.A + node.B <= b && !visited.count({ 0, node.A + node.B })) {		// A���� B�� �� ��� �ξ ��ġ�� ���� ���
			visited.insert({ 0, node.A + node.B });
			q.push({ 0, node.A + node.B, node.cnt + 1 });
		}
		else if (node.A + node.B > b && !visited.count({ node.A + node.B - b, b })) {	// A���� B�� �� ��� �ξ ��ĥ ���
			visited.insert({ node.A + node.B - b, b });
			q.push({ node.A + node.B - b, b, node.cnt + 1 });
		}
		if (node.A + node.B <= a && !visited.count({ node.A + node.B, 0 })) {		// B���� A�� �� ��� �ξ ��ġ�� ���� ���
			visited.insert({ node.A + node.B, 0 });
			q.push({ node.A + node.B, 0, node.cnt + 1 });
		}
		else if (node.A + node.B > a && !visited.count({ a, node.A + node.B - a })) {	// B���� A�� �� ��� �ξ ��ĥ ���
			visited.insert({ a, node.A + node.B - a });
			q.push({ a, node.A + node.B - a, node.cnt + 1 });
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