#include <iostream>
#define S 131072					// 2^17
using namespace std;

int N, Q, x, y, a;
long long b, tree[2 * S];			// tree[1] ~ tree[S - 1] : 내부노드, tree[S] ~ tree[2 * S - 1] : 리프노드

long long init(int left, int right, int node)
{
	int mid = (left + right) / 2;

	if (left == right)
		return tree[node];
	return tree[node] = init(left, mid, node * 2) + init(mid + 1, right, node * 2 + 1);
}

void update(int node, long long diff)
{
	while (node) {
		tree[node] += diff;
		node /= 2;
	}
}

long long find(int left, int right, int node)
{
	int mid = (left + right) / 2;

	if (left > y || right < x)
		return 0;
	if (left >= x && right <= y)
		return tree[node];
	return find(left, mid, node * 2) + find(mid + 1, right, node * 2 + 1);
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N >> Q;
	for (int i = 0; i < N; i++)
		cin >> tree[S + i];
	init(1, S, 1);

	for (int i = 0; i < Q; i++) {
		cin >> x >> y >> a >> b;
		if (x > y)
			swap(x, y);
		cout << find(1, S, 1) << "\n";
		update(a + S - 1, b - tree[a + S - 1]);
	}
	return 0;
}