#include <iostream>
//#include <fstream>
#define MAX 1<<7
using namespace std;

char tree[MAX], ch;
int N, num, child;

void inorder(int node)
{
    if (node <= N) {
        inorder(node * 2);
        cout << tree[node];
        inorder(node * 2 + 1);
    }
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    //ifstream fin;
    //fin.open("C:/Users/myeon/Downloads/input.txt");

    for (int test_case = 1; test_case <= 10; ++test_case) {
        //fin >> N;
        cin >> N;

        for (int i = 0; i < N; i++) {
            //fin >> num >> ch;
            cin >> num >> ch;
            tree[num] = ch;

            if (child + 1 <= N) {               // 완전 이진 트리이므로 반드시 자식들도 맨 앞 번호 정점부터 순서대로 딱딱 들어옴
                //fin >> child;
                cin >> child;                   // 왼쪽 자식부터 입력받음
            }
            if (child + 1 <= N) {
                //fin >> child;
                cin >> child;                   // 왼쪽 저장하고도 자식이 더 있다면 오른쪽 입력받음
            }
        }
        
        cout << '#' << test_case << ' ';
        inorder(1);                             // 중위 순회
        cout << "\n";
        child = 0;
    }
    return 0;
}
