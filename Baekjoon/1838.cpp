#include <iostream>
#include <map>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, A[500000], Copy[500000], to_higher, to_lower;
multimap<int, int> m;
multimap<int, int> ::iterator it;

int main()
{
	FAST;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> A[i];
		Copy[i] = A[i];
	}
	sort(Copy, Copy + N);
	for (int i = 0; i < N; i++)
		m.insert({ Copy[i], i });						// 값과 해당 값이 옮긴 위치 저장

	for (int i = 0; i < N; i++) {
		it = m.lower_bound(A[i]);						// *it = (현재 A[i], 현재 A[i]가 이동한 index)

		if (it->second > i)								// A[i]가 옮긴 index가 원래 있던 index보다 크다면
			to_higher++;								// 큰 수는 버블 소트 한 번만에 가고자 하는 index로 이동하기 때문
		else
			to_lower = max(to_lower, i - it->second);	// 작은 수는 버블 소트 한 번에 1번 왼쪽으로 이동
		m.erase(m.lower_bound(A[i]));
	}

	cout << max(to_higher, to_lower);
	return 0;
}