#include <iostream>
using namespace std;

int sudoku[9][9];

void DFS(int index)
{
	if (index == 81) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++)
				cout << sudoku[i][j] << ' ';
			cout << endl;
		}
		exit(0);
	}
	if (!sudoku[index / 9][index % 9]) {
		for (int n = 1; n <= 9; n++) {
			bool flag = true;

			for (int r = 0; r < 9; r++)
				if (sudoku[r][index % 9] == n)
					flag = false;

			for (int c = 0; c < 9; c++)
				if (sudoku[index / 9][c] == n)
					flag = false;

			int st_r = index / 9 - index / 9 % 3;
			int st_c = index % 9 - index % 9 % 3;
			for (int r = st_r; r < st_r + 3; r++)
				for (int c = st_c; c < st_c + 3; c++)
					if (sudoku[r][c] == n)
						flag = false;

			if (flag) {
				sudoku[index / 9][index % 9] = n;
				DFS(index + 1);
				sudoku[index / 9][index % 9] = 0;
			}
		}
	}
	else
		DFS(index + 1);
}

int main()
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			cin >> sudoku[i][j];

	DFS(0);
}