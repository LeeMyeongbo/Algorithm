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

void preorder(Tree* node, bool is_Max)			// is_Max : 현재 노드의 최대, 최소 여부 (최댓값이 나와야 할 땐 true, 최소여야 할 땐 false)
{
	if (node) {
		node->is_Max = is_Max;
		preorder(node->left, is_Max);			// 왼쪽 자식 노드는 무조건 부모 노드의 최대, 최소 여부와 같아야 함
		if (node->op == '-')					// 현재 연산자 노드의 연산자가 '-'일 경우
			preorder(node->right, !is_Max);		// 오른쪽 자식 노드로 갈 때는 부모 노드의 최대, 최소 여부와 반대가 되어야 함
		else
			preorder(node->right, is_Max);		// 연산자가 '+'이면 오른쪽 자식도 부모 노드의 최대, 최소 여부를 따라감
	}
}

void postorder(Tree* node)						// 피연산자 노드마다 저장된 최대, 최소 여부에 따라 정수 변환 + 계산
{
	if (node) {
		postorder(node->left);
		postorder(node->right);
		if (!node->op) {						// 현재 노드가 피연산자 노드일 경우
			if (node->is_Max)
				node->value = num[to--];		// 최댓값이 저장되어야 할 땐 큰 값부터 차례차례 지정
			else
				node->value = num[from++];		// 최솟값이 저장되어야 할 땐 작은 값부터 차례차례 지정
		}
		else {									// 연산자 노드라면 계산
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
		tree[i] = { nullptr, nullptr, value, 0, false };				// 피연산자 노드는 리프이므로 왼쪽, 오른쪽 모드 null로 둠
		num[i - 1] = value;
	}
	sort(num, num + N);													// 피연산자 노드들이 가지는 정수들을 오름차순으로 정렬
	for (int i = N + 1; i < 2 * N; i++) {
		cin >> op >> Left >> Right;
		tree[i] = { tree + Left, tree + Right, 0, op, false };		// 트리 형성
	}
	preorder(tree + 2 * N - 1, true);

	to = N - 1;
	postorder(tree + 2 * N - 1);
	cout << tree[2 * N - 1].value;
	return 0;
}