#include <iostream>
#include <map>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int n, m, post[100000], root;
map<int, int> in;

struct Tree {
	Tree* left, * right;
	int num;

	Tree(int n) {
		num = n;
		left = right = nullptr;
	}
};

void Make_Tree(Tree*& cur, int left_end, int right_end)
{
	if (left_end >= right_end)
		return;

	cur = new Tree(post[root]);					// 후위 순회에서는 각 서브트리의 루트에 해당하는 정점의 index가 오른쪽에서 차근차근 왼쪽으로 옴
	int root_index = in[post[root--]];			

	Make_Tree(cur->right, root_index + 1, right_end);	// 거꾸로 오른쪽 서브트리부터 차근차근 분할 정복
	Make_Tree(cur->left, left_end, root_index);			// 오른쪽 서브트리 완료되면 왼쪽 ㄱ
}

void preorder(Tree*& node)
{
	if (node) {
		cout << node->num << " ";
		preorder(node->left);
		preorder(node->right);
		delete(node);
	}
}

int main()
{
	FAST;
	Tree* Root = nullptr;
	cin >> n;
	root = n - 1;
	for (int i = 0; i < n; i++) {
		cin >> m;
		in.insert({ m, i });
	}
	for (int i = 0; i < n; i++)
		cin >> post[i];

	Make_Tree(Root, 0, n);
	preorder(Root);

	return 0;
}