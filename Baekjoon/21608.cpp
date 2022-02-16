#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int N, map[21][21], like[401][4], student, Ans;
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N * N; i++) {
		cin >> student;
		cin >> like[student][0] >> like[student][1] >> like[student][2] >> like[student][3];

		vector<pair<pair<int, int>, int>> info, empty;		// (칸 위치, 인접한 칸의 좋아하는 학생 수(empty는 비어있는 칸 수))
		for (int r = 1; r <= N; r++) {
			for (int c = 1; c <= N; c++) {
				if (map[r][c])					// 이미 누군가 앉았으면 skip
					continue;
				int sum = 0;
				for (int dir = 0; dir < 4; dir++) {		// 각 칸마다 인접한 좋아하는 학생 수 헤아림
					int R = r + dr[dir];
					int C = c + dc[dir];
					if (R >= 1 && R <= N && C >= 1 && C <= N) {
						for (int s = 0; s < 4; s++) {
							if (like[student][s] == map[R][C])
								sum++;
						}
					}
				}
				if (info.empty() || info[0].second == sum)
					info.push_back({ {r, c}, sum });
				else if (info[0].second < sum) {
					info.clear();
					info.push_back({ {r, c}, sum });
				}
			}
		}
		if (info.size() == 1) {			// 1번 조건을 만족하는 자리가 하나밖에 없으면 그 자리에 앉으면 됨
			map[info[0].first.first][info[0].first.second] = student;
			continue;
		}
		for (int k = 0; k < (int)info.size(); k++) {		// 2개 이상일 때 각 자리마다 인접한 빈 자리수 헤아림
			int r = info[k].first.first;
			int c = info[k].first.second;
			int sum = 0;
			for (int d = 0; d < 4; d++) {
				int R = r + dr[d];
				int C = c + dc[d];
				if (R >= 1 && R <= N && C >= 1 && C <= N && !map[R][C])
					sum++;
			}
			if (empty.empty() || empty[0].second == sum)
				empty.push_back({ info[k].first, sum });
			else if (empty[0].second < sum) {
				empty.clear();
				empty.push_back({ info[k].first, sum });
			}
		}
		map[empty[0].first.first][empty[0].first.second] = student;
	}
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			int n = 0;
			for (int d = 0; d < 4; d++) {
				int R = r + dr[d];
				int C = c + dc[d];
				if (R >= 1 && R <= N && C >= 1 && C <= N) {
					for (int l = 0; l < 4; l++) {
						if (map[R][C] == like[map[r][c]][l])
							n++;
					}
				}
			}
			Ans += (int)pow(10, n - 1);
		}
	}

	cout << Ans;
	return 0;
}