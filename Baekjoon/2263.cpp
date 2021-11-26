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

	cur = new Tree(post[root]);					// ���� ��ȸ������ �� ����Ʈ���� ��Ʈ�� �ش��ϴ� ������ index�� �����ʿ��� �������� �������� ��
	int root_index = in[post[root--]];			

	Make_Tree(cur->right, root_index + 1, right_end);	// �Ųٷ� ������ ����Ʈ������ �������� ���� ����
	Make_Tree(cur->left, left_end, root_index);			// ������ ����Ʈ�� �Ϸ�Ǹ� ���� ��
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