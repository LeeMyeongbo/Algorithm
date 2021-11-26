#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int Max, T, change;
string arr;

void dfs(int index, int depth) 
{
	if (depth == change) {
		Max = max(Max, stoi(arr));
		return;
	}
	for (int first = index; first < arr.length() - 1; first++) {			// �ߺ�����... ����� �ʱ�!!
		for (int second = first + 1; second < arr.length(); second++) {
			swap(arr[first], arr[second]);
			dfs(first, depth + 1);
			swap(arr[first], arr[second]);
		}
	}
}

int main(int argc, char** argv)
{
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		cin >> arr >> change;
		if (change > arr.length()) {		// ��ȯ Ƚ���� ���� ���̺��� �� ���
			if (change % 2 && arr.length() % 2 || !(change % 2) && !(arr.length() % 2))
				change = arr.length();		// ���� ���̿� ��ȯ Ƚ�� ��� ¦�� Ȥ�� Ȧ����� ���� ���̸�ŭ�� ��ȯ�ϸ� �� ����
			else
				change = arr.length() + 1;	// �װ� �ƴ϶�� �ִ� ���ڰ���+1 ��ŭ�� ��ȯ���൵ ���!
		}
		dfs(0, 0);
		cout << "#" << test_case << " " << Max << endl;
		Max = 0;
	}
	return 0;
}