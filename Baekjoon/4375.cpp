#include <iostream>
using namespace std;

int n;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	while (true) {
		cin >> n;
		if (cin.eof())
			return 0;

		int cnt = 0, r = 0;

		do {
			r = (r * 10 + 1) % n;
			cnt++;
		} while (r);

		cout << cnt << "\n";
	}
}