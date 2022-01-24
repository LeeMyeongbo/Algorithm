#include <iostream>
using namespace std;

struct Node {
	int val;
	Node* left, * right;
};
Node* root;
int n;

void init(Node** root, int num)
{
	if (*root) {
		if ((*root)->val > num)
			init(&(*root)->left, num);
		else
			init(&(*root)->right, num);
	}
	else {
		*root = new Node;
		(*root)->val = num;
		(*root)->left = (*root)->right = nullptr;
	}
}

void postorder(Node* root)
{
	if (root) {
		postorder(root->left);
		postorder(root->right);
		cout << root->val << endl;

		delete root;
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	while (true) {
		cin >> n;
		if (cin.eof())
			break;

		init(&root, n);
	}
	postorder(root);

	return 0;
}