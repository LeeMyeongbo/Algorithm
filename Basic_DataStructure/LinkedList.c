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
// phead : 리스트의 헤드 포인터의 포인터
// p:선행 노드
// new_node : 삽입될 노드
void insert_node(ListNode** phead, ListNode* p, ListNode* new_node)
{
	if (*phead == NULL) // 공백 리스트인 경우
	{
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (p == NULL) // p가 null이면 첫 번째 노드로 삽입
	{
		new_node->link = *phead;
		*phead = new_node;
	}
	else // p 다음에 삽입
	{
		new_node->link = p->link;
		p->link = new_node;
	}
}

// phead : 헤드 포인터에 대한 포인터
// p : 삭제될 노드의 선행 노드
// removed : 삭제될 노드
void remove_node(ListNode** phead, ListNode* p)
{
	if (p == NULL) // 맨 처음 노드를 삭제할 경우
		*phead = (*phead)->link;
	else
		p->link = (p->link)->link;
}

// 방문연산 : 리스트 상의 노드를 순차적으로 방문 (반복과 순환이 있음)
// 반복 버전
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

// 순환 버전
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

// 탐색 연산 : 특정 데이터값을 갖는 노드를 찾는 연산
ListNode* search(ListNode* head, int x)
{
	ListNode* p;
	p = head;
	while (p != NULL)
	{
		if (p->data == x) return p; // 탐색 성공
		p = p->link;
	}
	return p; // 탐색 실패일 경우 NULL 반환
}

// 합병 연산 : 2개의 리스트를 합하는 연산
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

// 역순연산 : 리스트의 노드들을 역순으로 만드는 연산
ListNode* reverse(ListNode* head)
{
	// 순회 포인터로 p,q,r 사용
	ListNode *p, *q, *r;
	p = head; // p는 역순으로 만들 리스트
	q = NULL; // q는 역순으로 만들 노드
	while (p != NULL)
	{
		r = q; // r은 역순으로 된 리스트. r은 q, q는 p를 차례로 따라간다.
		q = p;
		p = p->link;
		q->link = r;
	}
	return q; // q는 역순으로 된 리스트의 헤드 포인터
}

// 특정 데이터값의 노드 갯수
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

// 홀수 번째 노드 삭제
void deleteOddNode(ListNode** phead)
{
	int cnt = 1;
	ListNode* p = *phead, * remain = NULL, * remove = NULL;
	while (p!=NULL)
	{
		if (cnt == 1) // 첫 번째일 때
		{
			remove = p;
			p = p->link;
			*phead = p;
			free(remove);
		}
		else if (cnt % 2 == 0) // 짝수 번째일 때
		{
			remain = p;
			p = p->link;
		}
		else // 첫 번째를 제외한 홀수 번째일 때
		{
			remove = p;
			remain->link = remove->link;
			p = p->link;
			free(remove);
		}
		cnt++;
	}
}

// 모든 데이터값의 합
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
	printf("값이 10인 노드 갯수 : %d\n", check(head, 10));
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