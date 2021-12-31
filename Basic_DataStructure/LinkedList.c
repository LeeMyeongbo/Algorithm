#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode 
{
	element data;
	struct ListNode* link;
}ListNode;

void add_node(ListNode** phead, ListNode** ptail, ListNode* new_node)
{
	new_node->link = NULL;
	if (*phead == NULL)
		*phead = new_node;
	else
		(*ptail)->link = new_node;
	*ptail = new_node;
}
// phead : ����Ʈ�� ��� �������� ������
// p:���� ���
// new_node : ���Ե� ���
void insert_node(ListNode** phead, ListNode* p, ListNode* new_node)
{
	if (*phead == NULL) // ���� ����Ʈ�� ���
	{
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (p == NULL) // p�� null�̸� ù ��° ���� ����
	{
		new_node->link = *phead;
		*phead = new_node;
	}
	else // p ������ ����
	{
		new_node->link = p->link;
		p->link = new_node;
	}
}

// phead : ��� �����Ϳ� ���� ������
// p : ������ ����� ���� ���
// removed : ������ ���
void remove_node(ListNode** phead, ListNode* p)
{
	if (p == NULL) // �� ó�� ��带 ������ ���
		*phead = (*phead)->link;
	else
		p->link = (p->link)->link;
}

// �湮���� : ����Ʈ ���� ��带 ���������� �湮 (�ݺ��� ��ȯ�� ����)
// �ݺ� ����
void display(ListNode* head)
{
	ListNode* p = head;
	while (p != NULL)
	{
		printf("%d->", p->data);
		p = p->link;
	}
	printf("NULL\n");
}

// ��ȯ ����
void display_recur(ListNode* head)
{
	ListNode* p = head;
	if (p != NULL)
	{
		printf("%d->", p->data);
		display_recur(p->link);
	}
	printf("NULL\n");
}

// Ž�� ���� : Ư�� �����Ͱ��� ���� ��带 ã�� ����
ListNode* search(ListNode* head, int x)
{
	ListNode* p;
	p = head;
	while (p != NULL)
	{
		if (p->data == x) return p; // Ž�� ����
		p = p->link;
	}
	return p; // Ž�� ������ ��� NULL ��ȯ
}

// �պ� ���� : 2���� ����Ʈ�� ���ϴ� ����
ListNode* concat(ListNode* head1, ListNode* head2)
{
	ListNode* p;
	if (head1 == NULL) return head2;
	else if (head2 == NULL) return head1;
	else
	{
		p = head1;
		while (p->link != NULL)
			p = p->link;
		p->link = head2;
		return head1;
	}
}

// �������� : ����Ʈ�� ������ �������� ����� ����
ListNode* reverse(ListNode* head)
{
	// ��ȸ �����ͷ� p,q,r ���
	ListNode *p, *q, *r;
	p = head; // p�� �������� ���� ����Ʈ
	q = NULL; // q�� �������� ���� ���
	while (p != NULL)
	{
		r = q; // r�� �������� �� ����Ʈ. r�� q, q�� p�� ���ʷ� ���󰣴�.
		q = p;
		p = p->link;
		q->link = r;
	}
	return q; // q�� �������� �� ����Ʈ�� ��� ������
}

// Ư�� �����Ͱ��� ��� ����
int check(ListNode* head, int x)
{
	ListNode* p = head;
	int cnt = 0;
	while (p != NULL)
	{
		if (p->data == x)
			cnt++;
		p = p->link;
	}
	return cnt;
}

// Ȧ�� ��° ��� ����
void deleteOddNode(ListNode** phead)
{
	int cnt = 1;
	ListNode* p = *phead, * remain = NULL, * remove = NULL;
	while (p!=NULL)
	{
		if (cnt == 1) // ù ��°�� ��
		{
			remove = p;
			p = p->link;
			*phead = p;
			free(remove);
		}
		else if (cnt % 2 == 0) // ¦�� ��°�� ��
		{
			remain = p;
			p = p->link;
		}
		else // ù ��°�� ������ Ȧ�� ��°�� ��
		{
			remove = p;
			remain->link = remove->link;
			p = p->link;
			free(remove);
		}
		cnt++;
	}
}

// ��� �����Ͱ��� ��
int sum(ListNode* head)
{
	ListNode* p = head;
	int sum = 0;
	while (p != NULL)
	{
		sum += p->data;
		p = p->link;
	}
	return sum;
}
void main()
{
	ListNode* head = NULL;
	ListNode* cur = NULL;
	ListNode* tail = NULL;

	for (int i = 0; i < 10; i++)
	{
		ListNode* p = (ListNode*)malloc(sizeof(ListNode));
		p->data = i * 10;

		add_node(&head, &tail, p);
		if (i == 5) cur = p;
	}
	printf("���� 10�� ��� ���� : %d\n", check(head, 10));
	display(head);

	ListNode* p1 = (ListNode*)malloc(sizeof(ListNode));
	p1->data = 89;
	insert_node(&head, cur, p1);
	display(head);

	remove_node(&head, cur);
	display(head);
	
	deleteOddNode(&head);
	display(head);
}