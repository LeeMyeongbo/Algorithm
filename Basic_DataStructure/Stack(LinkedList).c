#include <stdio.h>
#include <stdlib.h>

typedef int element; // 요소의 타입

typedef struct StackNode
{
	element item;
	struct StackNode* link; // 노드의 타입
}StackNode;

typedef struct 
{
	StackNode* top; // 연결의 스택의 관련 데이터
}LinkedStackType;

void init(LinkedStackType* s)
{
	s->top = NULL;
}

// 공백 상태 검출 함수
int is_empty(LinkedStackType* s)
{
	return (s->top == NULL);
}

void push(LinkedStackType* s, element item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	if (temp == NULL)
	{
		fprint(stderr, "메모리 할당에러\n");
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
		fprintf(stderr, "스택이 비어있음\n");
		exit(1);
	}
	else
	{
		StackNode* temp = s->top; // 삭제할 노드 포인터변수로 생성
		int item = temp->item; // temp의 요소값을 item 변수에 대입
		s->top = s->top->link; // top의 위치 변경
		free(temp); // temp 제거
		return item; // 요소값 반환
	}
}