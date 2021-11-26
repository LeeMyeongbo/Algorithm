#include <iostream>
using namespace std;

struct Tree {
	Tree* left, * right;
	int cur;
};
int N, U, V;
long long K;
Tree tree[200001];

int dfs(Tree* node, long long cur)
{
	if (node->left && node->right) {				// ���� �ڽ��� ��� ������ ���
		if (cur % 2)
			return dfs(node->left, cur / 2 + 1);	// ���� ���� Ȧ���� ��� 2�� ���� ���� +1�� �ϰ� �������� �̵�
		else
			return dfs(node->right, cur / 2);		// ¦����� 2�� ������ ������ �̵�
	}
	else if (node->left)
		return dfs(node->left, cur);		// ���� �ڽĹۿ� ���ٸ� �״�� �������� �̵�
	else if (node->right)
		return dfs(node->right, cur);		// ������ �ۿ� ���ٸ� �״�� ���������� �̵�
	else
		return node->cur;					// ������ �ٴٸ��� ���� ������ index ��ȯ
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> U >> V;
		if (U != -1)
			tree[i].left = tree + U;	// ���� �ڽ��� �����Ѵٸ� ����
		if (V != -1)
			tree[i].right = tree + V;	// ������ �ڽ��� �����Ѵٸ� ����
		tree[i].cur = i;
	}
	cin >> K;

	cout << dfs(tree + 1, K);
	return 0;
}