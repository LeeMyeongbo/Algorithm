#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE	500
typedef char element; // �迭 ��Ҵ� element Ÿ������ ����
typedef struct
{
	element stack[MAX_STACK_SIZE];
	int top;
}StackType; // ���� �����͸� ����ü�� ��� �Լ��� �Ķ���ͷ� ����

// ���� �ʱ�ȭ �Լ�
void init(StackType* s)
{
	s->top = -1;
}

// ���� ���� ���� �Լ�
int is_empty(StackType* s)
{
	return (s->top == -1);
}

// ��ȭ ���� ���� �Լ�
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

// �����Լ�
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else
		s->stack[++(s->top)] = item;
}

// �����Լ�
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else
		return s->stack[(s->top)--];
}

// ��ũ�Լ�
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else
		return s->stack[s->top];
}

void main()
{
	char a[100];
	int i;
	StackType* s = (StackType*)malloc(sizeof(StackType));
	init(s);
	int small = 0, medium = 0, big = 0;
	printf("����(��ȣ �����ؼ�) �Է� : ");
	scanf_s("%s", a, 100);
	for (i = 0; i < 100; i++)
	{
		if (a[i] == '(')
		{
			push(s, a[i]);
			small++;
		}
		if (a[i] == '{')
		{
			push(s, a[i]);
			medium++;
		}
		if(a[i] == '[')
		{
			push(s, a[i]);
			big++;
		}
		if (a[i] == ')')
		{
			if (peek(s) == '(')
				pop(s);
			small--;
		}
		if (a[i] == '}')
		{
			if (peek(s) == '{')
				pop(s);
			medium--;
		}
		if (a[i] == ']')
		{
			if (peek(s) == '[')
				pop(s);
			big--;
		}
	}
	if (is_empty(s) && small == 0 && medium == 0 && big == 0) printf("0\n");
	else printf("1\n");
}