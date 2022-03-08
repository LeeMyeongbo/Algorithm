#include <iostream>
using namespace std;

int T, boundary[100000];
string B, S;

void getMaxBoundary()
{
    int len = 0;

    for (int i = 1; i < (int)S.length(); ) {
        if (S[i] == S[len])                 // 접두사 부분과 접미사 부분이 일치할 경우
            boundary[i++] = ++len;          // 접미사 끝 부분에 같은 부분의 길이 저장
        else {
            if (len)
                len = boundary[len - 1];
            else
                i++;
        }
    }
}

int KMP()
{
    int len = 0, cnt = 0;

    for (int i = 0; i < (int)B.length(); ) {
        if (B[i] == S[len]) {               // 글자가 일치할 경우
            i++, ++len;
            if (len == S.length()) {        // B에서 S를 찾았을 경우
                cnt++;
                len = boundary[len - 1];
            }
        }
        else {                              // 반대로 글자가 일치하지 않을 경우
            if (len)
                len = boundary[len - 1];    // 접미사 경계에 맞추어 S를 이동
            else
                i++;                        // S를 이동해도 탐색 실패하면 B에서 한 칸 이동
        }
    }

    return cnt;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> B >> S;

        getMaxBoundary();
        cout << '#' << test_case << ' ' << KMP() << "\n";

        fill(boundary, boundary + S.length(), 0);
    }
    return 0;
}
