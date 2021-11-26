#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int N, map[21][21], like[401][4], student, Ans;
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };

bool compare(pair<pair<int, int>, pair<int, int>> p1, pair<pair<int, int>, pair<int, int>> p2)
{
	return p1 > p2;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N * N; i++) {
		cin >> student;
		cin >> like[student][0] >> like[student][1] >> like[student][2] >> like[student][3];

		vector<pair<pair<int, int>, pair<int, int>>> info;			// ((�����ϴ� �л� ��, �� ĭ ��), (��, ��))
		for (int r = 1; r <= N; r++) {
			for (int c = 1; c <= N; c++) {
				if (map[r][c])										// �̹� ������ �ɾ����� skip
					continue;

				int st = 0, e = 0;
				for (int dir = 0; dir < 4; dir++) {
					int R = r + dr[dir];
					int C = c + dc[dir];
					if (R >= 1 && R <= N && C >= 1 && C <= N) {		// �������� 4�������� ���Ǹ�
						for (int s = 0; s < 4; s++)
							if (like[student][s] == map[R][C])		// �� ĭ���� ������ �����ϴ� �л� �� ��Ƹ�
								st++;
						if (!map[R][C])								// �� ĭ���� �� ĭ �� ��Ƹ�
							e++;
					}
				}
				info.push_back({ {st, e}, {r, c} });
			}
		}
		sort(info.begin(), info.end(), compare);			// ���� (�л� ��, ��ĭ ��)�� ���ؼ� �������� ����
		
		vector<pair<int, int>> rest;
		rest.push_back(info[0].second);
		for (int k = 1; k < (int)info.size(); k++) {
			if (info[k].first == info[0].first)				// �л� ���� ��ĭ �� ��� ���ٸ� (��, ��) ����
				rest.push_back(info[k].second);
			else
				break;
		}
		sort(rest.begin(), rest.end());						// (��, ��) �������� ����

		map[rest[0].first][rest[0].second] = student;
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