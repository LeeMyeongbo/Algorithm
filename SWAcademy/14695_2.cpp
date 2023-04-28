#include <iostream>
using namespace std;

long long x[100000], y[100000], z[100000];

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    register int T, N;
    cin >> T;

    for (register unsigned int test_case = 1; test_case <= T; ++test_case)
    {
        cin >> N;
        for (register unsigned int i = 0; i < N; i++)
            cin >> x[i] >> y[i] >> z[i];

        cout << '#' << test_case;

        if (N < 4) 
            cout << " TAK\n";
        else
        {
            register bool plane = false, possible = true;
            register long long a = 0, b = 0, c = 0, d = 0;
            for (register unsigned int n = 2; n < N; n++)
            {
                if (!plane)
                {
                    a = y[0] * (z[1] - z[n]) + y[1] * (z[n] - z[0]) + y[n] * (z[0] - z[1]);
                    b = z[0] * (x[1] - x[n]) + z[1] * (x[n] - x[0]) + z[n] * (x[0] - x[1]);
                    c = x[0] * (y[1] - y[n]) + x[1] * (y[n] - y[0]) + x[n] * (y[0] - y[1]);
                    d = x[0] * (y[1] * z[n] - y[n] * z[1]) + x[1] * (y[n] * z[0] - y[0] * z[n]) + x[n] * (y[0] * z[1] - y[1] * z[0]);

                    if (a || b || c || d)   // a ~ d 중 0이 아닌 것이 있다면 같은 직선 상이 아닌 평면 상에 존재하는 세 점 발견한 것
                        plane = true;
                }
                else                        // 평면 찾았으면 나머지 점들이 해당 평면 위에 있는지 조사하면 됨
                    if (a * x[n] + b * y[n] + c * z[n] != d)
                    {
                        possible = false;
                        break;
                    }
            }   
            possible ? cout << " TAK\n" : cout << " NIE\n";
        }
    }

    return 0;
}
