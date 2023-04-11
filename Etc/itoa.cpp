#include <iostream>
#include <string>
#include <deque>
using namespace std;

string itoa(int n)
{
    int N = n;
    string ans = "";
    if (N < 0) 
    {
        N = -N;
        ans.push_back('-');
    }

    deque<char> dq;
    while (N)
    {
        char c = N % 10 + '0';
        dq.push_front(c);
        N /= 10;
    }

    for (char c : dq)
        ans.push_back(c);
    
    return ans;
}

int main()
{
    int n;
    cin >> n;

    cout << itoa(n) << '\n';
    return 0;
}