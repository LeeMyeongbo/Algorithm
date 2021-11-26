#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
using namespace std;

int N, T[1500001], P[1500001], dp[1500005], Max;		// dp[i] : N일로부터 역으로 계산하여 1일째까지 벌 수 있는 최대 수익 저장

int main()
{
	if (!scanf("%d", &N))
		return 1;

	for (int i = 1; i <= N; i++)
		if (!scanf("%d %d", T + i, P + i))
			return 1;
	
	for (int i = N; i > 0; i--) {
		if (i + T[i] <= N + 1)								// i일에 상담을 했을 경우 : 현재 상담 완료 수익 + 상담 완료 이후 날짜의 최대 수익
			dp[i] = max(dp[i + T[i]] + P[i], dp[i + 1]);	// 안 했을 경우 : 바로 다음 날짜의 최대 수익
		else
			dp[i] = dp[i + 1];								// 상담 완료 이후 날짜가 N + 1일을 넘어가면 상담 못함
	}
	printf("%d", dp[1]);
	return 0;
}