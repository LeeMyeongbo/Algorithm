#include <stdio.h>

typedef int element;	// 요소의 타입

typedef struct DlistNode	// 노드의 타입(양쪽에서의 삽입, 삭제를 위해 이중 연결 리스트 이용)
{
	element data;
	struct DlistNode* llink;
	struct DlistNode* rlink;
}DlistNode;

typedef struct DequeType// 덱의 타입
{
	DlistNode* head;
	DlistNode* tail;
}DequeType;

// dq : 새로 추가되는 노드
// 뒤에서 삽입
void add_rear(DequeType* dq, element item)
{
	DlistNode* new_node = create_node(dq->tail, item, NULL);
	if (is_empty(dq))
		dq->head = new_node;
	else
		dq->tail->rlink = new_node;
	dq->tail = new_node;
}

// 앞에서 삽입
void add_front(DequeType* dq, element item)
{
	DlistNode* new_node = create_node(NULL, item, dq->head);
	if (is_empty(dq))
		dq->tail = new_node;
	else
		dq->head->llink = new_node;
	dq->head = new_node;
}

// 앞에서 삭제
element delete_front(DequeType* dq)
{
	element item;
	DlistNode* removed_node;
	if (is_empty(dq)) error("공백 덱에서 삭제");
	else
	{
		removed_node = dq->head; // 삭제할 노드
		item = removed_node->data; // 데이터 추출
		dq->head = dq->head->rlink; // 헤드포인터 변경
		free(removed_node); // 메모리 공간 반납
		if (dq->head == NULL) // 공백상태이면
			dq->tail = NULL;
		else                  // 공백상태가 아니면
			dq->head->llink = NULL;
	}
	return item;
}

