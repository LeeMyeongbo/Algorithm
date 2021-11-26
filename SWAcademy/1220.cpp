#include <iostream>
using namespace std;

int N, map[100][100], cnt, Case;

int Solve()
{
	for (int r = N - 1; r >= 0; r--) {			// S������ �̵��ϴ� ���� �� �� �ڼ�ü�������� �����ؼ� ������ �ִ��� �������� Ž��
		for (int c = 0; c < N; c++) {
			if (map[r][c] == 1) {
				map[r][c] = 0;
				int R = r + 1;
				while (R < N && !map[R][c])		// ���� ����� �ǰų� �ٸ� �ڼ�ü ���� ������ �ݺ�
					R++;
				if (R < N)
					map[R - 1][c] = 1;			// �ٸ� �ڼ�ü ������ ��쿡�� �ٷ� ���� ��ġ��Ŵ
			}
		}
	}
	for (int r = 0; r < N; r++) {				// N������ �̵��ϴ� ���� �� �� �ڼ�ü�������� �����ؼ� ���� �ִ��� �ö󰡸� Ž��
		for (int c = 0; c < N; c++) {
			if (map[r][c] == 2) {
				map[r][c] = 0;
				int R = r - 1;
				while (R >= 0 && !map[R][c])	// ���� ����� �ǰų� �ٸ� �ڼ�ü ���� ������ �ݺ�
					R--;
				if (R >= 0)
					map[R + 1][c] = 2;			// �ٸ� �ڼ�ü ������ ��쿡�� �ٷ� �Ʒ��� ��ġ��Ŵ
			}
		}
	}
	int cur = 1;
	for (int c = 0; c < N; c++)
		for (int r = 0; r < N; r++) {			// �� �������� Ž��
			if (!map[r][c])
				continue;
			if (map[r][c] == 2 && cur == 1)		// �ڼ�ü�� N -> S�� �ٲ� ���� �������� ���� ����
				cnt++;
			cur = map[r][c];
		}
	return cnt;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	while (true) {
		cin >> N;
		if (cin.eof())
			return 0;

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> map[i][j];

		cout << "#" << ++Case << " " << Solve() << endl;
		cnt = 0;
	}
}