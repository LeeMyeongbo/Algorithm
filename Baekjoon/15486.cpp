#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
using namespace std;

int N, T[1500001], P[1500001], dp[1500005], Max;		// dp[i] : N�Ϸκ��� ������ ����Ͽ� 1��°���� �� �� �ִ� �ִ� ���� ����

int main()
{
	if (!scanf("%d", &N))
		return 1;

	for (int i = 1; i <= N; i++)
		if (!scanf("%d %d", T + i, P + i))
			return 1;
	
	for (int i = N; i > 0; i--) {
		if (i + T[i] <= N + 1)								// i�Ͽ� ����� ���� ��� : ���� ��� �Ϸ� ���� + ��� �Ϸ� ���� ��¥�� �ִ� ����
			dp[i] = max(dp[i + T[i]] + P[i], dp[i + 1]);	// �� ���� ��� : �ٷ� ���� ��¥�� �ִ� ����
		else
			dp[i] = dp[i + 1];								// ��� �Ϸ� ���� ��¥�� N + 1���� �Ѿ�� ��� ����
	}
	printf("%d", dp[1]);
	return 0;
}