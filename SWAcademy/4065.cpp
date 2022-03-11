#include <iostream>
using namespace std;

int T, lcs[1001][1001];
string dna1, dna2;

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> dna1 >> dna2;

        for (int r = 1; r <= dna1.length(); r++) {
            for (int c = 1; c <= dna2.length(); c++) {
                if (dna1[r - 1] == dna2[c - 1])
                    lcs[r][c] = lcs[r - 1][c - 1] + 1;              // 두 문자열의 글자가 같다면 ↘방향 숫자에 +1
                else
                    lcs[r][c] = max(lcs[r - 1][c], lcs[r][c - 1]);  // 같지 않다면 ←, ↑ 방향의 숫자 중 최댓값 저장

            }
        }

        cout << '#' << test_case << ' ' << lcs[dna1.length()][dna2.length()] << '\n';
        for (int i = 1; i <= dna1.length(); i++)
            fill(lcs[i], lcs[i] + dna2.length() + 1, 0);
    }
    return 0;
}
