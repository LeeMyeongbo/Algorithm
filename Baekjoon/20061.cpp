#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int N, t, x, y, blue_board[4][6], green_board[6][4];
int score, num;

void Falling_Blue(int X, int Y)				// 파란색 보드에서 오른쪽으로 떨어지는 거 (연한 파란색의 0열에서 시작)
{
	switch (t) {
	case 1:									// 1x1 블록을 최대한 오른쪽으로 밀기
		blue_board[X][Y] = 1;
		while (Y < 5 && !blue_board[X][Y + 1]) {
			blue_board[X][Y++] = 0;
			blue_board[X][Y] = 1;
		}
		break;
	case 2:									// 1x2 블록을 최대한 오른쪽으로 
		blue_board[X][Y] = blue_board[X][Y + 1] = 2;
		while (Y < 4 && !blue_board[X][Y + 2]) {
			blue_board[X][Y++] = 0;
			blue_board[X][Y + 1] = 2;
		}
		break;
	default:								// 2x1 블록을 최대한 오른쪽으로
		blue_board[X][Y] = blue_board[X + 1][Y] = 3;
		while (Y < 5 && !blue_board[X][Y + 1] && !blue_board[X + 1][Y + 1]) {
			blue_board[X][Y++] = blue_board[X + 1][Y] = 0;
			blue_board[X][Y] = blue_board[X + 1][Y] = 3;
		}
	}
}

void Falling_Green(int X, int Y)			// 녹색 보드에서 아래로 최대한 떨어지는 거 (연한 녹색의 0행에서 시작)
{
	switch (t) {
	case 1:									// 1x1 블록을 최대한 아래로
		green_board[X][Y] = 1;
		while (X < 5 && !green_board[X + 1][Y]) {
			green_board[X++][Y] = 0;
			green_board[X][Y] = 1;
		}
		break;
	case 2:									// 1x2 블록을 최대한 아래로
		green_board[X][Y] = green_board[X][Y + 1] = 2;
		while (X < 5 && !green_board[X + 1][Y] && !green_board[X + 1][Y + 1]) {
			green_board[X++][Y] = green_board[X][Y + 1] = 0;
			green_board[X][Y] = green_board[X][Y + 1] = 2;
		}
		break;
	default:								// 2x1 블록을 최대한 아래로
		green_board[X][Y] = green_board[X + 1][Y] = 3;
		while (X < 4 && !green_board[X + 2][Y]) {
			green_board[X++][Y] = 0;
			green_board[X + 1][Y] = 3;
		}
	}
}

void Process()
{
	for (int y = 2; y < 6; y++) {				// 진한 파란색 부분의 2열에서 5열까지 차례로 살피며 가득 찬 열이 있는지 확인
		bool full = true;
		for (int x = 0; x < 4; x++) {
			if (!blue_board[x][y]) {			// 비어있는 칸이 하나라도 있다면 해당 열은 가득찬 것이 아님
				full = false;
				break;
			}
		}
		if (full) {								// 현재 열이 가득 찼다면 점수 올리고 해당 열 비운 다음 오른쪽으로 한 열씩 이동
			score++;
			blue_board[0][y] = blue_board[1][y] = blue_board[2][y] = blue_board[3][y] = 0;
			for (int c = y; c > 0; c--)
				for (int x = 0; x < 4; x++)
					blue_board[x][c] = blue_board[x][c - 1];
		}
	}
	for (int x = 2; x < 6; x++) {				// 진한 녹색 부분의 2행에서 5행까지 차례로 살피며 가득 찬 행이 있는지 확인
		bool full = true;
		for (int y = 0; y < 4; y++) {
			if (!green_board[x][y]) {			// 비어있는 칸이 하나라도 있다면 해당 행은 가득찬 것이 아님
				full = false;
				break;
			}
		}
		if (full) {								// 현재 행이 가득 찼다면 점수 올리고 해당 행 비운 다음 아래쪽으로 한 행씩 이동
			score++;
			green_board[x][0] = green_board[x][1] = green_board[x][2] = green_board[x][3] = 0;
			for (int c = x; c > 0; c--)
				for (int y = 0; y < 4; y++)
					green_board[c][y] = green_board[c - 1][y];
		}
	}
	while (blue_board[0][1] || blue_board[1][1] || blue_board[2][1] || blue_board[3][1]) {		// 연한 파란 부분 비우기
		for (int y = 5; y > 0; y--)
			for (int x = 0; x < 4; x++)
				blue_board[x][y] = blue_board[x][y - 1];
		blue_board[0][0] = blue_board[1][0] = blue_board[2][0] = blue_board[3][0] = 0;
	}
	while (green_board[1][0] || green_board[1][1] || green_board[1][2] || green_board[1][3]) {	// 연한 녹색 부분 비우기
		for (int x = 5; x > 0; x--)
			for (int y = 0; y < 4; y++)
				green_board[x][y] = green_board[x - 1][y];
		green_board[0][0] = green_board[0][1] = green_board[0][2] = green_board[0][3] = 0;
	}
}

int main()
{
	if (!scanf("%d", &N))
		return 1;
	for (int i = 0; i < N; i++) {
		if (!scanf("%d %d %d", &t, &x, &y))
			return 1;
		Falling_Blue(x, 0);
		Falling_Green(0, y);
		Process();
	}
	printf("%d\n", score);
	for (int r = 0; r < 4; r++)
		for (int c = 0; c < 6; c++)
			if (blue_board[r][c])
				num++;
	for (int r = 0; r < 6; r++)
		for (int c = 0; c < 4; c++)
			if (green_board[r][c])
				num++;
	printf("%d", num);
	return 0;
}