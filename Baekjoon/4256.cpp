#include <iostream>
#include <map>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int T, n, m, pre[1000], root;		// root : 전위 순회에서 서브 트리의 루트로 들어갈 정점의 index
map<int, int> in;					// in : 중위 순회 때 (정점 값, index)로 저장

struct Tree {
	Tree* left, * right;
	int num;

	Tree(int n) {
		num = n;
		left = right = nullptr;
	}
};
Tree* Root;

void Make_Tree(Tree* &cur, int first, int last)	// first, last : 현재 살피고 있는 서브트리의 index (first <= index < last)
{
	if (first >= last)
		return;
	cur = new Tree(pre[root]);			// 전위 순회에서는 각 서브트리의 루트에 해당하는 정점의 index가 왼쪽에서부터 차근차근 오른쪽으로 옴
	int root_index = in[pre[root++]];			// 중위 순회에서 현 서브 트리의 루트의 index를 찾아서 root_index에 저장
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
			in.insert({ m, i });		// (노드 값, index)로 저장
		}
		Make_Tree(Root, 0, n);
		postorder(Root);
		cout << "\n";

		root = 0;
		in.clear();
	}
	return 0;
}