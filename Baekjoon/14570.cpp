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
	if (node->left && node->right) {				// 양쪽 자식이 모두 존재할 경우
		if (cur % 2)
			return dfs(node->left, cur / 2 + 1);	// 현재 수가 홀수일 경우 2로 나눈 것의 +1을 하고 왼쪽으로 이동
		else
			return dfs(node->right, cur / 2);		// 짝수라면 2로 나누고 오른쪽 이동
	}
	else if (node->left)
		return dfs(node->left, cur);		// 왼쪽 자식밖에 없다면 그대로 왼쪽으로 이동
	else if (node->right)
		return dfs(node->right, cur);		// 오른쪽 밖에 없다면 그대로 오른쪽으로 이동
	else
		return node->cur;					// 리프에 다다르면 현재 리프의 index 반환
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> U >> V;
		if (U != -1)
			tree[i].left = tree + U;	// 왼쪽 자식이 존재한다면 저장
		if (V != -1)
			tree[i].right = tree + V;	// 오른쪽 자식이 존재한다면 저장
		tree[i].cur = i;
	}
	cin >> K;

	cout << dfs(tree + 1, K);
	return 0;
}