#include <iostream>
#include <cmath>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

long long G;

int main()
{
	FAST;
	cin >> G;
	long long left = 1, right = 1;
	bool possible = false;

	while (1) {
		long long v = right * right - left * left;
		if (v > G && right == left + 1)		// ���� ���ӵ� �ڿ��� ������ ���� G���� ũ�� �� �ڷδ� G�� ���� ���ɼ� �����Ƿ� ����
			break;
		if (v > G)
			left++;							// ������ ���� G���� ũ�� left + 1
		else {								// �׷��� ������ right + 1
			if (v == G) {
				cout << right << "\n";
				possible = true;
			}
			right++;
		}
	}
	if (!possible)
		cout << -1;

	return 0;
}