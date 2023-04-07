#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_NODE 10000

enum { ADD_HEAD = 1, ADD_TAIL, ADD_NUM, REMOVE, PRINT, END = 99 };

extern void init();
extern void addNode2Head(int data);
extern void addNode2Tail(int data);
extern void addNode2Num(int data, int num);
extern void removeNode(int data);
extern int getList(int output[MAX_NODE]);

static void run() {
	while (1) {
		int cmd, data, num, cnt, i;
		int output[MAX_NODE] = { 0 };

		scanf("%d", &cmd);
		switch (cmd) {
		case ADD_HEAD:
			scanf("%d", &data);
			addNode2Head(data);
			break;
		case ADD_TAIL:
			scanf("%d", &data);
			addNode2Tail(data);
			break;
		case ADD_NUM:
			scanf("%d %d", &data, &num);
			addNode2Num(data, num);
			break;
		case REMOVE:
			scanf("%d", &data);
			removeNode(data);
			break;
		case PRINT:
			cnt = getList(output);
			i = 0;
			while (cnt--)
				printf("%d ", output[i++]);
			printf("\n");
			break;
		case END:
			return;
		}
	}
}

struct Node {
	int data;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void init()
{
    head = getNode(0);
}

void addNode2Head(int data) 
{
    Node* node = getNode(data);
    node->next = head->next;
    head->next = node;
}

void addNode2Tail(int data) 
{
    Node* node = head;

    while (node->next)
        node = node->next;
    
    node->next = getNode(data);
}

void addNode2Num(int data, int num) 
{
    Node* node = head;
    Node* prev = nullptr;

    for (int i = 0; node && i < num; i++) 
    {
        prev = node;
        node = node->next;
    }
    
    if (prev)
    {
        Node* new_node = getNode(data);
        new_node->next = prev->next;
        prev->next = new_node;
    }
}

void removeNode(int data) 
{
    Node* node = head;
    Node* prev = nullptr;

    while (node && node->data != data) 
    {
        prev = node;
        node = node->next;
    }

    if (node)
        prev->next = node->next;
}

int getList(int output[MAX_NODE]) 
{
    int cnt = 0;
    Node* node = head->next;
    for (int i = 0; node; i++)
    {
        output[i] = node->data;
        node = node->next;
        cnt++;
    }

    return cnt;
}

int main(void) {
	int T;
	scanf("%d", &T);
    
	for (int t = 1; t <= T; t++) {
		printf("#%d\n", t);
		init();
		run();
		printf("\n");
	}

	return 0;
}