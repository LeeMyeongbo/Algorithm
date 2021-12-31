#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode
{
	element data;
	struct ListNode* link;
}ListNode;

// phead : ����Ʈ�� ��� �������� ������
// p : ���� ���
// node : ���Ե� ���
// ó�� �κп� ����
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

// �� �κп� ����
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