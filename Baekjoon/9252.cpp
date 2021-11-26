#include <iostream>
#include <algorithm>
#include <stack>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

string str1, str2;
int dp[1001][1001];

int main()
{
	FAST;
	cin >> str1 >> str2;

	for (int i = 0; i < (int)str1.length(); i++) {
		for (int j = 0; j < (int)str2.length(); j++) {
			if (str1[i] == str2[j])
				dp[i + 1][j + 1] = dp[i][j] + 1;			// �� ���ڿ��� ���ڰ� ���� ��쿡�� ������ �Ʒ� �밢�� �κ� + 1
			else											// �׷��� ������ ����, ���� �� ū �� ����
				dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
		}
	}
	cout << dp[str1.length()][str2.length()] << "\n";

	int row = str1.length(), col = str2.length();			// �� �Ʒ� �� �����ʿ������� ������ ����
	stack<char> s;
	while (row > 0 && col > 0) {
		// dp���̺��� ���� ��ġ ���� ����, ����, ���� �� �밢�� ������ Ŭ ��� ���� ��ġ�� ���ڸ� ���ÿ� �����ϰ� ���� �� �밢������ �̵�
		if (dp[row][col] > dp[row - 1][col] && dp[row][col] > dp[row][col - 1] && dp[row][col] > dp[row - 1][col - 1]) {
			s.push(str1[row - 1]);
			row--, col--;
		}
		// �׷��� �ʰ� ���� ��ġ ���� ���� ������ ũ�� ���� ���� ������ �������� �̵�
		else if (dp[row][col] > dp[row - 1][col] && dp[row][col] == dp[row][col - 1])
			col--;
		// �� �ܿ��� ���� �̵�
		else
			row--;
	}
	while (!s.empty()) {
		cout << s.top();
		s.pop();
	}
	return 0;
}