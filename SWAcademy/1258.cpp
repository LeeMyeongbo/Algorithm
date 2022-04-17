#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int T, n, map[100][100];
bool visited[100][100];

bool cmp(const pair<int, int>& p1, const pair<int, int>& p2)
{
    if (p1.first * p1.second < p2.first * p2.second)
        return true;
    if (p1.first * p1.second == p2.first * p2.second && p1.first < p2.first)
        return true;

    return false;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> T;

	for(int test_case = 1; test_case <= T; ++test_case) {
        vector<pair<int, int>> ans;
        cin >> n;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> map[i][j];
        
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (map[r][c] && !visited[r][c]) {
                    int R = r, C = c;
                    for (R = r; R < n && map[R][c]; R++) {
                        for (C = c; C < n && map[R][C]; C++)
                            visited[R][C] = true;
                    }
                    ans.push_back({R - r, C - c});
                }
            }
        }
        sort(ans.begin(), ans.end(), cmp);

        cout << '#' << test_case << ' ' << ans.size() << ' ';
        for (auto& a : ans)
            cout << a.first << ' ' << a.second << ' ';
        cout << '\n';

        memset(visited, false, sizeof(visited));
	}
	return 0;
}