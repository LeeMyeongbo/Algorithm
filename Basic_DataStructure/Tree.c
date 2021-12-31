#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode // Ʈ���� ���Ÿ��
{
	int data;
	struct TreeNode* left, * right;
} TreeNode;

typedef struct QueueNode  // ť�� ����� Ÿ�� 
{
	TreeNode* item;
	struct QueueNode* link;
} QueueNode;

typedef struct Position // ť ����� �� ��(front), �� ��(rear)�� ����Ŵ
{
	QueueNode* front, * rear;
} QueueType;

// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// ť �ʱ�ȭ �Լ�
void init_q(QueueType* q)
{
	q->front = q->rear = NULL;
}

// ť ���� ���� ���� �Լ�
int is_empty(QueueType* q)
{
	return (q->front == NULL);
}

// ť ���� �Լ�
void enqueue(QueueType* q, TreeNode* item)
{
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	if (temp == NULL)
		error("�޸𸮸� �Ҵ��� �� �����ϴ�");
	else 
	{
		temp->item = item; 			// ������ ����
		temp->link = NULL; 			// ��ũ �ʵ带 NULL
		if (is_empty(q))			// ť�� �����̸�
		{ 		
			q->front = temp;
			q->rear = temp;
		}
		else						// ť�� ������ �ƴϸ�
		{ 		
			q->rear->link = temp;   // ������ �߿�
			q->rear = temp;
		}
	}
}

// ť ���� �Լ�
TreeNode* dequeue(QueueType* q)
{
	QueueNode* temp = q->front;
	TreeNode* item;
	if (is_empty(q))				// �������
		error("ť�� ��� �����ϴ�");
	else 
	{
		item = temp->item; 			// �����͸� ������.
		q->front = q->front->link;  // front�� ������带 ����Ű���� �Ѵ�.
		if (q->front == NULL) 		// ���� ����
			q->rear = NULL;
		free(temp); 				// �����޸� ����
		return item; 				// ������ ��ȯ
	}
}

//// Ʈ�� ��带 ����Ű�� �������� �ʱ�ȭ
//void init(TreeNode** p)
//{
//	*p = (TreeNode*)malloc(sizeof(TreeNode));
//	(*p)->left = NULL;
//	(*p)->right = NULL;
//}
//
//// ����ȭ (p : �θ� ���, c : �ڽ� ���)
//void insert(TreeNode* p, TreeNode* c)
//{
//	if (p->left == NULL)
//		p->left = c;
//	else if (p->right == NULL)
//		p->right = c;
//	else
//		printf("����ȭ�� �� �����ϴ�.\n");
//}
//
//// �ش� ��� �ʱ�ȭ �� ������ �߰�
//void addData(TreeNode** node, int data)
//{
//	init(node);
//	(*node)->data = data;
//}

// ���� ��ȸ
void inorder(TreeNode* root) 
{
	if (root != NULL) 
	{
		inorder(root->left);			// ���ʼ���Ʈ�� ��ȸ
		printf("[%d] ", root->data);    // ��� �湮
		inorder(root->right);			// �����ʼ���Ʈ�� ��ȸ
	}
}

// ���� ��ȸ
void preorder(TreeNode* root) 
{
	if (root != NULL) 
	{
		printf("[%d] ", root->data);	// ��� �湮
		preorder(root->left);			// ���ʼ���Ʈ�� ��ȸ
		preorder(root->right);			// �����ʼ���Ʈ�� ��ȸ
	}
}

// ���� ��ȸ
void postorder(TreeNode* root) 
{
	if (root != NULL) 
	{
		postorder(root->left);			// ���ʼ���Ʈ�� ��ȸ
		postorder(root->right);			// �����ʼ���Ʈ����ȸ
		printf("[%d] ", root->data);    // ��� �湮
	}
}

// ���� ��ȸ
void levelorder(TreeNode* root)
{
	QueueType* q = (QueueType*)malloc(sizeof(QueueType));
	init_q(q); 
	enqueue(q, root); // �� ó�� ť�� root��� ����
	TreeNode* temp = root;
	while (!is_empty(q))
	{
		temp = dequeue(q); // ť���� �� �տ� �ִ� ��带 �����ϰ� ������ ��带 temp�� ����
		if (temp->left != NULL)
			enqueue(q, temp->left); // ������ ����� left�� null�� �ƴϸ� ť�� ����
		if (temp->right != NULL)
			enqueue(q, temp->right); // ������ ����� right�� null�� �ƴϸ� ť�� ����
		printf("[%d] ", temp->data); // ������ ����� data ���
	}
	free(q);
}

// ��� ����
int get_node_count(TreeNode* node)
{
	int count = 0;
	if (node != NULL)
		count = 1 + get_node_count(node->left) + get_node_count(node->right);
	return count;
}

// �ܸ� ��� ���� 
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

// ���� ���ϱ�
int get_height(TreeNode* node)
{
	int height = 0;
	if (node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right));
	return height;
}

// ��ȯ���� Ž�� �Լ�
TreeNode* search1(TreeNode* node, int key)
{
	if (node == NULL) return NULL;
	if (key == node->data) return node; // 1
	else if (key < node->data)
		return search1(node->left, key); // 2
	else
		return search1(node->right, key); // 3
}

// �ݺ����� Ž�� �Լ�
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
	return NULL; // Ž���� �������� ��� NULL ��ȯ
}

// key�� ���� Ž�� Ʈ�� root�� ����
// key�� �̹� root�ȿ� ������ ���Ե��� ����
void add(TreeNode** root, int key)
{
	TreeNode* p, *t; // p�� �θ���, t�� ������
	TreeNode* n; // n�� ������
	t = *root;
	p = NULL;

	// Ž�� ���� ����
	while (t != NULL)
	{
		if (key == t->data) return;
		p = t;
		if (key < t->data)
			t = t->left;
		else
			t = t->right;
	}
	// key�� Ʈ�� �ȿ� �����Ƿ� ����
	n = (TreeNode*)malloc(sizeof(TreeNode));
	if (n == NULL) return;

	// ������ ����
	n->data = key;
	n->left = n->right = NULL;

	// �θ� ���� ��ũ ����
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

/*// ��ȯ ���
TreeNode* insert_node(TreeNode* node, int key)
{
	// Ʈ���� �����̸� ���ο� ��� ��ȯ
	if (node == NULL) return new_node(key);
	
	// �׷��� ������ ��ȯ������ Ʈ�� ������
	if (key < node->data)
		node->left = insert_node(node->left, key);
	else if (key > node->data)
		node->right = insert_node(node->right, key);

	// ����� ��Ʈ ������ ��ȯ
	return node;
} 

// ���� �Լ�
void delete_node(TreeNode** root, int key)
{
	TreeNode* p, *child, *succ, *succ_p, *t; // key�� ���� ��� t Ž��, p�� t�� �θ���
	p = NULL;
	t = *root;

	// key�� ���� ��� t Ž��
	while (t != NULL && t->data != key)
	{
		p = t;
		t = (key < t->data) ? t->left : t->right;
	}

	// Ž���� ����� ������ t�� NULL�̸� Ʈ�� �ȿ� key�� ����
	if (t == NULL) // Ž���ϴ� Ʈ���� ���� ��
	{
		printf("ã�� ���� �����ϴ�.\n");
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