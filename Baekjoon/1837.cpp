#include <iostream>
#define MAX 1000000
using namespace std;

bool is_comp[MAX + 1];
string P;
int K;

void getPrime()							// 에라토스테네스의 체
{
	for (int i = 2; i <= MAX; i++) {
		if (!is_comp[i]) {
			for (int j = i * 2; j < MAX; j += i)
				is_comp[j] = true;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	getPrime();
	cin >> P >> K;

	for (int i = 2; i < K; i++) {		// 2 이상 K 미만의 모든 소수들에 대해 테스트
		if (is_comp[i])
			continue;

		int pre = 0;
		for (int j = 0; j < (int)P.length(); j++) {		// P의 가장 높은 자리수부터 차례로 나머지 연산
			int cur = (pre + P[j] - '0') % i;			// 이전 값 + 현재 자리 숫자 값에서 modulus 연산
			
			pre = cur * 10;								// x10 해서 저장
		}
		if (!pre) {
			cout << "BAD " << i;
			return 0;
		}
	}
	
	cout << "GOOD";
	return 0;
}