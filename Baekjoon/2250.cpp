#include <iostream>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, node, L, R, width[10001], most_left[10001], col = 1;		// width[i] : 레벨 i의 넓이
bool visited[10001];											// most_left[i] : 레벨 i에서 제일 왼쪽의 노드 열 번호
struct Tree {
	Tree* left, * right;
};
Tree tree[10001], * root;

void inorder(Tree* node, int level)					// 중위 순회를 이용하면 매우 간편
{
	if (node) {
		inorder(node->left, level + 1);
		if (!most_left[level])
			most_left[level] = col;
		else
			width[level] = col - most_left[level] + 1;
		col++;
		inorder(node->right, level + 1);
	}
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> node >> L >> R;
		if (L > -1) {
			tree[node].left = tree + L;
			visited[L] = true;				// 왼쪽 자식으로 온 노드 체크
		}
		if (R > -1) {
			tree[node].right = tree + R;
			visited[R] = true;				// 오른쪽 자식으로 온 노드 체크
		}
	}
	for (int i = 1; i <= N; i++)
		if (!visited[i])					// 왼쪽 자식도 아니고 오른쪽 자식도 아닌 노드가 루트
			root = tree + i;
	fill(width, width + N + 1, 1);

	inorder(root, 1);

	int ans_level = 0, ans_width = 0;
	for(int i = 1; i <= N; i++)
		if (ans_width < width[i]) {
			ans_width = width[i];
			ans_level = i;
		}

	cout << ans_level << " " << ans_width;
	return 0;
}