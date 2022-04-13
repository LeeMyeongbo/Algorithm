#include <iostream>
#include <cmath>
using namespace std;

int T;
string bin, tri;
long long bin_, tri_;

long long solve()
{
    int bp = 0;
    long long tmp_bin = bin_, tmp_tri = tri_;

    for (int b = bin.length() - 1; b >= 0; b--) {
        int b_cur = bin[b] - '0';
        tmp_bin -= b_cur * (long long)pow(2, bp);           // 원래 수에서 해당 자리의 숫자를 0으로 바꿨을 때 값 구함

        int b_new_num = (b_cur + 1) % 2;
        tmp_bin += b_new_num * (long long)pow(2, bp);       // 그리고 그 자리를 다른 숫자로 바꾼 것의 값 도출

        int cp = 0;
        for (int c = tri.length() - 1; c >= 0; c--) {       // 3진수도 마찬가지로 진행
            int c_cur = tri[c] - '0';
            tmp_tri -= c_cur * (long long)pow(3, cp);

            for (int n = 1; n < 3; n++) {
                int c_new_num = (c_cur + n) % 3;
                if (tmp_tri + c_new_num * (long long)pow(3, cp) == tmp_bin)
                    return tmp_bin;
            }
            cp++;
            tmp_tri = tri_;
        }
        bp++;
        tmp_bin = bin_;
    }

    return 0;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (register int test_case = 1; test_case <= T; ++test_case) {
        cin >> bin >> tri;
        int i = 0;
        for (int b = bin.length() - 1; b >= 0; b--) {
            int cur = bin[b] - '0';
            bin_ += cur * (long long)pow(2, i++);
        }
        
        i = 0;
        for (int c = tri.length() - 1; c >= 0; c--) {
            int cur = tri[c] - '0';
            tri_ += cur * (long long)pow(3, i++);
        }
        
        cout << '#' << test_case << ' ' << solve() << '\n';
        bin_ = tri_ = 0;
    }

    return 0;
}
