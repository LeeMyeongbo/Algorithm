#include <iostream>
using namespace std;

int N, map[50][50], k, ans = -1;

void DFS(int depth, int Max)							// depth :  ���� ��� ����, Max : �ִ� ������ ����
{
	if (depth < Max) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				for (int tile = 0; tile < 6; tile++) {
					if (tile != map[i][j]) {			// k = 1�� �� ������ Ÿ���� �ٸ� �ɷ� �ٲ�� �ϹǷ� �� ���� �߿�!!
						int tmp = map[i][j];
						map[i][j] = tile;
						DFS(depth + 1, Max);
						map[i][j] = tmp;				// �׻� ��Ͱ� ������ Ÿ���� ������� �����ؾ� ��
					}
				}
			}
		}
	}
	else {
		if (map[0][0] != 1 && map[0][0] != 5)			// �� ó�� ������ �� 1 �Ǵ� 5�� �ƴϸ� ���� ������ ���� ����
			return;

		int R = 0, C = 0, move = 1, dir = 0;	// move : ������ Ƚ��, dir : ���� �ٶ󺸰� �ִ� ���� (0 : ��, 1 : ��, 2 : ��, 3 : ��)
		bool flag = true;

		while (flag) {							// ���⼭���� ������...�Ǽ����� �ʵ��� ���� �����ؾ���
			if (map[R][C] == 0) {
				if (dir == 3 && C + 1 < N && map[R][C + 1] != 0 && map[R][C + 1] != 2 && map[R][C + 1] != 4)
					dir = 0, C++, move++;
				else if (dir == 1 && R + 1 < N && map[R + 1][C] != 0 && map[R + 1][C] != 1 && map[R + 1][C] != 5)
					dir = 2, R++, move++;
				else
					flag = false;				// �� �̻� ������ ���ϰ� �Ǹ� flag = false
			}
			else if (map[R][C] == 1) {
				if (dir == 0 && R + 1 < N && map[R + 1][C] != 0 && map[R + 1][C] != 1 && map[R + 1][C] != 5)
					dir = 2, R++, move++;
				else if (dir == 3 && C - 1 >= 0 && map[R][C - 1] != 1 && map[R][C - 1] != 3 && map[R][C - 1] != 4)
					dir = 1, C--, move++;
				else
					flag = false;
			}
			else if (map[R][C] == 2) {
				if (dir == 2 && C + 1 < N && map[R][C + 1] != 0 && map[R][C + 1] != 2 && map[R][C + 1] != 4)
					dir = 0, C++, move++;
				else if (dir == 1 && R - 1 >= 0 && map[R - 1][C] != 2 && map[R - 1][C] != 3 && map[R - 1][C] != 5)
					dir = 3, R--, move++;
				else
					flag = false;
			}
			else if (map[R][C] == 3) {
				if (dir == 0 && R - 1 >= 0 && map[R - 1][C] != 2 && map[R - 1][C] != 3 && map[R - 1][C] != 5)
					dir = 3, R--, move++;
				else if (dir == 2 && C - 1 >= 0 && map[R][C - 1] != 1 && map[R][C - 1] != 3 && map[R][C - 1] != 4)
					dir = 1, C--, move++;
				else
					flag = false;
			}
			else if (map[R][C] == 4) {
				if (dir == 3 && R - 1 >= 0 && map[R - 1][C] != 2 && map[R - 1][C] != 3 && map[R - 1][C] != 5)
					R--, move++;
				else if (dir == 2 && R + 1 < N && map[R + 1][C] != 0 && map[R + 1][C] != 1 && map[R + 1][C] != 5)
					R++, move++;
				else
					flag = false;
			}
			else {
				if (dir == 0 && C + 1 < N && map[R][C + 1] != 0 && map[R][C + 1] != 2 && map[R][C + 1] != 4)
					C++, move++;
				else if (dir == 1 && C - 1 >= 0 && map[R][C - 1] != 1 && map[R][C - 1] != 3 && map[R][C - 1] != 4)
					C--, move++;
				else
					flag = false;
			}
		}
		if (R == N - 1 && C == N - 1 && (map[R][C] == 2 || map[R][C] == 5)) {		// ���� �����ϰ� ���������� ���� �� �ִٸ�
			if (ans == -1)
				ans = move;
			ans = ans > move ? move : ans;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N >> k;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];

	DFS(0, k);			// ���� ��Ȯ�� �б�... �ִ� k���� �ƴ϶� ��Ȯ�� k���� ����
	
	cout << ans;
	return 0;
}