#include <iostream>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define INF 1000000001
using namespace std;

int N, M, a, b, arr[100001], tree[400004];

int make_Tree(int index, int start, int end)
{
	if (start == end)
		return tree[index] = arr[start];
	return tree[index] = min(make_Tree(index * 2, start, (start + end) / 2), make_Tree(index * 2 + 1, (start + end) / 2 + 1, end));
}

int find(int index, int start, int end)
{
	if (start > b || end < a)
		return INF;
	if (start >= a && end <= b)
		return tree[index];
	return min(find(index * 2, start, (start + end) / 2), find(index * 2 + 1, (start + end) / 2 + 1, end));
}

int main()
{
	FAST;
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
		cin >> arr[i];
	make_Tree(1, 1, N);

	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		cout << find(1, 1, N) << "\n";
	}
	return 0;
}