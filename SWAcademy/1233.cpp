#include <iostream>
#include <stack>
#include <cstring>
#include <sstream>
using namespace std;

struct Node
{
    char c;
    int c1, c2, num;
    bool is_node;
};
Node tree[201];
stack<int> numbers;
bool is_possible = true;

void postorder(int num)
{
    if (!is_possible) 
        return;
    
    if (tree[num].is_node && is_possible)
    {
        postorder(tree[num].c1);
        postorder(tree[num].c2);
        if (tree[num].num)
            numbers.push(tree[num].num);
        else if (tree[num].c && numbers.size() > 1)
        {
            int n1 = numbers.top();
            numbers.pop();

            int n2 = numbers.top();
            numbers.pop();

            if (tree[num].c == '+') numbers.push(n2 + n1);
            else if (tree[num].c == '-') numbers.push(n2 - n1);
            else if (tree[num].c == '*') numbers.push(n2 * n1);
            else numbers.push(n2);
        }
        else
            is_possible = false;
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    int N;

    for (int t = 1; t <= 10; t++)
    {
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

            if (!(i == 5 && (strs[1] == "+" || strs[1] == "-" || strs[1] == "*" || strs[1] == "/")
                || i == 3 && strs[1].back() >= '0' && strs[1].back() <= '9'))
                is_possible = false;        // 연산자 + 숫자가 4개일 때는 반드시 연산자가 있어야 하고 2개일 때는 숫자밖에 없어야 함
                
            if (is_possible)
            {
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
        }
        postorder(1);

        cout << '#' << t << ' ';
        if (is_possible && numbers.size() == 1)
            cout << 1 << '\n';
        else
            cout << 0 << '\n';

        while (!numbers.empty())
            numbers.pop();
        memset(tree, 0, sizeof(tree));
        is_possible = true;
    }
    return 0;
}