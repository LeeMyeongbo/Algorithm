#include <iostream>
#include <string>
#include <set>
using namespace std;

int w, b, s[] = { 0, 0, 0, 1, 1, 2, 3, 5, 11 };
const int dr[] = { -1, 0, 1, 1, 1, 0, -1, -1 }, dc[] = { 1, 1, 1, 0, -1, -1, -1, 0 };
string word, found;
set<string> words, ans_list;
char board[4][5];
bool visited[4][4];

void dfs(int length, int r, int c) 
{
	visited[r][c] = true;
	found.push_back(board[r][c]);					// 1. 체크인

	if (words.count(found))
		ans_list.insert(found);						// 2. 목적지 확인 (단어 찾은거 맞는지 확인)

	if (length < 8) {
		for (int d = 0; d < 8; d++) {				// 3. 방문할 수 있는지 확인 + 순회
			int new_r = r + dr[d];
			int new_c = c + dc[d];
			if (new_r >= 0 && new_r < 4 && new_c >= 0 && new_c < 4 && !visited[new_r][new_c])		// 4. 가능??
				dfs(length + 1, new_r, new_c);		// 5. 가능하면 감
		}
	}
	found.pop_back();
	visited[r][c] = false;							// 6. 체크아웃
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> w;
	for (int i = 0; i < w; i++) {
		cin >> word;
		words.insert(word);
	}

	cin >> b;
	for (int i = 0; i < b; i++) {
		for (int j = 0; j < 4; j++)
			cin >> board[j];

		for (int r = 0; r < 4; r++)
			for (int c = 0; c < 4; c++)
				dfs(1, r, c);							// 4*4=16곳 모두 시작점으로 하여 dfs 탐색

		int score = 0, length = 0;
		string longest = "";

		for (auto iter = ans_list.begin(); iter != ans_list.end(); iter++) {
			score += s[iter->length()];

			if (length < (int)iter->length()) {			// 최대 길이 갱신될 경우
				length = iter->length();
				longest = *iter;
			}
		}

		cout << score << ' ' << longest << ' ' << ans_list.size() << "\n";
		ans_list.clear();
	}
	return 0;
}