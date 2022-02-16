#include <iostream>
using namespace std;

int A[10000], N, M, Ans;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		cin >> A[i];

	int left = 0, right = 0, sum = A[0];

	while (right + 1 < N && left < N) {
		if (sum > M)
			sum -= A[left++];
		else if (sum < M)
			sum += A[++right];
		else {
			Ans++;
			sum -= A[left++];
		}
	}
	while (left < N) {
		if (sum == M)
			Ans++;
		sum -= A[left++];
	}

	cout << Ans;
	return 0;
}