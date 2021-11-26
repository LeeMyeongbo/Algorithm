#include <iostream>
#include <queue>
using namespace std;

priority_queue<pair<int, int>> pq;		// (현재 숫자, index) 저장
int L, N, A;

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N >> L;
	for (int i = 0; i < N; i++) {
		cin >> A;

		pq.push({ -A, -i });
		while (-pq.top().second <= i - L)
			pq.pop();
		
		cout << -pq.top().first << ' ';
	}
	return 0;
}