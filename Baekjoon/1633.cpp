#include <iostream>
#include <vector>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, A[1000];
vector<int> lds;

int Solve()								// A[i]를 역순으로 저장한 후 최장 증가 부분 수열의 길이 도출
{
	lds.push_back(A[0]);
	for (int i = 1; i < N; i++) {
		if (A[i] <= lds.back()) {		// lower_bound를 이용한 풀이법 기억!
			int index = lower_bound(lds.begin(), lds.end(), A[i]) - lds.begin();
			lds[index] = A[i];			// A 배열 내 현재 값이 lds의 마지막 값보다 작은 경우엔 lower_bound 구해서 그 위치에 현재 값 저장
		}
		else
			lds.push_back(A[i]);		// A 배열 내 현재 값이 lds의 마지막 값보다 큰 경우엔 추가
	}
	return lds.size();
}

int main()
{
	FAST;
	cin >> N;
	for (int i = N - 1; i >= 0; i--)
		cin >> A[i];

	cout << Solve();
	return 0;
}