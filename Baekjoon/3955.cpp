#include <iostream>
#include <cmath>
using namespace std;

int T;
long long A, B, s, t, r;		// A : K, B : C

void extendedGcd(long long a, long long b) 
{
	long long s0 = 1, t0 = 0, r0 = a;
	long long s1 = 0, t1 = 1, r1 = b;
	long long temp;

	while (r1) {
		long long q = r0 / r1;

		temp = r0 - q * r1;
		r0 = r1;
		r1 = temp;

		temp = t0 - q * t1;
		t0 = t1;
		t1 = temp;

		temp = s0 - q * s1;
		s0 = s1;
		s1 = temp;
	}
	s = s0, t = t0, r = r0;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	// 1. 해 검증
	// D = gcd(A, B), Ax + By = C일 때 C % D == 0 이어야 해 가짐 (C % D != 0 --> 해 x)
	
	// 2. 초기 해
	// x0 = s * C / D, y0 = t * C / D;

	// 3. 일반해
	// x = x0 + B / D * k, y = y0 - A / D * k

	// 4. k 범위
	// x < 0  →  x0 + B / D * k < 0 --> k < -x0 / B
	// 0 < y <= 1e9  →  0 < y0 - A / D * k <= 1e9  →  -y0 < -A * k <= 1e9 - y0  →  (y0 - 1e9) / A <= k < y0 / A
	// (어차피 C = 1이라 D도 반드시 1임. 그래서 생략)
	// <= 일 때는 floor, < 일 때는 ceil
	
	// 5. 만족하는 k가 있는지 찾고 그 k를 통해 y를 구한다.

	cin >> T;
	while (T--) {
		cin >> A >> B;
		extendedGcd(A, B);

		if (r != 1)
			cout << "IMPOSSIBLE\n";
		else {
			long long x0 = s, y0 = t;
			long long kY = (long long)ceil((long double)y0 / A) - 1;
			long long kX = (long long)ceil((long double)-x0 / B) - 1;
			long long k = min(kY, kX);

			long long mink = (long long)ceil((long double)(y0 - 1e9) / A);
			if (k >= mink)
				cout << y0 - A * k << "\n";
			else
				cout << "IMPOSSIBLE\n";
		}
	}
	return 0;
}