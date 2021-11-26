#include <iostream>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int K, N;
long long Lan[10000], sum, Left = 1, Right;

long long Solve()
{
	long long Result = 0;
	while (Left <= Right) {
		int n = 0;
		long long mid = (Left + Right) / 2;
		for (int i = 0; i < K; i++)
			n += Lan[i] / mid;
		if (n < N)
			Right = mid - 1;		// �ʿ��� �������� ���� ���� ��� ���̸� �� �� ����
		else {						// �ʿ��� ���� �̻��̶��
			if (Result < mid)
				Result = mid;		// mid �ִ� ����
			Left = mid + 1;			// ���̸� ����
		}
	}
	return Result;
}

int main()
{
	FAST;
	cin >> K >> N;
	for (int i = 0; i < K; i++) {
		cin >> Lan[i];
		sum += Lan[i];
		if (Right < Lan[i])
			Right = Lan[i];
	}
	cout << Solve();
	return 0;
}