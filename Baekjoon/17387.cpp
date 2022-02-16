#include <iostream>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;
typedef long long ll;

pair<ll, ll> l1, l2, l3, l4;

int CCW(pair<ll, ll> s1, pair<ll, ll> s2, pair<ll, ll> p) {
	ll val = s1.first * s2.second + s2.first * p.second + p.first * s1.second;
	val -= s1.second * s2.first + s2.second * p.first + p.second * s1.first;
	if (val < 0)
		return -1;
	else if (val > 0)
		return 1;
	return 0;
}

int solve()
{
	int ccw1 = CCW(l1, l2, l3) * CCW(l1, l2, l4), ccw2 = CCW(l3, l4, l1) * CCW(l3, l4, l2);
	if (ccw1 == 0 && ccw2 == 0) {			// 두 선분이 일직선상에 있을 경우
		if (l1 > l2)
			swap(l1, l2);
		if (l3 > l4)
			swap(l3, l4);					// 항상 작은 좌표 쪽을 l1, l3로 설정
		return l1 <= l4 && l3 <= l2;		// 두 선분이 만날 때 1, 아니면 0 리턴
	}
	return ccw1 <= 0 && ccw2 <= 0;
}

int main()
{
	FAST;
	cin >> l1.first >> l1.second >> l2.first >> l2.second >> l3.first >> l3.second >> l4.first >> l4.second;
	cout << solve();
	return 0;
}