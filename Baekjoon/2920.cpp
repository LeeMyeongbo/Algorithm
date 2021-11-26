#include <iostream>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int num[8];
bool ascending = true, descending = true;

int main()
{
	FAST;
	for (int i = 0; i < 8; i++)
		cin >> num[i];

	for (int i = 0; i < 8; i++)
		if (num[i] != i + 1)
			ascending = false;
	for (int i = 0; i < 8; i++)
		if (num[i] != 8 - i)
			descending = false;

	if (ascending)
		cout << "ascending";
	else if (descending)
		cout << "descending";
	else
		cout << "mixed";

	return 0;
}