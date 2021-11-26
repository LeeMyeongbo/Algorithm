#include <iostream>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, K, a, b;
long long A[1000001], tree[4000004], c;

long long init(int index, int start, int end)		// 세그먼트 트리 형성
{
	if (start == end)
		return tree[index] = A[start];
	return tree[index] = init(index * 2, start, (start + end) / 2) + init(index * 2 + 1, (start + end) / 2 + 1, end);
}

long long update(int index, int start, int end)		// b에 해당하는 자리의 값 변경
{
	if (start > b || end < b)
		return tree[index];
	if (start == end)
		return tree[index] = c;
	return tree[index] = update(index * 2, start, (start + end) / 2) + update(index * 2 + 1, (start + end) / 2 + 1, end);
}

long long Find(int index, int start, int end)		// [b, c]에 해당하는 구간 합
{
	if (start > c || end < b)
		return 0;
	if (start >= b && end <= c)
		return tree[index];
	return Find(index * 2, start, (start + end) / 2) + Find(index * 2 + 1, (start + end) / 2 + 1, end);
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