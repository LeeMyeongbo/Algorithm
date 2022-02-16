#include <iostream>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N;
struct Tree {
	char c;
	Tree* left, * right;

	Tree(char c) {
		this->c = c;
		left = right = nullptr;
	}
};
Tree* nodes[26];
char Node, Left, Right;

void Add_left(Tree* parent, char c) {
	nodes[c - 'A'] = new Tree(c);
	parent->left = nodes[c - 'A'];
}

void Add_right(Tree* parent, char c) {
	nodes[c - 'A'] = new Tree(c);
	parent->right = nodes[c - 'A'];
}

void preorder(Tree* node)
{
	if (node) {
		cout << node->c;
		preorder(node->left);
		preorder(node->right);
	}
}

void inorder(Tree* node)
{
	if (node) {
		inorder(node->left);
		cout << node->c;
		inorder(node->right);
	}
}

void postorder(Tree* node)
{
	if (node) {
		postorder(node->left);
		postorder(node->right);
		cout << node->c;
	}
}

int main()
{
	FAST;
	cin >> N;
	nodes[0] = new Tree('A');

	for (int i = 0; i < N; i++) {
		cin >> Node >> Left >> Right;
		if (Left != '.')
			Add_left(nodes[Node - 'A'], Left);
		if (Right != '.')
			Add_right(nodes[Node - 'A'], Right);
	}
	preorder(nodes[0]);
	cout << "\n";
	inorder(nodes[0]);
	cout << "\n";
	postorder(nodes[0]);
	return 0;
}