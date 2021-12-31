#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode
{
	element data;
	struct ListNode* link;
}ListNode;

// phead : 리스트의 헤드 포인터의 포인터
// p : 선행 노드
// node : 삽입될 노드
// 처음 부분에 삽입
void insert_first(ListNode** phead, ListNode* node)
{
	if (*phead == NULL)
	{
		*phead = node;
		node->link = node;
	}
	else
	{
		node->link = (*phead)->link;
		(*phead)->link = node;
	}
}

// 끝 부분에 삽입
void insert_last(ListNode** phead, ListNode* node)
{
	if (*phead == NULL)
	{
		*phead = node;
		node->link = node;
	}
	else
	{
		node->link = (*phead)->link;
		(*phead)->link = node;
		*phead = node;
	}
}