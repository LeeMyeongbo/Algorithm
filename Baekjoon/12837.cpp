#include <iostream>
using namespace std;

int N, Q, choice, p, q;
long long tree[4000004];

long long update(int index, int start, int end)
{
	if (start > p || end < p)
		return tree[index];
	if (start == end)
		return tree[index] += q;		// 값을 변경하는 게 아니라 추가한다고 했으므로
	return tree[index] = update(index * 2, start, (start + end) / 2) + update(index * 2 + 1, (start + end) / 2 + 1, end);
}

long long find(int index, int start, int end)
{
	if (start > q || end < p)
		return 0;
	if (start >= p && end <= q)
		return tree[index];
	return find(index * 2, start, (start + end) / 2) + find(index * 2 + 1, (start + end) / 2 + 1, end);
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N >> Q;

	for (int i = 0; i < Q; i++) {
		cin >> choice >> p >> q;
		if (choice == 1)
			update(1, 1, N);
		else
			cout << find(1, 1, N) << "\n";
	}
	return 0;
}