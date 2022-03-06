#include <iostream>
using namespace std;

int T, len[1000000];
string S;

int solve()
{
    int l = 0;
    fill(len, len + S.length(), 0);

    for (int i = 1; i < S.length(); ) {     // kmp 통해 문자열 S의 각 자리마다 가장 긴 접두사/접미사 길이 저장
        if (S[i] == S[l])
            len[i++] = ++l;
        else {
            if (l)
                l = len[l - 1];
            else
                i++;
        }
    }
    int cur = len[S.length() - 1], i;       // 부분 문자열이 반복되면 어느 순간부터 1, 2, 3, ... 이렇게 저장됨

    for (i = S.length() - 1; cur; i--) {    // cur=0이 될 때까지 왼쪽으로 살피며 1씩 감소하는지 확인
        if (len[i] != cur)
            return 0;
        cur--;
    }

    if (S.length() % (i + 1) == 0)          // 나머지 남은 부분의 길이가 문자열 S 전체 길이의 약수이면 n제곱 성립
        return S.length() / (i + 1);

    return 1;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    while (true) {
        cin >> S;
        if (S == ".")
            return 0;

        cout << solve() << '\n';
    }
}
