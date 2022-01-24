#include <iostream>
#include <algorithm>
using namespace std;

long long N, M, tree[1000000], Ans;

long long solve()
{
	long long left = 0, right = tree[N - 1], h = (left + right) / 2;

	while (left <= right) {
		h = (left + right) / 2;
		long long sum = 0;
		for (int i = 0; i < N; i++) {
			if (h < tree[i])
				sum += (tree[i] - h);
		}
		if (sum >= M) {		// ì�� ���� ��ü ���̰� M �̻��̶�� ���� + ���̸� ���� ���� ����
			Ans = h;
			left = h + 1;
		}
		else
			right = h - 1;	// �׷��� �ʴٸ� ���̸� ���� ����
	}
	return Ans;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		cin >> tree[i];
	
	sort(tree, tree + N);

	cout << solve();
	return 0;
}