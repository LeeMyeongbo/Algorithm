#include <iostream>
#include <list>
using namespace std;

int T, N;
list<int> dp[251];

void getAns()
{
    dp[1].push_back(1);
    dp[2].push_back(3);

    for (int i = 3; i <= 250; i++) {
        list<int> mid, tmp1(dp[i - 2]), tmp2(dp[i - 1]);
        int carry = 0;

        while (!tmp1.empty()) {
            int n = tmp1.back();
            tmp1.pop_back();
            
            int num = n + n + carry;
            if (num > 9) {
                num -= 10;
                carry = 1;
            }
            else
                carry = 0;
            mid.emplace_front(num);
        }
        if (carry)
            mid.emplace_front(carry);

        carry = 0;
        while (!tmp2.empty() && !mid.empty()) {
            int n1 = tmp2.back();
            tmp2.pop_back();
            int n2 = mid.back();
            mid.pop_back();

            int num = n1 + n2 + carry;
            if (num > 9) {
                num -= 10;
                carry = 1;
            }
            else
                carry = 0;
            dp[i].emplace_front(num);
        }

        while (!tmp2.empty()) {
            int n = tmp2.back();
            tmp2.pop_back();

            int num = n + carry;
            if (num > 9) {
                num -= 10;
                carry = 1;
            }
            else
                carry = 0;
            dp[i].emplace_front(num);
        }

        while (!mid.empty()) {
            int n = mid.back();
            mid.pop_back();

            int num = n + carry;
            if (num > 9) {
                num -= 10;
                carry = 1;
            }
            else
                carry = 0;
            dp[i].emplace_front(num);
        }

        if (carry)
            dp[i].emplace_front(carry);
    }
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;
    getAns();

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N;

        cout << '#' << test_case << ' ';
        for (int i : dp[N])
            cout << i;
        cout << '\n';
    }
    return 0;
}
