#include <iostream>
using namespace std;

int T, N, arr[100000], s[100001];
char ans[200001];

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N;
        for (int i = 0; i < N; i++)
            cin >> arr[i];
        
        int start = 1, head = 0, ans_idx = 0;

        for (int i = 0; i < N; i++) {
            if (arr[i] >= start) {
                s[head++] = start++;
                ans[ans_idx++] = '+';
                i--;
            }
            else if (head > 0 && s[head - 1] == arr[i]) {
                --head;
                ans[ans_idx++] = '-';
            }
            else
                break;
        }

        cout << '#' << test_case << ' ';
        if (ans_idx == N * 2)
            for (int i = 0; i < ans_idx; i++)
                cout << ans[i];
        else
            cout << "NO";
        cout << '\n';
    }
    return 0;
}
