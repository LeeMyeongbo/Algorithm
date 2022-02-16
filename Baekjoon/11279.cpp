#include <iostream>
#include <queue>
using namespace std;

int N, n;
priority_queue<int> q;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> n;
		if (n)
			q.push(n);
		else {
			if (q.empty())
				cout << 0 << "\n";
			else {
				cout << q.top() << "\n";
				q.pop();
			}
		}
	}
	return 0;
}