#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode // 트리의 노드타입
{
	int data;
	struct TreeNode* left, * right;
} TreeNode;

typedef struct QueueNode  // 큐의 노드의 타입 
{
	TreeNode* item;
	struct QueueNode* link;
} QueueNode;

typedef struct Position // 큐 노드의 맨 앞(front), 맨 뒤(rear)를 가리킴
{
	QueueNode* front, * rear;
} QueueType;

// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 큐 초기화 함수
void init_q(QueueType* q)
{
	q->front = q->rear = NULL;
}

// 큐 공백 상태 검출 함수
int is_empty(QueueType* q)
{
	return (q->front == NULL);
}

// 큐 삽입 함수
void enqueue(QueueType* q, TreeNode* item)
{
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	if (temp == NULL)
		error("메모리를 할당할 수 없습니다");
	else 
	{
		temp->item = item; 			// 데이터 저장
		temp->link = NULL; 			// 링크 필드를 NULL
		if (is_empty(q))			// 큐가 공백이면
		{ 		
			q->front = temp;
			q->rear = temp;
		}
		else						// 큐가 공백이 아니면
		{ 		
			q->rear->link = temp;   // 순서가 중요
			q->rear = temp;
		}
	}
}

// 큐 삭제 함수
TreeNode* dequeue(QueueType* q)
{
	QueueNode* temp = q->front;
	TreeNode* item;
	if (is_empty(q))				// 공백상태
		error("큐가 비어 있읍니다");
	else 
	{
		item = temp->item; 			// 데이터를 꺼낸다.
		q->front = q->front->link;  // front를 다음노드를 가리키도록 한다.
		if (q->front == NULL) 		// 공백 상태
			q->rear = NULL;
		free(temp); 				// 동적메모리 해제
		return item; 				// 데이터 반환
	}
}

//// 트리 노드를 가리키는 포인터의 초기화
//void init(TreeNode** p)
//{
//	*p = (TreeNode*)malloc(sizeof(TreeNode));
//	(*p)->left = NULL;
//	(*p)->right = NULL;
//}
//
//// 계층화 (p : 부모 노드, c : 자식 노드)
//void insert(TreeNode* p, TreeNode* c)
//{
//	if (p->left == NULL)
//		p->left = c;
//	else if (p->right == NULL)
//		p->right = c;
//	else
//		printf("계층화할 수 없습니다.\n");
//}
//
//// 해당 노드 초기화 및 데이터 추가
//void addData(TreeNode** node, int data)
//{
//	init(node);
//	(*node)->data = data;
//}

// 중위 순회
void inorder(TreeNode* root) 
{
	if (root != NULL) 
	{
		inorder(root->left);			// 왼쪽서브트리 순회
		printf("[%d] ", root->data);    // 노드 방문
		inorder(root->right);			// 오른쪽서브트리 순회
	}
}

// 전위 순회
void preorder(TreeNode* root) 
{
	if (root != NULL) 
	{
		printf("[%d] ", root->data);	// 노드 방문
		preorder(root->left);			// 왼쪽서브트리 순회
		preorder(root->right);			// 오른쪽서브트리 순회
	}
}

// 후위 순회
void postorder(TreeNode* root) 
{
	if (root != NULL) 
	{
		postorder(root->left);			// 왼쪽서브트리 순회
		postorder(root->right);			// 오른쪽서브트리순회
		printf("[%d] ", root->data);    // 노드 방문
	}
}

// 레벨 순회
void levelorder(TreeNode* root)
{
	QueueType* q = (QueueType*)malloc(sizeof(QueueType));
	init_q(q); 
	enqueue(q, root); // 맨 처음 큐에 root노드 넣음
	TreeNode* temp = root;
	while (!is_empty(q))
	{
		temp = dequeue(q); // 큐에서 맨 앞에 있는 노드를 삭제하고 삭제된 노드를 temp에 저장
		if (temp->left != NULL)
			enqueue(q, temp->left); // 삭제된 노드의 left가 null이 아니면 큐에 저장
		if (temp->right != NULL)
			enqueue(q, temp->right); // 삭제된 노드의 right가 null이 아니면 큐에 저장
		printf("[%d] ", temp->data); // 삭제된 노드의 data 출력
	}
	free(q);
}

// 노드 개수
int get_node_count(TreeNode* node)
{
	int count = 0;
	if (node != NULL)
		count = 1 + get_node_count(node->left) + get_node_count(node->right);
	return count;
}

// 단말 노드 개수 
int get_leaf_count(TreeNode* node)
{
	int count = 0;
	if (node != NULL)
	{
		if (node->left == NULL && node->right == NULL)
			return 1;
		else
			count = get_leaf_count(node->left) + get_leaf_count(node->right);
	}
	return count;
}

// 높이 구하기
int get_height(TreeNode* node)
{
	int height = 0;
	if (node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right));
	return height;
}

// 순환적인 탐색 함수
TreeNode* search1(TreeNode* node, int key)
{
	if (node == NULL) return NULL;
	if (key == node->data) return node; // 1
	else if (key < node->data)
		return search1(node->left, key); // 2
	else
		return search1(node->right, key); // 3
}

// 반복적인 탐색 함수
TreeNode* search2(TreeNode* node, int key)
{
	while (node != NULL)
	{
		if (key == node->data) return node;
		else if (key < node->data)
			node = node->left;
		else
			node = node->right;
	}
	return NULL; // 탐색에 실패했을 경우 NULL 반환
}

// key를 이진 탐색 트리 root에 삽입
// key가 이미 root안에 있으면 삽입되지 않음
void add(TreeNode** root, int key)
{
	TreeNode* p, *t; // p는 부모노드, t는 현재노드
	TreeNode* n; // n은 현재노드
	t = *root;
	p = NULL;

	// 탐색 먼저 수행
	while (t != NULL)
	{
		if (key == t->data) return;
		p = t;
		if (key < t->data)
			t = t->left;
		else
			t = t->right;
	}
	// key가 트리 안에 없으므로 삽입
	n = (TreeNode*)malloc(sizeof(TreeNode));
	if (n == NULL) return;

	// 데이터 복사
	n->data = key;
	n->left = n->right = NULL;

	// 부모 노드와 링크 연결
	if (p != NULL)
	{
		if (key < p->data)
			p->left = n;
		else
			p->right = n;
	}
	else
		*root = n;
}

/*// 순환 방식
TreeNode* insert_node(TreeNode* node, int key)
{
	// 트리가 공백이면 새로운 노드 반환
	if (node == NULL) return new_node(key);
	
	// 그렇지 않으면 순환적으로 트리 내려감
	if (key < node->data)
		node->left = insert_node(node->left, key);
	else if (key > node->data)
		node->right = insert_node(node->right, key);

	// 변경된 루트 포인터 반환
	return node;
} 

// 삭제 함수
void delete_node(TreeNode** root, int key)
{
	TreeNode* p, *child, *succ, *succ_p, *t; // key를 갖는 노드 t 탐색, p는 t의 부모노드
	p = NULL;
	t = *root;

	// key를 갖는 노드 t 탐색
	while (t != NULL && t->data != key)
	{
		p = t;
		t = (key < t->data) ? t->left : t->right;
	}

	// 탐색이 종료된 시점에 t가 NULL이면 트리 안에 key가 없음
	if (t == NULL) // 탐색하는 트리엔 없는 값
	{
		printf("찾는 값이 없습니다.\n");
		return;
	}
} */

void main()
{
	TreeNode* t = NULL;
	add(&t, 21);
	add(&t, 31);
	add(&t, 9);
	add(&t, 17);
	inorder(t);
}