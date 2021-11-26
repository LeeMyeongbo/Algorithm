#include <iostream>
#include <map>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int T, n, m, pre[1000], root;		// root : ���� ��ȸ���� ���� Ʈ���� ��Ʈ�� �� ������ index
map<int, int> in;					// in : ���� ��ȸ �� (���� ��, index)�� ����

struct Tree {
	Tree* left, * right;
	int num;

	Tree(int n) {
		num = n;
		left = right = nullptr;
	}
};
Tree* Root;

void Make_Tree(Tree* &cur, int first, int last)	// first, last : ���� ���ǰ� �ִ� ����Ʈ���� index (first <= index < last)
{
	if (first >= last)
		return;
	cur = new Tree(pre[root]);			// ���� ��ȸ������ �� ����Ʈ���� ��Ʈ�� �ش��ϴ� ������ index�� ���ʿ������� �������� ���������� ��
	int root_index = in[pre[root++]];			// ���� ��ȸ���� �� ���� Ʈ���� ��Ʈ�� index�� ã�Ƽ� root_index�� ����
	Make_Tree(cur->left, first, root_index);
	Make_Tree(cur->right, root_index + 1, last);
}

void postorder(Tree*& node)
{
	if (node) {
		postorder(node->left);
		postorder(node->right);
		cout << node->num << " ";
		delete(node);
	}
}

int main()
{
	FAST;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> pre[i];
		for (int i = 0; i < n; i++) {
			cin >> m;
			in.insert({ m, i });		// (��� ��, index)�� ����
		}
		Make_Tree(Root, 0, n);
		postorder(Root);
		cout << "\n";

		root = 0;
		in.clear();
	}
	return 0;
}