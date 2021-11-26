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
				dp[i + 1][j + 1] = dp[i][j] + 1;			// 두 문자열의 문자가 같을 경우에는 오른쪽 아래 대각선 부분 + 1
			else											// 그렇지 않으면 왼쪽, 위쪽 중 큰 값 취함
				dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
		}
	}
	cout << dp[str1.length()][str2.length()] << "\n";

	int row = str1.length(), col = str2.length();			// 맨 아래 맨 오른쪽에서부터 역추적 시작
	stack<char> s;
	while (row > 0 && col > 0) {
		// dp테이블의 현재 위치 값이 왼쪽, 위쪽, 왼쪽 위 대각선 값보다 클 경우 현재 위치의 문자를 스택에 저장하고 왼쪽 위 대각선으로 이동
		if (dp[row][col] > dp[row - 1][col] && dp[row][col] > dp[row][col - 1] && dp[row][col] > dp[row - 1][col - 1]) {
			s.push(str1[row - 1]);
			row--, col--;
		}
		// 그렇지 않고 현재 위치 값이 위쪽 값보단 크고 왼쪽 값과 같으면 왼쪽으로 이동
		else if (dp[row][col] > dp[row - 1][col] && dp[row][col] == dp[row][col - 1])
			col--;
		// 그 외에는 위로 이동
		else
			row--;
	}
	while (!s.empty()) {
		cout << s.top();
		s.pop();
	}
	return 0;
}