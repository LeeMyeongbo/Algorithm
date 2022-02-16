#include <iostream>
using namespace std;

int N, arr[1000], Ans;

int main(int argc, char** argv)
{   
    for (int test_case = 1; test_case <= 10; ++test_case) {
        cin >> N;
        for (int i = 0; i < N; i++)
            cin >> arr[i];
        
        for (int i = 2; i < N - 2; i++) {
            int M = max(max(arr[i - 2], arr[i - 1]), max(arr[i + 1], arr[i + 2]));
            if (M < arr[i])
                Ans += arr[i] - M;
        }

        cout << '#' << test_case << ' ' << Ans << endl;
        Ans = 0;
    }
    return 0;
}
