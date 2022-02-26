#include <iostream>
using namespace std;

int T, N, idx[200001], Si;

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N;

        for (int n = 1; n <= N; n++) {      // Si번 편수에 해당하는 index에 현재 순서 저장
            cin >> Si;
            idx[Si] = n;
        }

        int Ans = 1;
        for (int i = 2; i <= N; i++)
            if (idx[i] < idx[i - 1])        // Si번 편수의 만화책이 나타나는 순서가 Si-1번 편수 만화책보다 앞선다면 +1
                Ans++;

        cout << '#' << test_case << ' ' << Ans << "\n";
    }
    return 0;
}
