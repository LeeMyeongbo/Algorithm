#include <iostream>
using namespace std;

pair<int, int> tree[101];

void preorder(int node)
{
    if (node)
    {
        cout << node << ' ';
        preorder(tree[node].first);
        preorder(tree[node].second);
    }
}

void inorder(int node)
{
    if (node)
    {
        inorder(tree[node].first);
        cout << node << ' ';
        inorder(tree[node].second);
    }
}

void postorder(int node)
{
    if (node)
    {
        postorder(tree[node].first);
        postorder(tree[node].second);
        cout << node << ' ';
    }
}

int main()
{
    int parent, child;

    for (int i = 0; i < 12; i++)
    {
        cin >> parent >> child;
        !tree[parent].first ? tree[parent].first = child : tree[parent].second = child;
    }

    cout << "전위 순회 : ";
    preorder(1);
    cout << "\n중위 순회 : ";
    inorder(1);
    cout << "\n후위 순회 : ";
    postorder(1);
    
    return 0;
}