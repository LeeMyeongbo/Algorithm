#include <string>
#include <vector>
#include <stack>
using namespace std;

struct Node {
    int num;
    Node* prev, * next;
} node[1000000];
bool deleted[1000000];

string solution(int n, int k, vector<string> cmd) {
    string answer = "";
    stack<Node*> s;

    Node* now = node + k;
    node[0] = { 0, nullptr, node + 1 };
    for (int i = 1; i < n - 1; i++)
        node[i] = { i, node + i - 1, node + i + 1 };
    node[n - 1] = { n - 1, node + n - 2, nullptr };

    for (string& c : cmd) {
        if (c[0] == 'U' || c[0] == 'D') {
            string X;
            X.assign(c, 2, c.length() - 2);
            int x = stoi(X);

            if (c[0] == 'U')
                while (x--)
                    now = now->prev;
            else
                while (x--)
                    now = now->next;
        }
        else if (c[0] == 'C') {
            if (now->prev)
                now->prev->next = now->next;
            if (now->next)
                now->next->prev = now->prev;

            deleted[now->num] = true;
            s.push(now);
            if (now->next)
                now = now->next;
            else
                now = now->prev;
        }
        else {
            Node* node = s.top();
            s.pop();

            if (node->prev)
                node->prev->next = node;
            if (node->next)
                node->next->prev = node;
            deleted[node->num] = false;
        }
    }

    for (int i = 0; i < n; i++) {
        if (deleted[i])
            answer.push_back('X');
        else
            answer.push_back('O');
    }

    return answer;
}
