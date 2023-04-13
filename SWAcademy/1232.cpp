#include <iostream>
#include <stack>
#include <sstream>
using namespace std;

struct Node
{
    char c;
    int c1, c2, num;
    bool is_node;
};
stack<int> numbers;

void postorder(Node tree[], int num)
{
    if (tree[num].is_node)
    {
        postorder(tree, tree[num].c1);
        postorder(tree, tree[num].c2);
        if (tree[num].num)
            numbers.push(tree[num].num);
        else if (tree[num].c)
        {
            int n1 = numbers.top();
            numbers.pop();

            int n2 = numbers.top();
            numbers.pop();

            if (tree[num].c == '+') numbers.push(n2 + n1);
            else if (tree[num].c == '-') numbers.push(n2 - n1);
            else if (tree[num].c == '*') numbers.push(n2 * n1);
            else numbers.push(n2 / n1);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int N;

    for (int t = 1; t <= 10; t++)
    {
        Node tree[1001] = {0, };
        string str;

        cin >> N;
        cin.ignore();

        for (int n = 0; n < N; n++)
        {
            getline(cin, str);

            istringstream iss(str);
            string strs[5];
            int i = 0;

            while (getline(iss, strs[i++], ' '));

            int num = atoi(strs[0].c_str());
            if (strs[1] == "+" || strs[1] == "-" || strs[1] == "*" || strs[1] == "/")
            {
                tree[num].c = strs[1][0];
                tree[num].c1 = atoi(strs[2].c_str());
                tree[num].c2 = atoi(strs[3].c_str());
            }
            else
                tree[num].num = atoi(strs[1].c_str());
            tree[num].is_node = true;
        }
        postorder(tree, 1);

        cout << '#' << t << ' ' << numbers.top() << '\n';

        numbers.pop();
    }
    return 0;
}