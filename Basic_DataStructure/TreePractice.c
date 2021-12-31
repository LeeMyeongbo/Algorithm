#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH	30

typedef struct TreeNode // Ʈ���� ���Ÿ��
{
	char word[MAX_LENGTH];
	char mean[MAX_LENGTH];
	struct TreeNode* left, *right;
} TreeNode;

void init(TreeNode** root)
{
	*root = NULL;
}

// �Է�
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

// ���
void show_inorder(TreeNode* root)
{
	if (root != NULL)
	{
		inorder(root->left);			// ���ʼ���Ʈ�� ��ȸ
		printf("�ܾ� : %s\n�ǹ� : %s\n", root->word, root->mean);    // ��� �湮
		inorder(root->right);			// �����ʼ���Ʈ�� ��ȸ
	}
}

// Ž��
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
	printf("ã���� �ϴ� �ܾ �����ϴ�.\n");
	return NULL;
}

// ����
void delete_node(TreeNode** root, char word[])
{
	TreeNode* p, *child, *succ, *succ_p, *temp;
	TreeNode* t = *root; // t�� �����ϰ��� �ϴ� ���
	TreeNode* p = NULL; // p�� t�� �θ���
	while (t != NULL && strcmp(t->word, word) != 0)
	{
		p = t;
		t = strcmp(t->word, word) > 0 ? t->left : t->right;
	}
	if (t == NULL)
	{
		printf("�����ϰ��� �ϴ� �ܾ �����ϴ�.\n");
		return;
	}
	if (t->left == NULL && t->right == NULL) // �����Ϸ��� ��尡 �ܸ� ����� ���
	{
		temp = t;
		if (p->right == t)
			p->right = NULL;
		else
			p->left = NULL;
		free(temp);
	}
	else if (t->left == NULL || t->right == NULL) // �����Ϸ��� ��尡 �ϳ��� �ڽ� ��常 ���� ���
	{
		temp = t;
		child = t->left != NULL ? t->left : t->right;
		if (p->right == t)
			p->right = child;
		else
			p->left = child;
		free(temp);
	}
	else // �����Ϸ��� ��尡 �� �ڽ� ��带 ���� ���
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