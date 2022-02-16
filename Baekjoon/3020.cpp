#include <iostream>
#include <algorithm>
using namespace std;

int N, H, h, seok[500001], jong[500001], height[500001], Ans;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N >> H;

	for (int i = 0; i < N; i++) {
		cin >> h;
		if (i % 2)
			jong[H - h + 1]++;			// 종유석 -> 부딪힐 수 있는 최소 높이에다가 +1
		else							// 예) H=5, 종유석 길이=2 일 때, 최소 높이 5-2+1=4일 때부터 부딪힐 수 있으므로 [4]에 +1
			seok[h]++;					// 석순 -> 부딪힐 수 있는 최대 높이에다가 +1
	}									// 예) H=5, 석순 길이=2일 때, 최대 높이 2일때까지만 부딪힐 수 있으므로 [2]에 +1

	for (int i = H; i > 1; i--)
		seok[i - 1] += seok[i];			// 석순은 인덱스가 작아질수록 누적합 저장
	for (int i = 1; i < H; i++)
		jong[i + 1] += jong[i];			// 종유석은 인덱스가 커질수록 누적합 저장

	for (int i = 1; i <= H; i++)
		height[i] = seok[i] + jong[i];

	sort(height + 1, height + H + 1);

	cout << height[1] << ' ';
	for (int i = 1; i <= H; i++)
		if (height[i] == height[1])
			Ans++;
	
	cout << Ans;
	return 0;
}