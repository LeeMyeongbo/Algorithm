#include <iostream>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

string str, ans, str2;

int main()
{
	FAST;
	while (1) {
		char word[101] = { 0, };
		int n = 0;
		cin >> str;
		
		for (char c : str) {
			if (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == '-')
				word[n++] = c >= 'A' && c <= 'Z' ? c + 32 : c;
		}
		str2 = word;
		if (str2.length() > ans.length())
			ans = str2;
		if (str == "E-N-D")
			break;
	}
	cout << ans;
	return 0;
}