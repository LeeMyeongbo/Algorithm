#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N, Q, A[1 << 6][1 << 6], L[1000];
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };			// 동 서 남 북 순

void rotate(int cur_r, int cur_c, int l)							// 겉에서부터 내부까지 90도씩 시계방향 회전
{
	for (int stage = l / 2; stage > 0; stage--) {					// 겉에서부터 내부까지 돌려야 하는 총 횟수
		int R = cur_r + l / 2 - stage, C = cur_c + l / 2 - stage;	// 돌리기 시작하는 지점

		for (int i = 0; i < 2 * stage - 1; i++) {					// 각 변에서 하나씩 이동하는 작업을 90도 회전할 때까지 반복
			int temp = A[R][C];
			for (int j = 0; j < 2 * stage - 1; j++)					// 왼쪽 변에서 위로 하나씩 이동
				A[R + j][C] = A[R + j + 1][C];
			for (int j = 0; j < 2 * stage - 1; j++)					// 아래쪽 변에서 왼쪽으로 하나씩 이동
				A[R + 2 * stage - 1][C + j] = A[R + 2 * stage - 1][C + j + 1];
			for (int j = 2 * stage - 1; j > 0; j--)					// 오른쪽 변에서 아래로 하나씩 이동
				A[R + j][C + 2 * stage - 1] = A[R + j - 1][C + 2 * stage - 1];
			for (int j = 2 * stage - 1; j > 1; j--)					// 위쪽 변에서 오른쪽으로 하나씩 이동
				A[R][C + j] = A[R][C + j - 1];
			A[R][C + 1] = temp;
		}
	}
}

void Solve()
{
	int sum = 0, num = 0;
	for (int i = 0; i < Q; i++) {
		for (int r = 0; r < (1 << N); r += (1 << L[i])) {
			for (int c = 0; c < (1 << N); c += (1 << L[i])) {
				rotate(r, c, 1 << L[i]);							// 파이어스톰을 시전할 영역의 제일 왼쪽에서 맨 위의 칸 기준으로 회전
			}
		}
		bool chk[1 << 6][1 << 6] = { false, };						// 얼음의 양이 줄어들 위치 표시용
		for (int r = 0; r < (1 << N); r++) {
			for (int c = 0; c < (1 << N); c++) {
				int ice = 0;
				for (int d = 0; d < 4; d++) {
					int R = r + dr[d];
					int C = c + dc[d];
					if (R >= 0 && R < (1 << N) && C >= 0 && C < (1 << N) && A[R][C] > 0)	// 주위에 얼음이 존재하면 + 1
						ice++;
				}
				if (ice < 3)										// 주위에 얼음이 있는 칸이 3개보다 작으면 얼음이 줄어들 위치
					chk[r][c] = true;								// 그 위치에 true로 체크
			}
		}
		for (int r = 0; r < (1 << N); r++)
			for (int c = 0; c < (1 << N); c++)
				if (chk[r][c] && A[r][c] > 0)						// 얼음이 실제로 존재하고 true로 표시되어 있으면 얼음 줄어듦
					A[r][c]--;
	}
	queue<pair<int, int>> q;
	bool visited[1 << 6][1 << 6] = { false, };
	
	for (int r = 0; r < (1 << N); r++) {							// BFS로 최종 답 체크
		for (int c = 0; c < (1 << N); c++) {
			if (visited[r][c] || !A[r][c])
				continue;
			int n = 0;												// 덩어리에 포함된 칸 개수
			q.push({ r, c });
			visited[r][c] = true;

			while (!q.empty()) {
				int cur_r = q.front().first;
				int cur_c = q.front().second;
				q.pop();

				sum += A[cur_r][cur_c];
				n++;
				for (int d = 0; d < 4; d++) {
					int R = cur_r + dr[d];
					int C = cur_c + dc[d];
					if (R >= 0 && R < (1 << N) && C >= 0 && C < (1 << N) && !visited[R][C] && A[R][C]) {
						visited[R][C] = true;
						q.push({ R, C });
					}
				}
			}
			num = max(num, n);
		}
	}
	printf("%d\n%d", sum, num);
}

int main()
{
	cin >> N >> Q;
	for (int i = 0; i < (1 << N); i++)
		for (int j = 0; j < (1 << N); j++)
			cin >> A[i][j];
	for (int i = 0; i < Q; i++)
		cin >> L[i];
	Solve();
	return 0;
}