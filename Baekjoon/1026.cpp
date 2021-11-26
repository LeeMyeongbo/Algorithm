#include <iostream>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, A[50], B[50], ans;

int main()
{
	FAST;
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> A[i];
	for (int i = 0; i < N; i++)
		cin >> B[i];

	sort(A, A + N);
	sort(B, B + N, greater<int>());
	for (int i = 0; i < N; i++)
		ans += A[i] * B[i];

	cout << ans;
	return 0;
}