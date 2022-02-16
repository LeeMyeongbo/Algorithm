#include <iostream>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define INF 1000000001
using namespace std;

int N, M, query, i, j, A[100001], tree[400004];

int init(int index, int start, int end)
{
	if (start == end)
		return tree[index] = A[start];
	return tree[index] = min(init(index * 2, start, (start + end) / 2), init(index * 2 + 1, (start + end) / 2 + 1, end));
}

int update(int index, int start, int end)
{
	if (start > i || end < i)
		return tree[index];
	if (start == end)
		return tree[index] = j;
	return tree[index] = min(update(index * 2, start, (start + end) / 2), update(index * 2 + 1, (start + end) / 2 + 1, end));
}

int find(int index, int start, int end)
{
	if (start > j || end < i)
		return INF;
	if (start >= i && end <= j)
		return tree[index];
	return min(find(index * 2, start, (start + end) / 2), find(index * 2 + 1, (start + end) / 2 + 1, end));
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> A[i];
	init(1, 1, N);

	cin >> M;
	for (int a = 0; a < M; a++) {
		cin >> query >> i >> j;
		if (query == 1)
			update(1, 1, N);
		else
			cout << find(1, 1, N) << "\n";
	}
	return 0;
}