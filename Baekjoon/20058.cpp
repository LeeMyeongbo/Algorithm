#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N, Q, A[1 << 6][1 << 6], L[1000];
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };			// �� �� �� �� ��

void rotate(int cur_r, int cur_c, int l)							// �ѿ������� ���α��� 90���� �ð���� ȸ��
{
	for (int stage = l / 2; stage > 0; stage--) {					// �ѿ������� ���α��� ������ �ϴ� �� Ƚ��
		int R = cur_r + l / 2 - stage, C = cur_c + l / 2 - stage;	// ������ �����ϴ� ����

		for (int i = 0; i < 2 * stage - 1; i++) {					// �� ������ �ϳ��� �̵��ϴ� �۾��� 90�� ȸ���� ������ �ݺ�
			int temp = A[R][C];
			for (int j = 0; j < 2 * stage - 1; j++)					// ���� ������ ���� �ϳ��� �̵�
				A[R + j][C] = A[R + j + 1][C];
			for (int j = 0; j < 2 * stage - 1; j++)					// �Ʒ��� ������ �������� �ϳ��� �̵�
				A[R + 2 * stage - 1][C + j] = A[R + 2 * stage - 1][C + j + 1];
			for (int j = 2 * stage - 1; j > 0; j--)					// ������ ������ �Ʒ��� �ϳ��� �̵�
				A[R + j][C + 2 * stage - 1] = A[R + j - 1][C + 2 * stage - 1];
			for (int j = 2 * stage - 1; j > 1; j--)					// ���� ������ ���������� �ϳ��� �̵�
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
				rotate(r, c, 1 << L[i]);							// ���̾���� ������ ������ ���� ���ʿ��� �� ���� ĭ �������� ȸ��
			}
		}
		bool chk[1 << 6][1 << 6] = { false, };						// ������ ���� �پ�� ��ġ ǥ�ÿ�
		for (int r = 0; r < (1 << N); r++) {
			for (int c = 0; c < (1 << N); c++) {
				int ice = 0;
				for (int d = 0; d < 4; d++) {
					int R = r + dr[d];
					int C = c + dc[d];
					if (R >= 0 && R < (1 << N) && C >= 0 && C < (1 << N) && A[R][C] > 0)	// ������ ������ �����ϸ� + 1
						ice++;
				}
				if (ice < 3)										// ������ ������ �ִ� ĭ�� 3������ ������ ������ �پ�� ��ġ
					chk[r][c] = true;								// �� ��ġ�� true�� üũ
			}
		}
		for (int r = 0; r < (1 << N); r++)
			for (int c = 0; c < (1 << N); c++)
				if (chk[r][c] && A[r][c] > 0)						// ������ ������ �����ϰ� true�� ǥ�õǾ� ������ ���� �پ��
					A[r][c]--;
	}
	queue<pair<int, int>> q;
	bool visited[1 << 6][1 << 6] = { false, };
	
	for (int r = 0; r < (1 << N); r++) {							// BFS�� ���� �� üũ
		for (int c = 0; c < (1 << N); c++) {
			if (visited[r][c] || !A[r][c])
				continue;
			int n = 0;												// ����� ���Ե� ĭ ����
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