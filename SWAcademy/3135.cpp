#include <iostream>
using namespace std;

struct Node {
    int num;
    Node* next[26];
};
Node* head;

void init(void)
{
    head = new Node();
}

void insert(int buffer_size, char *buf) 
{
    Node* node = head;
    for (int i = 0; i < buffer_size; i++) {
        if (!node->next[buf[i] - 'a'])
            node->next[buf[i] - 'a'] = new Node();
        node->next[buf[i] - 'a']->num++;
        node = node->next[buf[i] - 'a'];
    }
}

int query(int buffer_size, char *buf)
{
    Node* node = head;
    for (int i = 0; i < buffer_size; i++) {
        if (!node->next[buf[i] - 'a'])
            return 0;
        node = node->next[buf[i] - 'a'];
    }
    return node->num;
}

void destroy(Node* node)
{
    for (int i = 0; i < 26; i++) {
        if (node->next[i])
            destroy(node->next[i]);
    }
    delete node;
}

int main(void) {
	int TestCase; 
	for (scanf("%d", &TestCase); TestCase--;) {
		int Query_N;
		scanf("%d", &Query_N);
		
		init();
        
		for (int i = 1; i <= Query_N; i++) {
			int type; scanf("%d", &type);

			if (type == 1) {
				char buf[15] = { 0, };
				scanf("%s", buf);
				
				int buffer_size = 0;
				while (buf[buffer_size]) buffer_size++;
				
				insert(buffer_size, buf);
			}
			else {
				char buf[15] = { 0, };
				scanf("%s", buf);
				
				int buffer_size = 0;
				while (buf[buffer_size]) buffer_size++;

				printf("%d\n", query(buffer_size, buf));
			}
		}
		printf("\n");
		fflush(stdout);
        destroy(head);
	}
}