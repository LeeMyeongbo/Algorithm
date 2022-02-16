#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N, n;
priority_queue<int> dsc_pq;
priority_queue<int, vector<int>, greater<int>> asc_pq;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N;
	
	for (int i = 0; i < N; i++) {
		cin >> n;
		if (dsc_pq.empty())
			dsc_pq.push(n);
		else {
			if (n > dsc_pq.top())
				asc_pq.push(n);
			else
				dsc_pq.push(n);
		}
		int dsc_size = dsc_pq.size();
		int asc_size = asc_pq.size();

		if (dsc_size - asc_size > 1) {			// 최대 힙의 크기가 최소 힙 크기 + 1을 넘어설 경우
			asc_pq.push(dsc_pq.top());
			dsc_pq.pop();
			dsc_size--, asc_size++;
		}
		else if (asc_size - dsc_size > 0) {		// 최소 힙 크기가 최소 힙 크기를 넘어설 경우
			dsc_pq.push(asc_pq.top());
			asc_pq.pop();
			dsc_size++, asc_size--;
		}

		cout << dsc_pq.top() << "\n";
	}
	return 0;
}