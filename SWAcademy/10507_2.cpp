#include <iostream>
#define MAX 1000000
using namespace std;

int T, n, p, study[MAX + 2], day;

int solve()                             // 투포인터 이용하면 더 간단
{
    int left = -1, right = 0, ans = 0, sum = study[right];
    
    while (right <= MAX) {
        if (sum + p >= right - left) {
            ans = max(ans, right - left);
            sum += study[++right];
        }
        else
            sum -= study[++left];
    }

    return ans;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> n >> p;
        for (int i = 0; i < n; i++) {
            cin >> day;
            study[day]++;
        }

        cout << '#' << test_case << ' ' << solve() << '\n';
        fill(study, study + MAX + 2, 0);
    }

    return 0;
}
