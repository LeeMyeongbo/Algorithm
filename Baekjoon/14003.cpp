#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, A[1000000], index[1000000];		// index[i] : A[i]�� lis���� ��ġ�ϴ� �ε��� ����
vector<int> lis;
stack<int> st;							// st : ���� ���� �κ� ���� ������

void Solve()
{
	lis.push_back(A[0]);
	for (int i = 1; i < N; i++) {
		if (lis.back() < A[i]) {		// A[i]�� ũ�� lis�� �ٷ� �߰�
			lis.push_back(A[i]);
			index[i] = lis.size() - 1;
		}
		else {							// �׷��� �ʴٸ� A[i]�� �� �� �ִ� ������ ��ġ(=lower bound)�� ���� A[i]�� ��ȯ
			int n = lower_bound(lis.begin(), lis.end(), A[i]) - lis.begin();
			lis[n] = A[i];
			index[i] = n;
		}
	}
	int s = lis.size();					// lis�� ũ�Ⱑ ���� ���� �κ� ������ ũ�� (���� ������ �κ� ������ ������ ���� �ƴ�)
	cout << s-- << "\n";

	for (int i = N - 1; i >= 0; i--) {
		if (index[i] == s) {			// index[i]�� ����� ��ġ�� s�� ������ A[i]�� ���ÿ� push
			st.push(A[i]);
			s--;
		}
	}
	while (!st.empty()) {				// Last in First Out���� pop�ϸ� ���
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