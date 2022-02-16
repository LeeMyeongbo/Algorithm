#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

struct cmp {
	bool operator()(const int& left, const int& right) const {		// 연산자 오버로딩
		if (abs(left) > abs(right))
			return true;
		else if (abs(left) < abs(right))							// 절댓값 오름차순으로 정렬하도록 함
			return false;
		return left > right;
	}
};
int N, n;
priority_queue<int, vector<int>, cmp> q;

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