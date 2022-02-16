#include <iostream>
#define MAX 100005
using namespace std;

int A[100000], N, S, Ans = MAX;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N >> S;
	for (int i = 0; i < N; i++)
		cin >> A[i];

	int left = 0, right = 0, sum = A[0];

	while (right + 1 < N && left < N) {
		if (sum >= S) {
			Ans = Ans > right - left + 1 ? right - left + 1 : Ans;
			sum -= A[left++];
		}
		else
			sum += A[++right];
	}

	while (left < N) {
		if (sum >= S)
			Ans = Ans > right - left + 1 ? right - left + 1 : Ans;
		sum -= A[left++];
	}

	if (Ans < MAX)
		cout << Ans;
	else
		cout << 0;

	return 0;
}