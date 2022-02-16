#include <iostream>
#include <algorithm>
using namespace std;

string N;
int sum = 0;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	sort(N.begin(), N.end(), greater<char>());
	for (int i = 0; i < N.length(); i++)
		sum += N[i] - '0';
	
	if (!(sum % 3) && N[N.length() - 1] == '0')
		cout << N;
	else
		cout << -1;

	return 0;
}