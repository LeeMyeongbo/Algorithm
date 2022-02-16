#include <iostream>
#include <stack>
using namespace std;

int T, l;
string str;

int solve()
{
	stack<char> s;
	for (char c : str) {
		if (c == '(' || c == '[' || c == '{' || c == '<')
			s.push(c);
		else if (!s.empty() && ((c == ')' && s.top() == '(') || (c == ']' && s.top() == '[') || (c == '}' && s.top() == '{') || (c == '>' && s.top() == '<')))
			s.pop();
		else
			return 0;
	}
	if (s.empty())
		return 1;
	return 0;
}

int main(int argc, char** argv)
{
	for (int test_case = 1; test_case <= 10; ++test_case) {
		cin >> l >> str;

		cout << '#' << test_case << ' ' << solve() << endl;
	}
	return 0;
}