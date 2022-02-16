#include <iostream>
#include <algorithm>
using namespace std;

int N, M, max_table[50][50], Ans;
bool visited[50][50];
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
char map[50][51];

void DFS(int depth, int r, int c)
{
	if (map[r][c] == 'H')								// H 만나면 종료
		return;

	visited[r][c] = true;								// 체크인
	for (int d = 0; d < 4; d++) {						// 연결된 곳 순회
		int new_r = r + (map[r][c] - '0') * dr[d];
		int new_c = c + (map[r][c] - '0') * dc[d];
		if (new_r >= 0 && new_r < N && new_c >= 0 && new_c < M) {	// 움직여도 범위를 벗어나지 않을 경우
			if (!visited[new_r][new_c]) {				// 한 번도 방문하지 않은 곳 방문 시
				if (!max_table[new_r][new_c])
					DFS(depth + 1, new_r, new_c);
				max_table[r][c] = max(max_table[r][c], 1 + max_table[new_r][new_c]);
			}
			else {										// 방문 중인 곳 방문 시 = 사이클
				cout << -1;
				exit(0);
			}
		}
		else
			max_table[r][c] = max(max_table[r][c], 1);	// 범위 벗어난다면 1과 현재 움직인 횟수 중 최댓값 저장
	}
	visited[r][c] = false;								// 체크아웃
}

int main()
{
	cin >> N >> M;
	for (int r = 0; r < N; r++)
		cin >> map[r];

	DFS(0, 0, 0);
	
	cout << max_table[0][0];
	return 0;
}