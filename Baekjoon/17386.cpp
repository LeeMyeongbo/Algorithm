#include <iostream>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

long long X1, X2, X3, X4, Y1, Y2, Y3, Y4;

int CCW(long long X1, long long X2, long long Y1, long long Y2, long long X3, long long Y3) {
	long long val = X1 * Y2 + X2 * Y3 + X3 * Y1 - (Y1 * X2 + Y2 * X3 + Y3 * X1);		// 선분 교차 판정
	if (val < 0)																		// (x1, y1)과 (x2, y2)는 선분, (x3, y3)는 점
		return -1;
	else if (val > 0)
		return 1;
	return 0;
}

int solve()
{
	if (CCW(X1, X2, Y1, Y2, X3, Y3) * CCW(X1, X2, Y1, Y2, X4, Y4) <= 0 && CCW(X3, X4, Y3, Y4, X1, Y1) * CCW(X3, X4, Y3, Y4, X2, Y2) <= 0)
		return 1;
	return 0;
}

int main()
{
	FAST;
	cin >> X1 >> Y1 >> X2 >> Y2 >> X3 >> Y3 >> X4 >> Y4;
	cout << solve();
	return 0;
}