#include <iostream>
//#include <fstream>
#include <vector>
#include <map>
using namespace std;

int T, N, M;
char board[50][101];
map<string, int> Map;

int solve()
{
    for (int r = 0; r < N; r++) {
        vector<int> codes;
        for (int c = M - 1; c >= 0; ) {
            if (board[r][c] != '1' || !(board[r][c] == board[r + 1][c] && board[r][c] == board[r + 2][c] 
                && board[r][c] == board[r + 3][c] && board[r][c] == board[r + 4][c]))
                c--;                                    // 1로 끝나지 않거나 세로로 최소 5칸이 같지 않다면 pass!
            else {
                string str = "";
                for (int i = c - 6; i <= c; i++)
                    str.push_back(board[r][i]);
                if (Map.find(str) != Map.end())
                    codes.push_back(Map[str]);
                c -= 7;
            }
        }
        if (codes.size() == 8) {
            if (((codes[1] + codes[3] + codes[5] + codes[7]) * 3 + codes[0] + codes[2] + codes[4] + codes[6]) % 10 == 0)
                return codes[0] + codes[1] + codes[2] + codes[3] + codes[4] + codes[5] + codes[6] + codes[7];
        }
    }
    return 0;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    //ifstream fin;
    //fin.open("C:/Users/myeon/Downloads/input.txt");

    Map["0001101"] = 0;
    Map["0011001"] = 1;
    Map["0010011"] = 2;
    Map["0111101"] = 3;
    Map["0100011"] = 4;
    Map["0110001"] = 5;
    Map["0101111"] = 6;
    Map["0111011"] = 7;
    Map["0110111"] = 8;
    Map["0001011"] = 9;

    //fin >> T;
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        //fin >> N >> M;
        cin >> N >> M;
        for (int r = 0; r < N; r++)
            cin >> board[r];
            //fin >> board[r];

        cout << '#' << test_case << ' ' << solve() << "\n";
    }
    return 0;
}
