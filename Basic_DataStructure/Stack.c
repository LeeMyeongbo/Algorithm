#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE	500
typedef char element; // 배열 요소는 element 타입으로 선언
typedef struct
{
	element stack[MAX_STACK_SIZE];
	int top;
}StackType; // 관련 데이터를 구조체로 묶어서 함수의 파라미터로 전달

// 스택 초기화 함수
void init(StackType* s)
{
	s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType* s)
{
	return (s->top == -1);
}

// 포화 상태 검출 함수
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

// 삽입함수
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else
		s->stack[++(s->top)] = item;
}

// 삭제함수
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		return s->stack[(s->top)--];
}

// 피크함수
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
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
	printf("문장(괄호 포함해서) 입력 : ");
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