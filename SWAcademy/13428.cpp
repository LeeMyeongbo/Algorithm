#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int T, N, Max, Min, change[2], jari;
char M[10];

void DFS(int depth, int cur)
{
	change[depth - 1] = cur;
	if (depth == 2) {
		swap(M[change[0]], M[change[1]]);
		if (M[0] != '0') {
			int new_n = atoi(M);
			Max = max(Max, new_n);
			Min = min(Min, new_n);
		}
		swap(M[change[0]], M[change[1]]);
	}
	else {
		for (int i = cur + 1; M[i]; i++)
			DFS(depth + 1, i);
	}
	change[depth - 1] = 0;
}

int main(int argc, char** argv)
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		cin >> N;
		Max = Min = N;

		jari = (int)log10(N);
		while (N) {
			M[jari--] = N % 10 + '0';
			N /= 10;
		}

		for (int i = 0; M[i]; i++)
			DFS(1, i);

		cout << '#' << test_case << ' ' << Min << ' ' << Max << "\n";
		fill(M, M + 10, 0);
	}
	return 0;
}