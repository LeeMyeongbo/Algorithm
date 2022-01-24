#include <iostream>
#include <algorithm>
using namespace std;

int N, arr[1000000], ltr_gcd[1000000], rtl_gcd[1000000], none_k[1000000], Ans, Max;	// ltr_gcd : ���ʿ������� ������ gcd ����
																					// rtl_gcd : �����ʿ������� ������ gcd ����
int gcd(int a, int b)																// none_k : k ������ ������ ������ gcd ����
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
	rtl_gcd[N - 1] = arr[N - 1];				// ltr_gcd�� �� ���ʿ��� ù��° ����, rtl_gcd�� �� �����ʿ��� ������ ��° ���� ����

	for (int i = 1; i < N; i++) {
		int a = max(arr[i], ltr_gcd[i - 1]);
		int b = min(arr[i], ltr_gcd[i - 1]);
		ltr_gcd[i] = gcd(a, b);					// ���ʿ��� 2��° ������ �����Ͽ� ���������� �����ϸ鼭 ���� gcd ����, ����
	}
	for (int i = N - 2; i >= 0; i--) {
		int a = max(arr[i], rtl_gcd[i + 1]);
		int b = min(arr[i], rtl_gcd[i + 1]);
		rtl_gcd[i] = gcd(a, b);					// �����ʿ��� 2��° ������ �����Ͽ� �������� �����ϸ鼭 ���� gcd ����, ����
	}

	none_k[0] = rtl_gcd[1];
	none_k[N - 1] = ltr_gcd[N - 2];

	for (int i = 1; i < N - 1; i++) {
		int a = max(ltr_gcd[i - 1], rtl_gcd[i + 1]);
		int b = min(ltr_gcd[i - 1], rtl_gcd[i + 1]);
		none_k[i] = gcd(a, b);					// ������ 2��° ������ N - 1��° ���� none_k�� ���� ltr_gcd�� ������ rtl_gcd�� gcd��!
	}

	for (int i = 0; i < N; i++) {
		if (arr[i] % none_k[i] && none_k[i] > Max) {	// none_k�� �ش� k�� ����� �ƴϸ鼭 �ִ� ���� ������ ���
			Max = none_k[i];
			Ans = arr[i];
		}
	}
	if (!Ans)
		cout << -1;								// Ans=0�̴�? -> �� ���� ������ �̷������ �ʾҴٴ� �ǹ�
	else
		cout << Max << ' ' << Ans;
	return 0;
}