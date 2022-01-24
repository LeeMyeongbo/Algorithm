#include <iostream>
using namespace std;

long long fib[91];
int n;

int main()
{
	fib[0] = 0, fib[1] = 1;
	for (int i = 2; i <= 90; i++)
		fib[i] = fib[i - 1] + fib[i - 2];

	cin >> n;
	cout << fib[n];

	return 0;
}