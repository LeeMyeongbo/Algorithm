#include <iostream>
#include <vector>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, K, map[12][12], horse[11], r, c, dir;				// horse[i] : i�� ���� ���� ���� ���� (0 : ��, 1 : ��, 2 : ��, 3 : ��)
const int dr[] = { 0, -1, 0, 1 }, dc[] = { 1, 0, -1, 0 };	// �� �� �� �� �� (�ݴ� ���� ��ȯ ���� �ϱ� ����)
vector<int> cur[12][12];									// ���� ������ ��� �ִ��� ����
pair<int, int> pos[11];										// 1�� ������ �� ���� �� ��ġ ���� (��, ��)

void move_White(int h, int R, int C, int new_R, int new_C)	// ��� ĭ���� move
{
	for (int n : cur[R][C]) {
		cur[new_R][new_C].push_back(n);		// ���ʴ�� ����
		pos[n] = { new_R, new_C };
	}
	cur[R][C].clear();
}

void move_Red(int h, int R, int C, int new_R, int new_C)	// ������ ĭ���� move
{
	while (!cur[R][C].empty()) {
		int n = cur[R][C].back();

		cur[new_R][new_C].push_back(n);		// ������ ����
		pos[n] = { new_R, new_C };
		cur[R][C].pop_back();
	}
}

void move_Blue(int h, int R, int C)							// �Ķ��� ĭ���� move
{
	horse[h] = (horse[h] + 2) % 4;			// ���� �ݴ�� ��ȯ
	int new_R = R + dr[horse[h]];
	int new_C = C + dc[horse[h]];
	if (new_R >= 0 && new_R < N && new_C >= 0 && new_C < N) {
		if (!map[new_R][new_C])
			move_White(h, R, C, new_R, new_C);				// �����̰��� �ϴ� ĭ�� ����̶�� move_White
		else if (map[new_R][new_C] == 1)
			move_Red(h, R, C, new_R, new_C);				// �����̰��� �ϴ� ĭ�� �������̶�� move_Red
	}
}

bool Move(int h)
{
	int R = pos[h].first, C = pos[h].second;
	if (cur[R][C].size() && cur[R][C][0] == h) {			// �� ��ġ�� �� �Ʒ��� �����̰��� �ϴ� ���� ������ ���
		int new_R = R + dr[horse[h]];
		int new_C = C + dc[horse[h]];
		if (new_R >= 0 && new_R < N && new_C >= 0 && new_C < N) {
			if (!map[new_R][new_C])
				move_White(h, R, C, new_R, new_C);
			else if (map[new_R][new_C] == 1)
				move_Red(h, R, C, new_R, new_C);
			else
				move_Blue(h, R, C);
		}
		else
			move_Blue(h, R, C);
	}
	for (int R = 0; R < N; R++)
		for (int C = 0; C < N; C++)
			if (cur[R][C].size() >= 4)
				return false;
	return true;
}

int solve()
{
	for (int num = 1; num <= 1000; num++)
		for (int h = 1; h <= K; h++)			// 1�� ������ K�� ������ ���ʷ� ������ ��
			if (!Move(h))						// 4�� �̻��� ���� �� ĭ�� ���̸� �ٷ� ����
				return num;
	return -1;
}

int main()
{
	FAST;
	cin >> N >> K;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];
	for (int i = 1; i <= K; i++) {
		cin >> r >> c >> dir;
		cur[r - 1][c - 1].push_back(i);
		pos[i] = { r - 1, c - 1 };
		if (dir == 1 || dir == 4)
			horse[i] = dir - 1;
		else if (dir == 2)
			horse[i] = dir;
		else
			horse[i] = 1;
	}

	cout << solve();
	return 0;
}