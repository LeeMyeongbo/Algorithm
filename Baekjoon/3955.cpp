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

	// 1. �� ����
	// D = gcd(A, B), Ax + By = C�� �� C % D == 0 �̾�� �� ���� (C % D != 0 --> �� x)
	
	// 2. �ʱ� ��
	// x0 = s * C / D, y0 = t * C / D;

	// 3. �Ϲ���
	// x = x0 + B / D * k, y = y0 - A / D * k

	// 4. k ����
	// x < 0  ��  x0 + B / D * k < 0 --> k < -x0 / B
	// 0 < y <= 1e9  ��  0 < y0 - A / D * k <= 1e9  ��  -y0 < -A * k <= 1e9 - y0  ��  (y0 - 1e9) / A <= k < y0 / A
	// (������ C = 1�̶� D�� �ݵ�� 1��. �׷��� ����)
	// <= �� ���� floor, < �� ���� ceil
	
	// 5. �����ϴ� k�� �ִ��� ã�� �� k�� ���� y�� ���Ѵ�.

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