#include <iostream>
#include <algorithm>
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

	cout << dp[str1.length()][str2.length()];
	return 0;
}