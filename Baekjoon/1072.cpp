#include <iostream>
using namespace std;

int X, Y, Z, Ans;

int win_rate(long double y, long double x)
{
	return (int)(y * 100. / x);
}

int solve()
{
	int low = 0, high = X;
	while (low <= high) {
		int middle = (high + low) / 2;
		if (Z < win_rate((long double)Y + middle, (long double)X + middle)) {
			Ans = middle;
			high = middle - 1;
		}
		else
			low = middle + 1;
	}
	return Ans;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> X >> Y;
	Z = win_rate((double)Y, (double)X);
	if (Z >= 99) {			// 이미 승률 99% 찍었으면 절대 100 찍을 일은 없음
		cout << -1;
		return 0;
	}

	cout << solve();
	return 0;
}