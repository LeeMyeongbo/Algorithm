#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH	30

typedef struct TreeNode // 트리의 노드타입
{
	char word[MAX_LENGTH];
	char mean[MAX_LENGTH];
	struct TreeNode* left, *right;
} TreeNode;

void init(TreeNode** root)
{
	*root = NULL;
}

// 입력
void insert_node(TreeNode** root, char word[], char mean[])
{
	TreeNode* t, *p;
	TreeNode* n;
	t = *root;
	p = NULL;

	while (t != NULL)
	{
		if (!strcmp(t->word, word)) return;
		p = t;
		if (strcmp(t->word, word) > 0)
			t = t->left;
		else
			t = t->right;
	}
	n = (TreeNode*)malloc(sizeof(TreeNode));
	if (n == NULL) return;

	strcpy(n->word, word);
	strcpy(n->mean, mean);
	n->left = n->right = NULL;

	if (p != NULL)
	{
		if (strcmp(p->word, word) > 0)
			p->left = n;
		else
			p->right = n;
	}
}

// 출력
void show_inorder(TreeNode* root)
{
	if (root != NULL)
	{
		inorder(root->left);			// 왼쪽서브트리 순회
		printf("단어 : %s\n의미 : %s\n", root->word, root->mean);    // 노드 방문
		inorder(root->right);			// 오른쪽서브트리 순회
	}
}

// 탐색
TreeNode* search(TreeNode* root, char word[])
{
	TreeNode* t = root;
	while (t != NULL)
	{
		if (!strcmp(t->word, word))
			return t;
		if (strcmp(t->word, word) > 0)
			t = t->left;
		else
			t = t->right;
	}
	printf("찾고자 하는 단어가 없습니다.\n");
	return NULL;
}

// 삭제
void delete_node(TreeNode** root, char word[])
{
	TreeNode* p, *child, *succ, *succ_p, *temp;
	TreeNode* t = *root; // t는 삭제하고자 하는 노드
	TreeNode* p = NULL; // p는 t의 부모노드
	while (t != NULL && strcmp(t->word, word) != 0)
	{
		p = t;
		t = strcmp(t->word, word) > 0 ? t->left : t->right;
	}
	if (t == NULL)
	{
		printf("삭제하고자 하는 단어가 없습니다.\n");
		return;
	}
	if (t->left == NULL && t->right == NULL) // 삭제하려는 노드가 단말 노드일 경우
	{
		temp = t;
		if (p->right == t)
			p->right = NULL;
		else
			p->left = NULL;
		free(temp);
	}
	else if (t->left == NULL || t->right == NULL) // 삭제하려는 노드가 하나의 자식 노드만 가질 경우
	{
		temp = t;
		child = t->left != NULL ? t->left : t->right;
		if (p->right == t)
			p->right = child;
		else
			p->left = child;
		free(temp);
	}
	else // 삭제하려는 노드가 두 자식 노드를 가질 경우
	{
		succ_p = t;
		succ = t->left;
		while (succ->right != NULL)
		{
			succ_p = succ;
			succ = succ->right;
		}
		if (succ_p->right == succ)
			succ_p->right = succ->right;
		else

	}
}
void main()
{

}