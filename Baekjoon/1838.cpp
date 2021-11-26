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
		m.insert({ Copy[i], i });						// ���� �ش� ���� �ű� ��ġ ����

	for (int i = 0; i < N; i++) {
		it = m.lower_bound(A[i]);						// *it = (���� A[i], ���� A[i]�� �̵��� index)

		if (it->second > i)								// A[i]�� �ű� index�� ���� �ִ� index���� ũ�ٸ�
			to_higher++;								// ū ���� ���� ��Ʈ �� ������ ������ �ϴ� index�� �̵��ϱ� ����
		else
			to_lower = max(to_lower, i - it->second);	// ���� ���� ���� ��Ʈ �� ���� 1�� �������� �̵�
		m.erase(m.lower_bound(A[i]));
	}

	cout << max(to_higher, to_lower);
	return 0;
}