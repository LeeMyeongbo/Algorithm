#include <iostream>
#include <cmath>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

long long N, ans;

int main()
{
	FAST;
	cin >> N;
	for (long long i = 1; i < 10; i++) {
		long long p1 = (long long)pow(10, i - 1);
		long long p2 = (long long)pow(10, i);		// 항상 자료형은 맞춰 주자!
		if (N >= p1 && N < p2) {
			ans += i * (N - p1 + 1);
			break;
		}
		else
			ans += i * (p2 - p1);
	}
	cout << ans;
	return 0;
}