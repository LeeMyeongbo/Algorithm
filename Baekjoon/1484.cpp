#include <iostream>
#include <cmath>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

long long G;

int main()
{
	FAST;
	cin >> G;
	long long left = 1, right = 1;
	bool possible = false;

	while (1) {
		long long v = right * right - left * left;
		if (v > G && right == left + 1)		// 서로 연속된 자연수 제곱의 차가 G보다 크면 이 뒤로는 G가 나올 가능성 없으므로 종료
			break;
		if (v > G)
			left++;							// 제곱의 차가 G보다 크면 left + 1
		else {								// 그렇지 않으면 right + 1
			if (v == G) {
				cout << right << "\n";
				possible = true;
			}
			right++;
		}
	}
	if (!possible)
		cout << -1;

	return 0;
}