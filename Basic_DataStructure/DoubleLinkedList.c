#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DlistNode
{
	element data;
	struct DlistNode *llink;
	struct DlistNode *rlink;
}DlistNode;

// 노드 new_node를 노드 before의 오른쪽에 삽입
void dinsert_node(DlistNode* before, DlistNode* new_node)
{
	new_node->llink = before; // 1
	new_node->rlink = before->rlink; // 2
	before->rlink->llink = new_node; // 3
	before->rlink = new_node; // 4
}

// 노드 removed를 삭제한다.
void dremoved_node(DlistNode* phead_node, DlistNode* removed)
{
	if (removed == phead_node) return;
	removed->llink->rlink = removed->rlink; // 1
	removed->rlink->llink = removed->llink; // 2
	free(removed);
}