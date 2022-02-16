#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_STACK_SIZE	500
typedef char element; // 배열 요소는 element 타입으로 선언
typedef struct
{
	element px[MAX_STACK_SIZE];
	element py[MAX_STACK_SIZE];
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
void push(StackType* s, element item1, element item2)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else
	{
		s->px[++(s->top)] = item1;
		s->py[s->top] = item2;
	}
}

// 삭제함수
void pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		(s->top)--;
}

// 피크함수
void peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		printf("%d %d\n", s->px[s->top], s->py[s->top]);
}

void main()
{
	int i = 1, j = 0;
	StackType* pos = (StackType*)malloc(sizeof(StackType));
	init(pos);
	char miro[10][10] = {
		1,1,1,1,1,1,1,1,1,1,
		0,0,0,0,1,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,1,1,1,0,0,1,0,1,
		1,0,1,0,1,0,0,1,0,1,
		1,0,1,0,1,0,0,1,0,1,
		1,0,1,0,1,0,0,1,0,1,
		1,0,1,0,1,1,0,1,0,1,
		1,0,1,0,0,0,0,1,0,0,
		1,1,1,1,1,1,1,1,1,1 };
	push(pos, i, j);
	while (i<=8 && j<=9)
	{
		system("cls");
		miro[i][j] = 2; // 현재 위치를 2로 처리
		for (int a = 0; a < 10; a++)
		{
			for (int b = 0; b < 10; b++)
				printf("%d ", miro[a][b]);
			printf("\n");
		}
		if (i == 8 && j == 9) break;
		if (miro[i + 1][j] == 0) // 만약 현재 위치에서 아래쪽이 0이라면
			push(pos, ++i, j);
		else if (miro[i][j + 1] == 0) // 만약 현재 위치에서 오른쪽이 0이라면
			push(pos, i, ++j);
		else if (miro[i - 1][j] == 0) // 만약 현재 위치에서 위쪽이 0이라면
			push(pos, --i, j);
		else if (miro[i][j - 1] == 0) // 만약 현재 위치에서 왼쪽이 0이라면
			push(pos, i, --j);
		else // 주위에 0이 없을 경우
		{
			while (1)
			{
				system("cls");
				miro[pos->px[pos->top]][pos->py[pos->top]] = 3; // 현재 위치한 곳을 3으로 처리
				for (int a = 0; a < 10; a++)
				{
					for (int b = 0; b < 10; b++)
						printf("%d ", miro[a][b]);
					printf("\n");
				}
				if (miro[pos->px[pos->top] + 1][pos->py[pos->top]] == 0 ||
					miro[pos->px[pos->top]][pos->py[pos->top] + 1] == 0 ||
					miro[pos->px[pos->top] - 1][pos->py[pos->top]] == 0 ||
					miro[pos->px[pos->top]][pos->py[pos->top] - 1] == 0) // 현재 위치에서 위, 아래, 오른쪽, 왼쪽 중 0이 있다면
				{
					i = pos->px[pos->top]; 
					j = pos->py[pos->top]; 
					break;
				}
				pop(pos); // 바로 전 위치로 되돌림
				if (is_empty(pos))
				{
					printf("경로가 없습니다.\n");
					return;
				}
				Sleep(500);
			}
		}
		Sleep(500);
	}
	printf("길 찾기 완료\n");
}