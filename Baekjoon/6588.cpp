#include <iostream>
#define MAX 1000000
using namespace std;

int n, a, b;
bool is_comp[MAX + 1];

void getPrime()
{
	for (int i = 2; i <= MAX; i++) {
		if (!is_comp[i]) {
			for (int j = i * 2; j < MAX; j += i)
				is_comp[j] = true;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	getPrime();
	while (true) {
		cin >> n;
		if (!n)
			return 0;

		for (int i = 3; i <= n; i++) {
			if (!is_comp[i] && !is_comp[n - i]) {
				cout << n << " = " << i << " + " << n - i << "\n";
				break;
			}
		}
	}
}