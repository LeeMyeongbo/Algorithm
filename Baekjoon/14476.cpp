#include <iostream>
#include <algorithm>
using namespace std;

int N, arr[1000000], ltr_gcd[1000000], rtl_gcd[1000000], none_k[1000000], Ans, Max;	// ltr_gcd : 왼쪽에서부터 진행한 gcd 저장
																					// rtl_gcd : 오른쪽에서부터 진행한 gcd 저장
int gcd(int a, int b)																// none_k : k 제외한 나머지 수들의 gcd 저장
{
	int r = a % b;
	if (r)
		return gcd(b, r);
	return b;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> arr[i];
	ltr_gcd[0] = arr[0];
	rtl_gcd[N - 1] = arr[N - 1];				// ltr_gcd의 맨 왼쪽에는 첫번째 수를, rtl_gcd의 맨 오른쪽에는 마지막 번째 수를 저장

	for (int i = 1; i < N; i++) {
		int a = max(arr[i], ltr_gcd[i - 1]);
		int b = min(arr[i], ltr_gcd[i - 1]);
		ltr_gcd[i] = gcd(a, b);					// 왼쪽에서 2번째 수부터 시작하여 오른쪽으로 진행하면서 누적 gcd 진행, 저장
	}
	for (int i = N - 2; i >= 0; i--) {
		int a = max(arr[i], rtl_gcd[i + 1]);
		int b = min(arr[i], rtl_gcd[i + 1]);
		rtl_gcd[i] = gcd(a, b);					// 오른쪽에서 2번째 수부터 시작하여 왼쪽으로 진행하면서 누적 gcd 진행, 저장
	}

	none_k[0] = rtl_gcd[1];
	none_k[N - 1] = ltr_gcd[N - 2];

	for (int i = 1; i < N - 1; i++) {
		int a = max(ltr_gcd[i - 1], rtl_gcd[i + 1]);
		int b = min(ltr_gcd[i - 1], rtl_gcd[i + 1]);
		none_k[i] = gcd(a, b);					// 나머지 2번째 수부터 N - 1번째 수의 none_k는 왼쪽 ltr_gcd와 오른쪽 rtl_gcd의 gcd임!
	}

	for (int i = 0; i < N; i++) {
		if (arr[i] % none_k[i] && none_k[i] > Max) {	// none_k가 해당 k의 약수가 아니면서 최댓값 갱신 가능할 경우
			Max = none_k[i];
			Ans = arr[i];
		}
	}
	if (!Ans)
		cout << -1;								// Ans=0이다? -> 한 번도 갱신이 이루어지지 않았다는 의미
	else
		cout << Max << ' ' << Ans;
	return 0;
}