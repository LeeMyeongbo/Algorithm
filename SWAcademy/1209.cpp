#include <iostream>
#define MIN -(1 << 31)
using namespace std;

int n, arr[100][100], Ans = MIN;

int main(int argc, char** argv)
{
    for (int test_case = 1; test_case <= 10; ++test_case) {
        cin >> n;
        for (int i = 0; i < 100; i++)
            for (int j = 0; j < 100; j++)
                cin >> arr[i][j];

        for (int i = 0; i < 100; i++) {
            int sum = 0;
            for (int j = 0; j < 100; j++)
                sum += arr[i][j];
            Ans = max(Ans, sum);
        }

        for (int j = 0; j < 100; j++) {
            int sum = 0;
            for (int i = 0; i < 100; i++)
                sum += arr[i][j];
            Ans = max(Ans, sum);
        }

        int sum = 0;
        for (int i = 0; i < 100; i++)
            sum += arr[i][i];
        Ans = max(Ans, sum);

        sum = 0;
        for (int i = 0; i < 100; i++)
            sum += arr[99 - i][i];
        Ans = max(Ans, sum);

        cout << '#' << test_case << ' ' << Ans << endl;
        Ans = MIN;
    }
    return 0;
}
