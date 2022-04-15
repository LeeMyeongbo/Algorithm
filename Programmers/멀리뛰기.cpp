#include <iostream>
#include <string>
#include <vector>

using namespace std;

long long solution(int n) 
{
    long long answer = 0;
    long long a = 1, b = 2;

    for (int i = 0; i < n - 2; i++) {
        answer = (a + b) % 1234567;
        a = b;
        b = answer;
    }
    return answer;
}

int main()
{
    int n;
    cin >> n;

    cout << solution(n);

    return 0;
}