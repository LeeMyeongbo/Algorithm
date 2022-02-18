#include <iostream>
#include <vector>
//#include <fstream>
#define MAX 1<<14
using namespace std;

struct Tree {
    int num;
    Tree* left, * right, * parent;
} tree[MAX];
int T, V, E, v1, v2, parent, child, subtree;

int Find()                          // v1, v2의 조상들을 bottom-up 방식으로 쫙 저장하고 루트에서부터 차례대로 내려가며 lca 탐색
{
    Tree* tmp = nullptr;
    vector<int> v1_anc, v2_anc;

    tmp = tree + v1;
    while (tmp) {
        v1_anc.push_back(tmp->num);
        tmp = tmp->parent;
    }

    tmp = tree + v2;
    while (tmp) {
        v2_anc.push_back(tmp->num);
        tmp = tmp->parent;
    }

    int LCA = 0;
    while (v1_anc.back() == v2_anc.back()) {    // 반드시 마지막 부분부터 탐색하며 내려와야 함
        LCA = v1_anc.back();
        v1_anc.pop_back();
        v2_anc.pop_back();
    }

    return LCA;
}

void preorder(Tree* node)
{
    if (node) {
        subtree++;
        preorder(node->left);
        preorder(node->right);
    }
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    //ifstream fin;
    //fin.open("C:/Users/myeon/Downloads/input.txt");
    //fin >> T;
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        for (int i = 0; i < MAX; i++)
            tree[i] = { i, 0, 0, 0 };

        //fin >> V >> E >> v1 >> v2;
        cin >> V >> E >> v1 >> v2;

        for (int e = 0; e < E; e++) {
            //fin >> parent >> child;
            cin >> parent >> child;
            !tree[parent].left ? tree[parent].left = tree + child : tree[parent].right = tree + child;
            tree[child].parent = tree + parent;
        }

        int lca = Find();
        preorder(tree + lca);               // 전위순회 방식으로 서브트리 개수 헤아림

        cout << '#' << test_case << ' ' << lca << ' ' << subtree << "\n";
        subtree = 0;
    }
    return 0;
}
