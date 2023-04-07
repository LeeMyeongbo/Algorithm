#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_NODE 10000

enum { ADD_HEAD = 1, ADD_TAIL, ADD_NUM, FIND, REMOVE, PRINT, PRINT_REVERSE, END = 99 };

extern void init();
extern void addNode2Head(int data);
extern void addNode2Tail(int data);
extern void addNode2Num(int data, int num);
extern int findNode(int data);
extern void removeNode(int data);
extern int getList(int output[MAX_NODE]);
extern int getReversedList(int output[MAX_NODE]);

static void run() {
	while (1) {
		int cmd, data, num, cnt, i = 0;
		int output[MAX_NODE] = { 0 };

		scanf("%d", &cmd);
		switch (cmd) {
		case ADD_HEAD: // 1
			scanf("%d", &data);
			addNode2Head(data);
			break;
		case ADD_TAIL: // 2
			scanf("%d", &data);
			addNode2Tail(data);
			break;
		case ADD_NUM: // 3
			scanf("%d %d", &data, &num);
			addNode2Num(data, num);
			break;
		case FIND: // 4
			scanf("%d", &data);
			num = findNode(data);
			printf("%d\n", num);
			break;
		case REMOVE: // 5
			scanf("%d", &data);
			removeNode(data);
			break;
		case PRINT: // 6
			cnt = getList(output);
			while (cnt--)
				printf("%d ", output[i++]);
			printf("\n");
			break;
		case PRINT_REVERSE: // 7
			cnt = getReversedList(output);
			while (cnt--)
				printf("%d ", output[i++]);
			printf("\n");
			break;
		case END:
			return;
		}
	}
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

struct Node {
	int data;
	Node* prev;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].prev = nullptr;
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
    node->prev = head;
    node->next = head->next;

    if (head->next)
        head->next->prev = node;
    
    head->next = node;
}

void addNode2Tail(int data) 
{
    Node* node = getNode(data);
    Node* start = head;
    
    while (start->next)
        start = start->next;
    
    node->prev = start;
    start->next = node;
}

void addNode2Num(int data, int num) 
{
    Node* node = head;

    for (int i = 0; node && i < num; i++) 
        node = node->next;
    
    if (node)
    {
        Node* new_node = getNode(data);
        new_node->prev = node->prev;
        new_node->next = node;
        node->prev->next = new_node;
        node->prev = new_node;
    }
    else
        addNode2Tail(data);
}

int findNode(int data) 
{
    Node* node = head->next;

    for (int i = 1; node; i++)
    {
        if (node->data == data)
            return i;
        
        node = node->next;
    }

    return -1;
}

void removeNode(int data) 
{
    Node* node = head->next;
    while (node && node->data != data)
        node = node->next;
    
    if (node)
    {
        node->prev->next = node->next;
        if (node->next)
            node->next->prev = node->prev;
    }
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

int getReversedList(int output[MAX_NODE]) 
{
    int cnt = 0;
    Node* node = head;

    while (node->next)
        node = node->next;

    for (int i = 0; node != head; i++)
    {
        output[i] = node->data;
        node = node->prev;
        cnt++;
    }

    return cnt;
}