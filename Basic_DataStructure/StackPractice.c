#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_STACK_SIZE	500
typedef char element; // �迭 ��Ҵ� element Ÿ������ ����
typedef struct
{
	element px[MAX_STACK_SIZE];
	element py[MAX_STACK_SIZE];
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
void push(StackType* s, element item1, element item2)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else
	{
		s->px[++(s->top)] = item1;
		s->py[s->top] = item2;
	}
}

// �����Լ�
void pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else
		(s->top)--;
}

// ��ũ�Լ�
void peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
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
		miro[i][j] = 2; // ���� ��ġ�� 2�� ó��
		for (int a = 0; a < 10; a++)
		{
			for (int b = 0; b < 10; b++)
				printf("%d ", miro[a][b]);
			printf("\n");
		}
		if (i == 8 && j == 9) break;
		if (miro[i + 1][j] == 0) // ���� ���� ��ġ���� �Ʒ����� 0�̶��
			push(pos, ++i, j);
		else if (miro[i][j + 1] == 0) // ���� ���� ��ġ���� �������� 0�̶��
			push(pos, i, ++j);
		else if (miro[i - 1][j] == 0) // ���� ���� ��ġ���� ������ 0�̶��
			push(pos, --i, j);
		else if (miro[i][j - 1] == 0) // ���� ���� ��ġ���� ������ 0�̶��
			push(pos, i, --j);
		else // ������ 0�� ���� ���
		{
			while (1)
			{
				system("cls");
				miro[pos->px[pos->top]][pos->py[pos->top]] = 3; // ���� ��ġ�� ���� 3���� ó��
				for (int a = 0; a < 10; a++)
				{
					for (int b = 0; b < 10; b++)
						printf("%d ", miro[a][b]);
					printf("\n");
				}
				if (miro[pos->px[pos->top] + 1][pos->py[pos->top]] == 0 ||
					miro[pos->px[pos->top]][pos->py[pos->top] + 1] == 0 ||
					miro[pos->px[pos->top] - 1][pos->py[pos->top]] == 0 ||
					miro[pos->px[pos->top]][pos->py[pos->top] - 1] == 0) // ���� ��ġ���� ��, �Ʒ�, ������, ���� �� 0�� �ִٸ�
				{
					i = pos->px[pos->top]; 
					j = pos->py[pos->top]; 
					break;
				}
				pop(pos); // �ٷ� �� ��ġ�� �ǵ���
				if (is_empty(pos))
				{
					printf("��ΰ� �����ϴ�.\n");
					return;
				}
				Sleep(500);
			}
		}
		Sleep(500);
	}
	printf("�� ã�� �Ϸ�\n");
}