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
		if (sum >= M) {		// 챙긴 나무 전체 길이가 M 이상이라면 저장 + 높이를 보다 높게 잡음
			Ans = h;
			left = h + 1;
		}
		else
			right = h - 1;	// 그렇지 않다면 높이를 낮게 잡음
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