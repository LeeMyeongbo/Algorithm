#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DlistNode
{
	element data;
	struct DlistNode *llink;
	struct DlistNode *rlink;
}DlistNode;

// ��� new_node�� ��� before�� �����ʿ� ����
void dinsert_node(DlistNode* before, DlistNode* new_node)
{
	new_node->llink = before; // 1
	new_node->rlink = before->rlink; // 2
	before->rlink->llink = new_node; // 3
	before->rlink = new_node; // 4
}

// ��� removed�� �����Ѵ�.
void dremoved_node(DlistNode* phead_node, DlistNode* removed)
{
	if (removed == phead_node) return;
	removed->llink->rlink = removed->rlink; // 1
	removed->rlink->llink = removed->llink; // 2
	free(removed);
}