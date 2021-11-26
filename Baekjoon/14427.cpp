#include <iostream>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, A[100001], choice, i, graph, tree[400004];		// tree : 최솟값의 index 저장

int get_index(int i1, int i2)
{
	return min(make_pair(A[i1], i1), make_pair(A[i2], i2)).second;
}

int init(int index, int start, int end)
{
	if (start == end)
		return tree[index] = start;
	
	// 현 노드의 두 자식들 중 최솟값의 index를 저장
	return tree[index] = get_index(init(index * 2, start, (start + end) / 2), init(index * 2 + 1, (start + end) / 2 + 1, end));
}

int change(int index, int start, int end)
{
	if (i < start || i > end)
		return tree[index];

	if (start == end) {
		A[tree[index]] = graph;
		return tree[index];
	}
	return tree[index] = get_index(change(index * 2, start, (start + end) / 2), change(index * 2 + 1, (start + end) / 2 + 1, end));
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> A[i];
	init(1, 1, N);

	cin >> M;
	for (int q = 0; q < M; q++) {
		cin >> choice;
		if (choice == 1) {
			cin >> i >> graph;
			change(1, 1, N);
		}
		else
			cout << tree[1] << "\n";
	}
	return 0;
}