#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, A[1000000], index[1000000];		// index[i] : A[i]가 lis내에 위치하는 인덱스 저장
vector<int> lis;
stack<int> st;							// st : 최장 증가 부분 수열 추적용

void Solve()
{
	lis.push_back(A[0]);
	for (int i = 1; i < N; i++) {
		if (lis.back() < A[i]) {		// A[i]가 크면 lis에 바로 추가
			lis.push_back(A[i]);
			index[i] = lis.size() - 1;
		}
		else {							// 그렇지 않다면 A[i]가 들어갈 수 있는 최적의 위치(=lower bound)의 값을 A[i]로 변환
			int n = lower_bound(lis.begin(), lis.end(), A[i]) - lis.begin();
			lis[n] = A[i];
			index[i] = n;
		}
	}
	int s = lis.size();					// lis의 크기가 최장 증가 부분 수열의 크기 (내부 값들이 부분 수열의 원소인 것은 아님)
	cout << s-- << "\n";

	for (int i = N - 1; i >= 0; i--) {
		if (index[i] == s) {			// index[i]에 저장된 위치가 s와 같으면 A[i]를 스택에 push
			st.push(A[i]);
			s--;
		}
	}
	while (!st.empty()) {				// Last in First Out으로 pop하며 출력
		cout << st.top() << " ";
		st.pop();
	}
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> A[i];
	Solve();
	return 0;
}