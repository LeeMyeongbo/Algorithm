#include <iostream>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, choose, x, y;
long long tree[4000004];

long long find(int index, int start, int end)
{
	if (start > y || end < x)
		return 0;
	if (start >= x && end <= y)
		return tree[index];
	return find(index * 2, start, (start + end) / 2) + find(index * 2 + 1, (start + end) / 2 + 1, end);
}

long long update(int index, int start, int end)
{
	if (start > x || end < x)
		return tree[index];
	if (start == end)
		return tree[index] = y;
	return tree[index] = update(index * 2, start, (start + end) / 2) + update(index * 2 + 1, (start + end) / 2 + 1, end);
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> choose >> x >> y;
		if (!choose) {
			if (x > y) swap(x, y);
			cout << find(1, 1, N) << "\n";
		}
		else
			update(1, 1, N);
	}
	return 0;
}