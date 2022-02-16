#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int T, num, dp[27];
string card;
vector<int> tmp;
vector<vector<int>> possible_list;
vector<string> cards;

bool chk(string c1, string c2, string c3) {
	for (int d = 0; d < 4; d++) {
		if (c1[d] == c2[d] && c2[d] == c3[d])
			return true;
	}
	for (int d = 0; d < 4; d++) {
		if (!(c1[d] != c2[d] && c2[d] != c3[d] && c3[d] != c1[d]))
			return false;
	}
	return true;
}

void DFS(int cur, int depth)
{
	if (depth == 3) {
		if (chk(cards[tmp[0]], cards[tmp[1]], cards[tmp[2]]))
			possible_list.push_back(tmp);
		return;
	}

	for (int i = cur; i < num; i++) {
		tmp.push_back(i);
		DFS(i + 1, depth + 1);
		tmp.pop_back();
	}
}

int main()
{
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> num;
		for (int n = 0; n < num; n++) {
			cin >> card;
			cards.push_back(card);
		}

		DFS(0, 0);

		if (!possible_list.empty()) {
			dp[0] = 1;
			vector<int> c = possible_list[0];

			for (int i = 1; i < possible_list.size(); i++) {
				bool flag = true;
				for (int j = 0; j < 9; j++) {
					if (c[j / 3] == possible_list[i][j % 3]) {
						flag = false;
					}
				}
				if (!flag)
					dp[i] = dp[i - 1];
				else {

				}
			}
		}
		cout << '#' << t << ' ' << dp[num - 1] << endl;

		cards.clear();
		possible_list.clear();
	}
}