#include <iostream>
using namespace std;

char map[5][10];
bool visited[12];

void DFS(int row, int col)
{
	if (row == 5) {
		int val1 = map[1][1] - 'A' + map[1][3] - 'A' + map[1][5] - 'A' + map[1][7] - 'A';
		int val2 = map[3][1] - 'A' + map[3][3] - 'A' + map[3][5] - 'A' + map[3][7] - 'A';
		int val3 = map[0][4] - 'A' + map[1][3] - 'A' + map[2][2] - 'A' + map[3][1] - 'A';
		int val4 = map[0][4] - 'A' + map[1][5] - 'A' + map[2][6] - 'A' + map[3][7] - 'A';
		int val5 = map[4][4] - 'A' + map[3][3] - 'A' + map[2][2] - 'A' + map[1][1] - 'A';
		int val6 = map[4][4] - 'A' + map[3][5] - 'A' + map[2][6] - 'A' + map[1][7] - 'A';
		if (val1 == val2 && val2 == val3 && val3 == val4 && val4 == val5 && val5 == val6) {
			for (int i = 0; i < 5; i++)
				cout << map[i] << endl;
			exit(0);
		}
		return;
	}
	else if (col == 10)
		DFS(row + 1, 0);
	else if (map[row][col] != 'x')
		DFS(row, col + 1);
	else {
		for (char c = 'A'; c <= 'L'; c++) {
			if (!visited[c - 'A']) {
				visited[c - 'A'] = true;
				map[row][col] = c;
				DFS(row, col + 1);
				map[row][col] = 'x';
				visited[c - 'A'] = false;
			}
		}
	}
}

int main()
{
	for (int i = 0; i < 5; i++) {
		cin >> map[i];
		for (int j = 0; j < 10; j++)
			if (map[i][j] >= 'A' && map[i][j] <= 'L')
				visited[map[i][j] - 'A'] = true;
	}
	DFS(0, 0);
	return 0;
}