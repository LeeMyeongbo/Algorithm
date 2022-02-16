#include <iostream>
#define MAX 100000
using namespace std;

int N, K, cnt;
bool is_comp[MAX];

int get_Prime()
{
	for (int i = 2; i <= N; i++) {
		if (!is_comp[i]) {
			for (int j = i; j <= N; j += i) {
				if (!is_comp[j]) {
					is_comp[j] = true;
					cnt++;
				}
				if (cnt == K)
					return j;
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N >> K;
	cout << get_Prime();
	return 0;
}