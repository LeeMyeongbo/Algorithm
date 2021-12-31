#include <stdio.h>

typedef int element;	// ����� Ÿ��

typedef struct DlistNode	// ����� Ÿ��(���ʿ����� ����, ������ ���� ���� ���� ����Ʈ �̿�)
{
	element data;
	struct DlistNode* llink;
	struct DlistNode* rlink;
}DlistNode;

typedef struct DequeType// ���� Ÿ��
{
	DlistNode* head;
	DlistNode* tail;
}DequeType;

// dq : ���� �߰��Ǵ� ���
// �ڿ��� ����
void add_rear(DequeType* dq, element item)
{
	DlistNode* new_node = create_node(dq->tail, item, NULL);
	if (is_empty(dq))
		dq->head = new_node;
	else
		dq->tail->rlink = new_node;
	dq->tail = new_node;
}

// �տ��� ����
void add_front(DequeType* dq, element item)
{
	DlistNode* new_node = create_node(NULL, item, dq->head);
	if (is_empty(dq))
		dq->tail = new_node;
	else
		dq->head->llink = new_node;
	dq->head = new_node;
}

// �տ��� ����
element delete_front(DequeType* dq)
{
	element item;
	DlistNode* removed_node;
	if (is_empty(dq)) error("���� ������ ����");
	else
	{
		removed_node = dq->head; // ������ ���
		item = removed_node->data; // ������ ����
		dq->head = dq->head->rlink; // ��������� ����
		free(removed_node); // �޸� ���� �ݳ�
		if (dq->head == NULL) // ��������̸�
			dq->tail = NULL;
		else                  // ������°� �ƴϸ�
			dq->head->llink = NULL;
	}
	return item;
}

