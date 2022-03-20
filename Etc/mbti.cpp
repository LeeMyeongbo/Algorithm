#include <iostream>
#include <set>
using namespace std;

int N, M, ans;
const int dr[] = { -1, -1, 0, 1, 1, 1, 0, -1 }, dc[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
char board[200][201];
set<string> mbti;
char personality[4][2] = { {'E', 'I'}, {'N', 'S'}, {'F', 'T'}, {'P', 'J'} };

void init(int depth)
{
    static string p;
    if (depth == 4) {
        mbti.insert(p);
        return;
    }
    for (int i = 0; i < 2; i++) {
        p.push_back(personality[depth][i]);
        init(depth + 1);
        p.pop_back();
    }
}

bool find(int r, int c, int d)
{
    string s = "";
    for (int i = 0; i < 4; i++) {
        int R = r + dr[d] * i;
        int C = c + dc[d] * i;
        if (R >= 0 && R < N && C >= 0 && C < M)
            s.push_back(board[R][C]);
        else
            return false;
    }
    if (mbti.count(s))
        return true;
    return false;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    init(0);
    cin >> N >> M;

    for (int i = 0; i < N; i++)
        cin >> board[i];
    
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            for (int d = 0; d < 8; d++) {
                if (find(r, c, d))
                    ans++;
            }
        }
    }

    cout << ans;
    return 0;
}
