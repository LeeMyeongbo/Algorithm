#include <iostream>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, value, Left, Right, num[100000], from, to;
char op;

struct Tree {
	Tree* left, * right;
	int value;
	char op;
	bool is_Max;
} tree[200005];

void preorder(Tree* node, bool is_Max)			// is_Max : ���� ����� �ִ�, �ּ� ���� (�ִ��� ���;� �� �� true, �ּҿ��� �� �� false)
{
	if (node) {
		node->is_Max = is_Max;
		preorder(node->left, is_Max);			// ���� �ڽ� ���� ������ �θ� ����� �ִ�, �ּ� ���ο� ���ƾ� ��
		if (node->op == '-')					// ���� ������ ����� �����ڰ� '-'�� ���
			preorder(node->right, !is_Max);		// ������ �ڽ� ���� �� ���� �θ� ����� �ִ�, �ּ� ���ο� �ݴ밡 �Ǿ�� ��
		else
			preorder(node->right, is_Max);		// �����ڰ� '+'�̸� ������ �ڽĵ� �θ� ����� �ִ�, �ּ� ���θ� ����
	}
}

void postorder(Tree* node)						// �ǿ����� ��帶�� ����� �ִ�, �ּ� ���ο� ���� ���� ��ȯ + ���
{
	if (node) {
		postorder(node->left);
		postorder(node->right);
		if (!node->op) {						// ���� ��尡 �ǿ����� ����� ���
			if (node->is_Max)
				node->value = num[to--];		// �ִ��� ����Ǿ�� �� �� ū ������ �������� ����
			else
				node->value = num[from++];		// �ּڰ��� ����Ǿ�� �� �� ���� ������ �������� ����
		}
		else {									// ������ ����� ���
			if (node->op == '+')
				node->value = node->left->value + node->right->value;
			else
				node->value = node->left->value - node->right->value;
		}
	}
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> value;
		tree[i] = { nullptr, nullptr, value, 0, false };				// �ǿ����� ���� �����̹Ƿ� ����, ������ ��� null�� ��
		num[i - 1] = value;
	}
	sort(num, num + N);													// �ǿ����� ������ ������ �������� ������������ ����
	for (int i = N + 1; i < 2 * N; i++) {
		cin >> op >> Left >> Right;
		tree[i] = { tree + Left, tree + Right, 0, op, false };		// Ʈ�� ����
	}
	preorder(tree + 2 * N - 1, true);

	to = N - 1;
	postorder(tree + 2 * N - 1);
	cout << tree[2 * N - 1].value;
	return 0;
}