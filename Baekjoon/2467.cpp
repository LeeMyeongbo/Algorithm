#include <iostream>
#include <cmath>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, solu[100000];
struct cmp {
	bool operator()(const int& n1, const int& n2) const {
		return abs(n1) < abs(n2);
	}
};
pair<int, int> ans;

int main()
{
	FAST;
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> solu[i];

	sort(solu, solu + N, cmp());			// 절댓값 오름차순으로 정렬
	ans = { solu[0], solu[1] };
	int min = solu[0] + solu[1];

	for (int i = 1; i < N - 1; i++) {		// 인접한 거 2개씩 비교하며 합 최솟값 갱신
		if (abs(min) > abs(solu[i] + solu[i + 1])) {
			ans = { solu[i], solu[i + 1] };
			min = solu[i] + solu[i + 1];
		}
	}

	ans.first < ans.second ? cout << ans.first << " " << ans.second : cout << ans.second << " " << ans.first;
	return 0;
}