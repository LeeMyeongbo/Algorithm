#include <iostream>
#include <vector>
#include <cmath>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N;
vector<int> prime;
bool not_prime[4000001];

void get_prime()
{
	for (int i = 2; i <= (int)sqrt(N); i++) {
		if (!not_prime[i]) {
			for (int j = 2; i * j <= N; j++)
				not_prime[i * j] = true;
		}
	}
	for (int i = 2; i <= N; i++)		// N ������ �Ҽ��� ��� ����
		if (!not_prime[i])
			prime.push_back(i);
}

int Solve()
{
	int left = 0, right = 1, ans = 0, sum = 2;
	while (left <= right && right < prime.size()) {		// �� �����ͷ� ���ӵ� ���� N�� �����ϴ� ��� Ž��
		if (sum > N)
			sum -= prime[left++];
		else {
			if (sum == N)
				ans++;
			sum += prime[right++];
		}
	}
	while (right == prime.size() && left < prime.size()) {
		if (sum == N)
			ans++;
		sum -= prime[left++];
	}
	return ans;
}

int main()
{
	FAST;
	cin >> N;
	get_prime();

	cout << Solve();
	return 0;
}