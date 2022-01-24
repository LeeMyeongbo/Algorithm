#include <iostream>
#define S 1048576
using namespace std;

int N, M, K;
long long a, b, c, tree[2 * S];					// tree[1] ~ tree[S - 1] : 내부노드, tree[S] ~ tree[2 * S - 1] : 리프노드

long long init(int left, int right, int node)	// 인덱스 트리 형성
{
	int mid = (left + right) / 2;

	if (left == right)
		return tree[node];
	return tree[node] = init(left, mid, node * 2) + init(mid + 1, right, node * 2 + 1);
}

void update(int node, long long diff)			// bottom-up 방식으로 갱신
{
	while (node) {
		tree[node] += diff;
		node /= 2;
	}
}

long long find(int left, int right, int node)	// top-down 방식으로 구간 합 도출
{
	int mid = (left + right) / 2;

	if (left > c || right < b)
		return 0;
	if (left >= b && right <= c)
		return tree[node];
	return find(left, mid, node * 2) + find(mid + 1, right, node * 2 + 1);
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M >> K;
	for (int i = 0; i < N; i++)
		cin >> tree[S + i];
	init(1, S, 1);

	for (int i = 0; i < M + K; i++) {
		cin >> a >> b >> c;
		if (a == 1) {
			int node = (int)b + S - 1;
			update(node, c - tree[node]);
		}
		else
			cout << find(1, S, 1) << "\n";
	}
	return 0;
}