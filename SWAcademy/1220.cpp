#include <iostream>
using namespace std;

int N, map[100][100];

int Solve()										// 굳이 N과 S 동시에 이동시키지 않아도 됨!
{
	for (int r = N - 1; r >= 0; r--) 			// S극으로 이동하는 것은 맨 밑 자성체에서부터 시작해서 밑으로 최대한 내려가며 탐색
	{
		for (int c = 0; c < N; c++)
			if (map[r][c] == 1) 
			{
				map[r][c] = 0;
				int R = r + 1;
				while (R < N && !map[R][c])		// 맵을 벗어나게 되거나 다른 자성체 만날 때까지 반복
					R++;
				if (R < N)						// 다른 자성체 만났을 경우
					map[R - 1][c] = 1;
			}
	}
	for (int r = 0; r < N; r++) 				// N극으로 이동하는 것은 맨 위 자성체에서부터 시작해서 위로 최대한 올라가며 탐색
	{
		for (int c = 0; c < N; c++)
			if (map[r][c] == 2) 
			{
				map[r][c] = 0;
				int R = r - 1;
				while (R >= 0 && !map[R][c])	// 맵을 벗어나게 되거나 다른 자성체 만날 때까지 반복
					R--;
				if (R >= 0)
					map[R + 1][c] = 2;
			}
	}

	int cnt = 0;
	for (int c = 0; c < N; c++)
		for (int r = 0; r < N - 1; r++)
			if (map[r][c] == 1 && map[r + 1][c] == 2)	// ↓ 방향으로 탐색하면서 순서가 N→S 일때만 개수 헤아림
				cnt++;
	
	return cnt;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	for (int t = 0 ; t < 10; )
	{
		cin >> N;

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> map[i][j];

		cout << '#' << ++t << ' ' << Solve() << '\n';
	}

	return 0;
}