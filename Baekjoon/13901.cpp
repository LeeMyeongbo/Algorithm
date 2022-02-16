#include <iostream>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int R, C, k, br, bc, sr, sc, dir[4];
const int dr[] = { -1, 1, 0, 0 }, dc[] = { 0, 0, -1, 1 };
char map[1000][1001];

void Solve()
{
	int cur_r = sr, cur_c = sc, dir_index = 0;
	while (1) {
		map[cur_r][cur_c] = 'r';

		int d;
		for (d = 0; ; d++) {
			int new_r = cur_r + dr[dir[(dir_index + d) % 4]];
			int new_c = cur_c + dc[dir[(dir_index + d) % 4]];
			if (new_r >= 0 && new_r < R && new_c >= 0 && new_c < C && !map[new_r][new_c]) {
				cur_r = new_r, cur_c = new_c, dir_index = (dir_index + d) % 4;
				break;
			}
			else if (d == 3) {
				cout << cur_r << " " << cur_c;
				return;
			}
		}
	}
}

int main()
{
	FAST;
	cin >> R >> C >> k;
	for (int i = 0; i < k; i++) {
		cin >> br >> bc;
		map[br][bc] = 'x';
	}
	cin >> sr >> sc;
	for (int i = 0; i < 4; i++) {
		cin >> dir[i];
		dir[i]--;
	}

	Solve();
	return 0;
}