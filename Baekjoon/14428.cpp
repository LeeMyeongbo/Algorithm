#include <iostream>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, M, A[100001], seg_tree[400004], choice, i, j, Min_index[400004];

int Make_Tree(int index, int start, int end)
{
	if (start == end) {
		Min_index[index] = start;
		return seg_tree[index] = A[start];
	}
	int m1 = Make_Tree(index * 2, start, (start + end) / 2);
	int m2 = Make_Tree(index * 2 + 1, (start + end) / 2 + 1, end);
	
	if (m1 > m2) {
		Min_index[index] = Min_index[index * 2 + 1];
		return seg_tree[index] = m2;
	}
	else {
		Min_index[index] = Min_index[index * 2];
		return seg_tree[index] = m1;
	}
}

int Change(int index, int start, int end)
{
	if (i < start || i > end)
		return seg_tree[index];

	if (start == end)
		return seg_tree[index] = j;
	
	int m1 = Change(index * 2, start, (start + end) / 2);
	int m2 = Change(index * 2 + 1, (start + end) / 2 + 1, end);

	if (m1 > m2) {
		Min_index[index] = Min_index[index * 2 + 1];
		return seg_tree[index] = m2;
	}
	else {
		Min_index[index] = Min_index[index * 2];
		return seg_tree[index] = m1;
	}
}

pair<int, int> Find(int index, int start, int end)
{
	if (start > j || end < i)		// �󱸰� [start, end]�� �󱸰� [i, j] �ٱ��� ������ ��� (10^9 + 1, 0) ����
		return { 1000000001, 0 };

	if (start >= i && end <= j)		// �󱸰� [start, end]�� �󱸰� [i, j] ���ο� ������ ��� (�ش� ������ �ּڰ�, index) ����
		return { seg_tree[index], Min_index[index] };

	return min(Find(index * 2, start, (start + end) / 2), Find(index * 2 + 1, (start + end) / 2 + 1, end));
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> A[i];
	Make_Tree(1, 1, N);

	cin >> M;
	for (int n = 0; n < M; n++) {
		cin >> choice >> i >> j;
		if (choice == 1)
			Change(1, 1, N);
		else
			cout << Find(1, 1, N).second << "\n";
	}
	return 0;
}