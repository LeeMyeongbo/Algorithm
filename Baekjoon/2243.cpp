#include <iostream>
#define S 1048576					// 2^20
using namespace std;

int n, A, B, C, tree[2 * S];		// tree[1] ~ tree[S - 1] : 내부노드, tree[S] ~ tree[2 * S - 1] : 리프노드

void update(int idx, int diff)		// bottom-up 방식으로 갱신
{
	int node = idx + S - 1;
	while (node) {
		tree[node] += diff;
		node /= 2;
	}
}

int find(int left, int right, int node, int rank)
{
	int mid = (left + right) / 2;

	if (left == right) {
		update(left, -1);			// 1개 빼줘야 함!
		return left;
	}
	if (tree[node * 2] >= rank)
		return find(left, mid, node * 2, rank);								// 왼쪽 서브트리로 갈 때는 원래 순위 그대로 전달
	else
		return find(mid + 1, right, node * 2 + 1, rank - tree[node * 2]);	// 오른쪽 서브트리로 갈 때 원래 순위에서 왼쪽 서브트리 합 빼줌!
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> A;
		if (A == 1) {
			cin >> B;
			cout << find(1, S, 1, B) << "\n";
		}
		else {
			cin >> B >> C;
			update(B, C);
		}
	}
	return 0;
}