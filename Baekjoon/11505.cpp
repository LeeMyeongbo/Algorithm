#include <iostream>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define MAX 1000000007
using namespace std;

int N, M, K, a, b, c, A[1000001];
long long tree[4000004];

long long init(int index, int start, int end)
{
	if (start == end)
		return tree[index] = A[start];
	return tree[index] = init(index * 2, start, (start + end) / 2) * init(index * 2 + 1, (start + end) / 2 + 1, end) % MAX;
}

long long update(int index, int start, int end)
{
	if (b < start || b > end)
		return tree[index];
	if (start == end)
		return tree[index] = c;
	return tree[index] = update(index * 2, start, (start + end) / 2) * update(index * 2 + 1, (start + end) / 2 + 1, end) % MAX;
}

long long Find(int index, int start, int end)
{
	if (start > c || end < b)
		return 1;
	if (start >= b && end <= c)
		return tree[index];
	return Find(index * 2, start, (start + end) / 2) * Find(index * 2 + 1, (start + end) / 2 + 1, end) % MAX;
}

int main()
{
	FAST;
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++)
		cin >> A[i];
	init(1, 1, N);

	for (int i = 0; i < M + K; i++) {
		cin >> a >> b >> c;
		if (a == 1)
			update(1, 1, N);
		else
			cout << Find(1, 1, N) << "\n";
	}
	return 0;
}