#include <iostream>
#include <queue>
using namespace std;

int N, cards, ans;
priority_queue<int, vector<int>, greater<int>> q;		// 무조건 카드 묶음이 큰 것일수록 나중에 합치는 게 이득! 

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> cards;
		q.push(cards);
	}
	while (q.size() > 1) {
		int n1 = q.top();
		q.pop();
		int n2 = q.top();
		q.pop();

		ans += n1 + n2;
		q.push(n1 + n2);
	}
	cout << ans;
	return 0;
}