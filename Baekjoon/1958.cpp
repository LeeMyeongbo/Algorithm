#include <iostream>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

string str1, str2, str3;
int dp[101][101][101];

int main()
{
	FAST;
	cin >> str1 >> str2 >> str3;
	for (int i = 0; i < str1.length(); i++) {							// str1의 i번째 문자에 대해서 
		for (int j = 0; j < str2.length(); j++) {						// str2의 j번째 문자랑
			for (int k = 0; k < str3.length(); k++) {					// str3의 k번째 문자 비교 및 LCS 진행
				if (str1[i] == str2[j] && str2[j] == str3[k])			// 3개 문자가 모두 같다면
					dp[i + 1][j + 1][k + 1] = dp[i][j][k] + 1;			// 오른쪽 아래 대각선 쪽 아랫면 칸에 +1
				else {													// 그렇지 않다면 왼쪽, 위쪽, 위쪽 면의 칸 3개 중에서 최댓값 취함
					int M1 = max(dp[i + 1][j][k + 1], dp[i + 1][j + 1][k]);
					dp[i + 1][j + 1][k + 1] = max(M1, dp[i][j + 1][k + 1]);
				}
			}
		}
	}

	cout << dp[str1.length()][str2.length()][str3.length()];
	return 0;
}