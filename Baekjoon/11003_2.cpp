#include <iostream>
#include <queue>
using namespace std;

priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int N, L, A;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N >> L;
	for (int i = 0; i < N; i++) {
		cin >> A;
		
		while (!pq.empty() && i - pq.top().second >= L)
			pq.pop();

		pq.push({ A, i });

		cout << pq.top().first << ' ';
	}
	return 0;
}