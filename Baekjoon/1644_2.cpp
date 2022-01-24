#include <iostream>
#include <vector>
#define MAX 5000000
using namespace std;

int N;
bool is_comp[MAX];							// 합성수를 true로 표시
vector<int> prime;

void get_Prime()							// 에라토스테네스의 체
{
	for (int i = 2; i < MAX; i++) {
		if (!is_comp[i]) {
			for (int j = i * 2; j < MAX; j += i)
				is_comp[j] = true;
			prime.push_back(i);
		}
	}
}

int solve()
{
	int left = 0, right = 0, cnt = 0, sum = prime[left];

	while (right + 1 < (int)prime.size() && left <= right) {
		if (sum < N)
			sum += prime[++right];
		else {
			if (sum == N)
				cnt++;
			sum -= prime[left++];
		}
	}
	
	return cnt;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	get_Prime();
	cin >> N;
	cout << solve();
	return 0;
}