#include <iostream>
using namespace std;

int T, N, M;
char map[50][51];

bool Find()
{
	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < M - 1; j++) {
			if (map[i][j] == '#' && map[i][j + 1] == '#' && map[i + 1][j] == '#' && map[i + 1][j + 1] == '#')
				map[i][j] = map[i][j + 1] = map[i + 1][j] = map[i + 1][j + 1] = '.';
		}
	}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (map[i][j] == '#')
				return false;
	return true;
}

int main(int argc, char** argv)
{
	cin >> T;

	for (int test_case = 1; test_case <= T; ++test_case) {
		cin >> N >> M;
		for (int r = 0; r < N; r++)
			cin >> map[r];

		if (Find())
			cout << '#' << test_case << ' ' << "YES\n";
		else
			cout << '#' << test_case << ' ' << "NO\n";
	}

	return 0;
}