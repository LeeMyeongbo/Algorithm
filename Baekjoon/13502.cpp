#include <iostream>
#include <fstream>
using namespace std;

struct Trie {
    Trie* trie[26];
    bool is_over, found;
};
Trie* head;
char map[5][6];
int ans;
const int dr[] = {-1, -1, 0, 1, 1, 1, 0, -1}, dc[] = {0, 1, 1, 1, 0, -1, -1, -1};
bool visited[5][5];

void insert(string& str)        // 트라이 형성
{
    Trie* t = head;
    for (char c : str) {
        if (!(t->trie[c - 'A']))
            t->trie[c - 'A'] = new Trie();
        t = t->trie[c - 'A'];
    }
    t->is_over = true;
}

void destroy(Trie* trie)        // 트라이 제거
{
    for (int c = 0; c < 26; c++)
        if (trie->trie[c])
            destroy(trie->trie[c]);

    delete trie;
}

void find(Trie* t, int r, int c)        // dfs 방식으로 찾으며 문자열을 찾을 때마다 개수 증가 + found 체크
{
    if (!t) return;
    
    if (t->is_over && !t->found) {
        ans++;
        t->found = true;
    }
    
    for (int d = 0; d < 8; d++) {
        int R = r + dr[d], C = c + dc[d];
        if (R >= 0 && R < 5 && C >= 0 && C < 5 && !visited[R][C]) {
            visited[R][C] = true;
            find(t->trie[map[R][C] - 'A'], R, C);
            visited[R][C] = false;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	ifstream fin;
    fin.open("C:/Users/myeon/Downloads/dict.txt");

    string str;
    head = new Trie();

    while (!fin.eof()) {
        fin >> str;
        insert(str);
    }

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            cin >> map[i][j];

    for (int r = 0; r < 5; r++)
        for (int c = 0; c < 5; c++)
            if (head->trie[map[r][c] - 'A']) {
                visited[r][c] = true;
                find(head->trie[map[r][c] - 'A'], r, c);
                visited[r][c] = false;
            }

    cout << ans;

    destroy(head);
    return 0;
}