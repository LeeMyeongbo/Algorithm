#include <iostream>
using namespace std;

int N, Case, cur, l, r;
struct Node {
	char c;
	int right, left;
} node[101];
char ch;

void inorder(Node node[], int root)
{
	if (root) {
		inorder(node, node[root].left);
		cout << node[root].c;
		inorder(node, node[root].right);
	}
}

int main(int argc, char** argv)
{
	while (true) {
		cin >> N;
		if (cin.eof())
			return 0;

		bool is_all = false;
		for (int i = 0; i < N; i++) {
			cin >> cur >> ch;
			node[cur] = { ch, 0, 0 };
			if (!is_all) {
				cin >> l;
				if (l == N)
					is_all = true;
				node[cur].left = l;
			}
			if (!is_all) {
				cin >> r;
				if (r == N)
					is_all = true;
				node[cur].right = r;
			}
		}

		cout << "#" << ++Case << " ";
		inorder(node, 1);
		cout << endl;

		for (int i = 1; i <= N; i++)
			node[i] = { 0, 0, 0 };
	}
}