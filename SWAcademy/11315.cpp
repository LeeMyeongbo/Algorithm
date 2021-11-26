#include <iostream>
using namespace std;

char map[20][21];
int test_case, T, N, dr[] = { 0, 1, 1, 1 }, dc[] = { 1, 1, 0, -1 };

bool find()
{
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			for (int d = 0; d < 4; d++) {
				int R = r, C = c, num = 0;
				while (R >= 0 && R < N && C >= 0 && C < N && map[R][C] == 'o') {
					num++;
					R += dr[d], C += dc[d];
				}
				if (num >= 5)
					return true;
			}
		}
	}
	return false;
}

int main(int argc, char** argv)
{	
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		cin >> N;
		for (int i = 0; i < N; i++)
			cin >> map[i];

		cout << "#" << test_case << " ";
		if (find())
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}