#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
using namespace std;		// 특정 칸에서 움직인 횟수의 최댓값을 한번 구하면 이후에 똑같은 칸에 다시 왔을 때 또 일일이 구할 필요가 없음을 이용(DP)

int N, M, Max_move[4][50][50];		// Max_move : 해당 칸에 방향 별로 최대한 움직일 수 있는 횟수를 저장해서 가지치기에 활용!
const int dr[] = { 0, 1, 0, -1 }, dc[] = { 1, 0, -1, 0 };			// 동 남 서 북 순으로 움직임
char map[50][51];
bool visited[4][50][50];			// 사이클이 존재하는 지 확인하기 위함

int dfs(int r, int c, int move)
{
	if (r < 0 || r >= N || c < 0 || c >= M || map[r][c] == 'H')		// 범위를 벗어나거나 구멍에 다다르면 바로 0 리턴
		return 0;

	for (int d = 0; d < 4; d++) {
		int R = r + dr[d] * (map[r][c] - '0');
		int C = c + dc[d] * (map[r][c] - '0');
		
		if (!visited[d][r][c]) {
			visited[d][r][c] = true;
			if (!Max_move[d][r][c])
				Max_move[d][r][c] = max(Max_move[d][r][c], dfs(R, C, move + 1) + 1);	// 방향 별로 움직일 수 있는 최대 횟수 갱신
			visited[d][r][c] = false;
		}
		else {						// 이미 방문한 곳 또 방문하면 사이클이 형성!
			printf("-1");
			exit(0);
		}
	}
	
	return max(max(Max_move[0][r][c], Max_move[1][r][c]), max(Max_move[2][r][c], Max_move[3][r][c]));	// 동 남 서 북 방향 중 최댓값
}

int main()
{
	if (!scanf("%d %d", &N, &M))
		return 1;
	for (int i = 0; i < N; i++)
		if (!scanf("%s", map + i))
			return 1;
	dfs(0, 0, 0);

	printf("%d", max(max(Max_move[0][0][0], Max_move[1][0][0]), max(Max_move[2][0][0], Max_move[3][0][0])));
	return 0;
}