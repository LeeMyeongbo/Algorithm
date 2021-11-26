#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int N[9], Sum;

void Solve(int r, int start, int sum)
{
	static int choose[7];
	if (r == 7) {
		if (sum == 100) {
			for (int i = 0; i < 7; i++)
				printf("%d\n", choose[i]);
			exit(0);
		}
		return;
	}
	for (int i = start; i < 9; i++) {
		choose[r] = N[i];
		Solve(r + 1, i + 1, sum + N[i]);
		choose[r] = 0;
	}
}

int main()
{
	for (int i = 0; i < 9; i++) {
		if (!scanf("%d", N + i))
			return 1;
		Sum += N[i];
	}
	Solve(0, 0, 0);
	return 0;
}