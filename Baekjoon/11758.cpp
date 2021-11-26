#include <iostream>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int X1, X2, X3, Y1, Y2, Y3;

int main()
{
	FAST;
	cin >> X1 >> Y1 >> X2 >> Y2 >> X3 >> Y3;
	int ccw = X1 * Y2 + X2 * Y3 + X3 * Y1 - (Y1 * X2 + Y2 * X3 + Y3 * X1);
	if (ccw > 0)
		cout << 1;
	else if (ccw < 0)
		cout << -1;
	else
		cout << 0;
	return 0;
}