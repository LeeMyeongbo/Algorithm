#include <iostream>
//#include <fstream>
#define MAX 1<<7
using namespace std;

struct Node {
    char c;
    Node* left, * right;
} node[MAX];

void inorder(Node* node)
{
    if (node) {
        inorder(node->left);
        cout << node->c;
        inorder(node->right);
    }
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int N, num, child;
    char ch;

    //ifstream fin;
    //fin.open("C:/Users/myeon/Downloads/input.txt");

    for (int test_case = 1; test_case <= 10; ++test_case) {
        //fin >> N;
        cin >> N;

        for (int i = 1; i < MAX; i++)
            node[i] = { 0, 0, 0 };
        child = 0;

        for (int i = 0; i < N; i++) {
            //fin >> num >> ch;
            cin >> num >> ch;
            node[num].c = ch;

            if (child + 1 <= N) {               // 완전 이진 트리이므로 반드시 자식들도 맨 앞 번호 정점부터 순서대로 딱딱 들어옴
                //fin >> child;
                cin >> child;
                node[num].left = node + child;  // 왼쪽 자식부터 저장
            }
            if (child + 1 <= N) {
                //fin >> child;
                cin >> child;
                node[num].right = node + child; // 왼쪽 저장하고도 자식이 더 있다면 오른쪽 저장
            }
        }
        
        cout << '#' << test_case << ' ';
        inorder(node + 1);                      // 중위 순회
        cout << "\n";
    }
    return 0;
}
