#include <iostream>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

string str1, str2;
int dp[3003][3003];

int main()
{
	FAST;
	cin >> str1 >> str2;

	for (int i = 0; i < (int)str1.length(); i += 3) {
		for (int j = 0; j < (int)str2.length(); j += 3) {
			if (str1[i] == str2[j] && str1[i + 1] == str2[j + 1] && str1[i + 2] == str2[j + 2])
				dp[i + 3][j + 3] = dp[i][j] + 1;
			else
				dp[i + 3][j + 3] = max(dp[i][j + 3], dp[i + 3][j]);
		}
	}

	cout << dp[str1.length()][str2.length()];
	return 0;
}