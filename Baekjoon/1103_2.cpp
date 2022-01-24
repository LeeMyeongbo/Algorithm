#include <iostream>
#include <algorithm>
using namespace std;

int N, M, max_table[50][50], Ans;
bool visited[50][50];
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
char map[50][51];

void DFS(int depth, int r, int c)
{
	if (map[r][c] == 'H')								// H ������ ����
		return;

	visited[r][c] = true;								// üũ��
	for (int d = 0; d < 4; d++) {						// ����� �� ��ȸ
		int new_r = r + (map[r][c] - '0') * dr[d];
		int new_c = c + (map[r][c] - '0') * dc[d];
		if (new_r >= 0 && new_r < N && new_c >= 0 && new_c < M) {	// �������� ������ ����� ���� ���
			if (!visited[new_r][new_c]) {				// �� ���� �湮���� ���� �� �湮 ��
				if (!max_table[new_r][new_c])
					DFS(depth + 1, new_r, new_c);
				max_table[r][c] = max(max_table[r][c], 1 + max_table[new_r][new_c]);
			}
			else {										// �湮 ���� �� �湮 �� = ����Ŭ
				cout << -1;
				exit(0);
			}
		}
		else
			max_table[r][c] = max(max_table[r][c], 1);	// ���� ����ٸ� 1�� ���� ������ Ƚ�� �� �ִ� ����
	}
	visited[r][c] = false;								// üũ�ƿ�
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