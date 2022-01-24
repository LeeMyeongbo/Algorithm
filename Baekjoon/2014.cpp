#include <iostream>
#include <queue>
using namespace std;

int K, N;
long long sosu[100], pre;
priority_queue<long long, vector<long long>, greater<long long>> pq;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> K >> N;
	for (int i = 0; i < K; i++) {
		cin >> sosu[i];
		pq.push(sosu[i]);
	}

	for (int i = 0; i < N; i++) {
		pre = pq.top();
		pq.pop();

		for (int k = 0; k < K; k++) {
			pq.push(pre * sosu[k]);
			if (!(pre % sosu[k]))
				break;
		}
	}

	cout << pre;
	return 0;
}