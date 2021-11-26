#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

int N, A[500][500], a, b, c, d, e;
const int dr[] = { 0, 1, 0, -1 }, dc[] = { -1, 0, 1, 0 };		// ��-��-��-�� ��

int Solve()
{
	int start_r = N / 2, start_c = N / 2, ans = 0;		// ans : ���� ������ ���� �� ��
	for (int i = 1; i < N; i++) {
		if (i % 2) {									// i�� Ȧ���� ��
			for (int j = 0; j < i; j++) {				// ���� �������� iĭ��ŭ �̵��ϸ鼭 �𷡵� �̵�
				start_r += dr[0], start_c += dc[0];
				a = (int)(A[start_r][start_c] * 0.01);
				b = (int)(A[start_r][start_c] * 0.02);
				c = (int)(A[start_r][start_c] * 0.07);
				d = (int)(A[start_r][start_c] * 0.1);
				e = (int)(A[start_r][start_c] * 0.05);
				if (start_r - 1 >= 0 && start_r - 1 < N && start_c + 1 >= 0 && start_c + 1 < N)
					A[start_r - 1][start_c + 1] += a;
				else
					ans += a;
				if (start_r + 1 >= 0 && start_r + 1 < N && start_c + 1 >= 0 && start_c + 1 < N)
					A[start_r + 1][start_c + 1] += a;
				else
					ans += a;
				if (start_r - 2 >= 0 && start_r - 2 < N)
					A[start_r - 2][start_c] += b;
				else
					ans += b;
				if (start_r - 1 >= 0 && start_r - 1 < N)
					A[start_r - 1][start_c] += c;
				else
					ans += c;
				if (start_r + 1 >= 0 && start_r + 1 < N)
					A[start_r + 1][start_c] += c;
				else
					ans += c;
				if (start_r + 2 >= 0 && start_r + 2 < N)
					A[start_r + 2][start_c] += b;
				else
					ans += b;
				if (start_r - 1 >= 0 && start_r - 1 < N && start_c - 1 >= 0 && start_c - 1 < N)
					A[start_r - 1][start_c - 1] += d;
				else
					ans += d;
				if (start_r + 1 >= 0 && start_r + 1 < N && start_c - 1 >= 0 && start_c - 1 < N)
					A[start_r + 1][start_c - 1] += d;
				else
					ans += d;
				if (start_c - 2 >= 0 && start_c - 2 < N)
					A[start_r][start_c - 2] += e;
				else
					ans += e;
				int rest = A[start_r][start_c] - (2 * (a + b + c + d) + e);
				if (start_c - 1 >= 0 && start_c - 1 < N)
					A[start_r][start_c - 1] += rest;
				else
					ans += rest;
				A[start_r][start_c] = 0;
			}
			for (int j = 0; j < i; j++) {				// �׸��� �������� i��ŭ �̵�
				start_r += dr[1], start_c += dc[1];
				a = (int)(A[start_r][start_c] * 0.01);
				b = (int)(A[start_r][start_c] * 0.02);
				c = (int)(A[start_r][start_c] * 0.07);
				d = (int)(A[start_r][start_c] * 0.1);
				e = (int)(A[start_r][start_c] * 0.05);
				if (start_r - 1 >= 0 && start_r - 1 < N && start_c - 1 >= 0 && start_c - 1 < N)
					A[start_r - 1][start_c - 1] += a;
				else
					ans += a;
				if (start_r - 1 >= 0 && start_r - 1 < N && start_c + 1 >= 0 && start_c + 1 < N)
					A[start_r - 1][start_c + 1] += a;
				else
					ans += a;
				if (start_c - 2 >= 0 && start_c - 2 < N)
					A[start_r][start_c - 2] += b;
				else
					ans += b;
				if (start_c - 1 >= 0 && start_c - 1 < N)
					A[start_r][start_c - 1] += c;
				else
					ans += c;
				if (start_c + 1 >= 0 && start_c + 1 < N)
					A[start_r][start_c + 1] += c;
				else
					ans += c;
				if (start_c + 2 >= 0 && start_c + 2 < N)
					A[start_r][start_c + 2] += b;
				else
					ans += b;
				if (start_r + 1 >= 0 && start_r + 1 < N && start_c - 1 >= 0 && start_c - 1 < N)
					A[start_r + 1][start_c - 1] += d;
				else
					ans += d;
				if (start_r + 1 >= 0 && start_r + 1 < N && start_c + 1 >= 0 && start_c + 1 < N)
					A[start_r + 1][start_c + 1] += d;
				else
					ans += d;
				if (start_r + 2 >= 0 && start_r + 2 < N)
					A[start_r + 2][start_c] += e;
				else
					ans += e;
				int rest = A[start_r][start_c] - (2 * (a + b + c + d) + e);
				if (start_r + 1 >= 0 && start_r + 1 < N)
					A[start_r + 1][start_c] += rest;
				else
					ans += rest;
				A[start_r][start_c] = 0;
			}
		}
		else {											// i�� ¦���� ��
			for (int j = 0; j < i; j++) {				// ���� �������� iĭ��ŭ �̵��ϸ鼭 �𷡵� �̵�
				start_r += dr[2], start_c += dc[2];
				a = (int)(A[start_r][start_c] * 0.01);
				b = (int)(A[start_r][start_c] * 0.02);
				c = (int)(A[start_r][start_c] * 0.07);
				d = (int)(A[start_r][start_c] * 0.1);
				e = (int)(A[start_r][start_c] * 0.05);
				if (start_r - 1 >= 0 && start_r - 1 < N && start_c - 1 >= 0 && start_c - 1 < N)
					A[start_r - 1][start_c - 1] += a;
				else
					ans += a;
				if (start_r + 1 >= 0 && start_r + 1 < N && start_c - 1 >= 0 && start_c - 1 < N)
					A[start_r + 1][start_c - 1] += a;
				else
					ans += a;
				if (start_r - 2 >= 0 && start_r - 2 < N)
					A[start_r - 2][start_c] += b;
				else
					ans += b;
				if (start_r - 1 >= 0 && start_r - 1 < N)
					A[start_r - 1][start_c] += c;
				else
					ans += c;
				if (start_r + 1 >= 0 && start_r + 1 < N)
					A[start_r + 1][start_c] += c;
				else
					ans += c;
				if (start_r + 2 >= 0 && start_r + 2 < N)
					A[start_r + 2][start_c] += b;
				else
					ans += b;
				if (start_r - 1 >= 0 && start_r - 1 < N && start_c + 1 >= 0 && start_c + 1 < N)
					A[start_r - 1][start_c + 1] += d;
				else
					ans += d;
				if (start_r + 1 >= 0 && start_r + 1 < N && start_c + 1 >= 0 && start_c + 1 < N)
					A[start_r + 1][start_c + 1] += d;
				else
					ans += d;
				if (start_c + 2 >= 0 && start_c + 2 < N)
					A[start_r][start_c + 2] += e;
				else
					ans += e;
				int rest = A[start_r][start_c] - (2 * (a + b + c + d) + e);
				if (start_c + 1 >= 0 && start_c + 1 < N)
					A[start_r][start_c + 1] += rest;
				else
					ans += rest;
				A[start_r][start_c] = 0;
			}
			for (int j = 0; j < i; j++) {				// �׸��� �������� i��ŭ �̵�
				start_r += dr[3], start_c += dc[3];
				a = (int)(A[start_r][start_c] * 0.01);
				b = (int)(A[start_r][start_c] * 0.02);
				c = (int)(A[start_r][start_c] * 0.07);
				d = (int)(A[start_r][start_c] * 0.1);
				e = (int)(A[start_r][start_c] * 0.05);
				if (start_r + 1 >= 0 && start_r + 1 < N && start_c - 1 >= 0 && start_c - 1 < N)
					A[start_r + 1][start_c - 1] += a;
				else
					ans += a;
				if (start_r + 1 >= 0 && start_r + 1 < N && start_c + 1 >= 0 && start_c + 1 < N)
					A[start_r + 1][start_c + 1] += a;
				else
					ans += a;
				if (start_c - 2 >= 0 && start_c - 2 < N)
					A[start_r][start_c - 2] += b;
				else
					ans += b;
				if (start_c - 1 >= 0 && start_c - 1 < N)
					A[start_r][start_c - 1] += c;
				else
					ans += c;
				if (start_c + 1 >= 0 && start_c + 1 < N)
					A[start_r][start_c + 1] += c;
				else
					ans += c;
				if (start_c + 2 >= 0 && start_c + 2 < N)
					A[start_r][start_c + 2] += b;
				else
					ans += b;
				if (start_r - 1 >= 0 && start_r - 1 < N && start_c - 1 >= 0 && start_c - 1 < N)
					A[start_r - 1][start_c - 1] += d;
				else
					ans += d;
				if (start_r - 1 >= 0 && start_r - 1 < N && start_c + 1 >= 0 && start_c + 1 < N)
					A[start_r - 1][start_c + 1] += d;
				else
					ans += d;
				if (start_r - 2 >= 0 && start_r - 2 < N)
					A[start_r - 2][start_c] += e;
				else
					ans += e;
				int rest = A[start_r][start_c] - (2 * (a + b + c + d) + e);
				if (start_r - 1 >= 0 && start_r - 1 < N)
					A[start_r - 1][start_c] += rest;
				else
					ans += rest;
				A[start_r][start_c] = 0;
			}
		}
	}
	for (int j = 0; j < N - 1; j++) {				// ���������� �������� N - 1ĭ��ŭ �̵��ϸ鼭 �𷡵� �̵�
		start_r += dr[0], start_c += dc[0];
		a = (int)(A[start_r][start_c] * 0.01);
		b = (int)(A[start_r][start_c] * 0.02);
		c = (int)(A[start_r][start_c] * 0.07);
		d = (int)(A[start_r][start_c] * 0.1);
		e = (int)(A[start_r][start_c] * 0.05);
		if (start_r - 1 >= 0 && start_r - 1 < N && start_c + 1 >= 0 && start_c + 1 < N)
			A[start_r - 1][start_c + 1] += a;
		else
			ans += a;
		if (start_r + 1 >= 0 && start_r + 1 < N && start_c + 1 >= 0 && start_c + 1 < N)
			A[start_r + 1][start_c + 1] += a;
		else
			ans += a;
		if (start_r - 2 >= 0 && start_r - 2 < N)
			A[start_r - 2][start_c] += b;
		else
			ans += b;
		if (start_r - 1 >= 0 && start_r - 1 < N)
			A[start_r - 1][start_c] += c;
		else
			ans += c;
		if (start_r + 1 >= 0 && start_r + 1 < N)
			A[start_r + 1][start_c] += c;
		else
			ans += c;
		if (start_r + 2 >= 0 && start_r + 2 < N)
			A[start_r + 2][start_c] += b;
		else
			ans += b;
		if (start_r - 1 >= 0 && start_r - 1 < N && start_c - 1 >= 0 && start_c - 1 < N)
			A[start_r - 1][start_c - 1] += d;
		else
			ans += d;
		if (start_r + 1 >= 0 && start_r + 1 < N && start_c - 1 >= 0 && start_c - 1 < N)
			A[start_r + 1][start_c - 1] += d;
		else
			ans += d;
		if (start_c - 2 >= 0 && start_c - 2 < N)
			A[start_r][start_c - 2] += e;
		else
			ans += e;
		int rest = A[start_r][start_c] - (2 * (a + b + c + d) + e);
		if (start_c - 1 >= 0 && start_c - 1 < N)
			A[start_r][start_c - 1] += rest;
		else
			ans += rest;
		A[start_r][start_c] = 0;
	}
	return ans;
}

int main()
{
	if (!scanf("%d", &N))
		return 1;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (!scanf("%d", &A[i][j]))
				return 1;
	printf("%d\n", Solve());
	return 0;
}