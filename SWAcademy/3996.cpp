#include <iostream>
using namespace std;

int T, ans;
pair<char, int> card[7];
string res[] = { "Top", "1 Pair", "2 Pair", "Triple", "Straight", "Flush", "Full House", "4 Card", "Straight Flush" };

void chk(int depth, int start)
{
    static int number[14];
    static char shape[5];

    if (depth == 5) {                   // 5장 뽑았을 시
        bool one_shape = true;
        if (!(shape[0] == shape[1] && shape[1] == shape[2] && shape[2] == shape[3] && shape[3] == shape[4]))
            one_shape = false;          // 5장 중 모양이 다른 게 있다면 모양 하나만 있는게 아님!
        if (one_shape)
            ans = max(ans, 5);          // 모두 같은 모양이면 flush

        for (int i = 1; i < 10; i++)
            if (number[i] && number[i + 1] && number[i + 2] && number[i + 3] && number[i + 4]) {
                ans = max(ans, 4);      // 숫자가 5개 연속으로 존재하면 straight
                if (one_shape)
                    ans = max(ans, 8);  // 모양까지 전부 같으면 straight flush
            }
        if (number[1] && number[10] && number[11] && number[12] && number[13]) {    // 1, 10, 11, 12, 13 뽑았을 경우 처리
            ans = max(ans, 4);
            if (one_shape)
                ans = max(ans, 8);
        }

        int p = 0, t = 0;
        for (int i = 1; i <= 13; i++) {
            if (number[i] == 2) {           // 같은 숫자가 2개 존재 시 1 pair
                p++;
                ans = max(ans, 1);
            }
            else if (number[i] == 3) {      // 같은 숫자가 3개 존재 시 triple
                t++;
                ans = max(ans, 3);
            }
            else if (number[i] == 4)        // 같은 숫자가 4개 존재 시 4 card
                ans = max(ans, 7);
        }
        if (p && t)
            ans = max(ans, 6);              // 1 pair와 triple 모두 존재 시 full house
        if (p > 1)
            ans = max(ans, 2);              // 1 pair가 2개 이상 존재하면 2 pair

        return;
    }

    for (int i = start + 1; i < 7; i++) {   // 7장 중 5장 뽑으며 진행
        number[card[i].second]++;
        shape[depth] = card[i].first;
        chk(depth + 1, i);
        number[card[i].second]--;
        shape[depth] = 0;
    }
}

int main(int argc, char** argv)
{
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        for (int i = 0; i < 7; i++)
            cin >> card[i].first >> card[i].second;

        chk(0, -1);
        cout << '#' << test_case << ' ' << res[ans] << '\n';
        ans = 0;
    }
    return 0;
}
