#include <iostream>
#define MAX 1000000
using namespace std;

bool is_comp[MAX + 1];
string P;
int K;

void getPrime()							// �����佺�׳׽��� ü
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

	for (int i = 2; i < K; i++) {		// 2 �̻� K �̸��� ��� �Ҽ��鿡 ���� �׽�Ʈ
		if (is_comp[i])
			continue;

		int pre = 0;
		for (int j = 0; j < (int)P.length(); j++) {		// P�� ���� ���� �ڸ������� ���ʷ� ������ ����
			int cur = (pre + P[j] - '0') % i;			// ���� �� + ���� �ڸ� ���� ������ modulus ����
			
			pre = cur * 10;								// x10 �ؼ� ����
		}
		if (!pre) {
			cout << "BAD " << i;
			return 0;
		}
	}
	
	cout << "GOOD";
	return 0;
}