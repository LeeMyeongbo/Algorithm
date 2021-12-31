#include <stdio.h>
#include <stdlib.h>

typedef int element; // ����� Ÿ��

typedef struct StackNode
{
	element item;
	struct StackNode* link; // ����� Ÿ��
}StackNode;

typedef struct 
{
	StackNode* top; // ������ ������ ���� ������
}LinkedStackType;

void init(LinkedStackType* s)
{
	s->top = NULL;
}

// ���� ���� ���� �Լ�
int is_empty(LinkedStackType* s)
{
	return (s->top == NULL);
}

void push(LinkedStackType* s, element item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	if (temp == NULL)
	{
		fprint(stderr, "�޸� �Ҵ翡��\n");
		return;
	}
	else
	{
		temp->item = item;
		temp->link = s->top; // 1
		s->top = temp; // 2
	}
}

element pop(LinkedStackType* s)
{
	if (is_empty(s))
	{
		fprintf(stderr, "������ �������\n");
		exit(1);
	}
	else
	{
		StackNode* temp = s->top; // ������ ��� �����ͺ����� ����
		int item = temp->item; // temp�� ��Ұ��� item ������ ����
		s->top = s->top->link; // top�� ��ġ ����
		free(temp); // temp ����
		return item; // ��Ұ� ��ȯ
	}
}