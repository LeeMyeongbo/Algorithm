#include <iostream>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, Q, x, y, a, b;
long long arr[100001], tree[400004];

long long make_Tree(int index, int start, int end)
{
	if (start == end)
		return tree[index] = arr[start];
	return tree[index] = make_Tree(index * 2, start, (start + end) / 2) + make_Tree(index * 2 + 1, (start + end) / 2 + 1, end);
}

long long Find(int index, int start, int end)
{
	if (start > y || end < x)
		return 0;
	if (start >= x && end <= y)
		return tree[index];
	return Find(index * 2, start, (start + end) / 2) + Find(index * 2 + 1, (start + end) / 2 + 1, end);
}

long long update(int index, int start, int end)
{
	if (start > a || end < a)
		return tree[index];
	if (start == end)
		return tree[index] = arr[start] = b;
	return tree[index] = update(index * 2, start, (start + end) / 2) + update(index * 2 + 1, (start + end) / 2 + 1, end);
}

int main()
{
	FAST;
	cin >> N >> Q;
	for (int i = 1; i <= N; i++)
		cin >> arr[i];

	make_Tree(1, 1, N);
	for (int q = 0; q < Q; q++) {
		cin >> x >> y >> a >> b;
		int Min = min(x, y);
		int Max = max(x, y);
		x = Min, y = Max;

		cout << Find(1, 1, N) << "\n";
		update(1, 1, N);
	}
	return 0;
}