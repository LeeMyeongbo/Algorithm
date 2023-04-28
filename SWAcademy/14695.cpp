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

        cout << '#' << test_case << ' ';

        register bool possible = true;
        register unsigned int n;

        for (n = 2; n < N; n++)     // 2번째 좌표부터 살피면서 0번째와 1번째 좌표를 잇는 직선 상에 있지 않은 좌표가 나올 때까지 반복
        {
            register long long m1, m2, m3;
            if (x[0] == x[1] && y[0] == y[1])           // z축과 평행한 직선일 경우
            {
                if (x[n] != x[0] || y[n] != y[0])
                    break;
            }
            else if (y[0] == y[1] && z[0] == z[1])      // x축과 평행한 직선일 경우
            {
                if (y[n] != y[0] || z[n] != z[0])
                    break;
            }
            else if (z[0] == z[1] && x[0] == x[1])      // y축과 평행한 직선일 경우
            {
                if (z[n] != z[0] || x[n] != x[0])
                    break;
            }
            else if (x[0] == x[1])                      // yz평면과 평행한 직선일 경우
            {
                m1 = (z[1] - z[0]) * (y[n] - y[0]);
                m2 = (y[1] - y[0]) * (z[n] - z[0]);
                if (x[n] != x[0] || m1 != m2)
                    break;
            }
            else if (y[0] == y[1])                      // zx평면과 평행한 직선일 경우
            {
                m1 = (z[1] - z[0]) * (x[n] - x[0]);
                m2 = (x[1] - x[0]) * (z[n] - z[0]);
                if (y[n] != y[0] || m1 != m2)
                    break;
            }
            else if (z[0] == z[1])                      // xy평면과 평행한 직선일 경우
            {
                m1 = (y[1] - y[0]) * (x[n] - x[0]);
                m2 = (x[1] - x[0]) * (y[n] - y[0]);
                if (z[n] != z[0] || m1 != m2)
                    break;
            }
            else
            {
                m1 = (y[1] - y[0]) * (z[1] - z[0]) * (x[n] - x[0]);
                m2 = (z[1] - z[0]) * (x[1] - x[0]) * (y[n] - y[0]);
                m3 = (x[1] - x[0]) * (y[1] - y[0]) * (z[n] - z[0]);
                if (m1 != m2 || m2 != m3)
                    break;
            }
        }

        if (N > 3)                                      // 좌표가 4개 이상일 때 같은 직선 상에 있지 않은 n번째 좌표부터 진행
        {
            register long long a = y[0]*(z[1] - z[n]) + y[1]*(z[n] - z[0]) + y[n]*(z[0] - z[1]);
            register long long b = z[0]*(x[1] - x[n]) + z[1]*(x[n] - x[0]) + z[n]*(x[0] - x[1]);
            register long long c = x[0]*(y[1] - y[n]) + x[1]*(y[n] - y[0]) + x[n]*(y[0] - y[1]);
            register long long d = -x[0]*(y[1]*z[n] - y[n]*z[1]) - x[1]*(y[n]*z[0] - y[0]*z[n]) - x[n]*(y[0]*z[1] - y[1]*z[0]);


            for (register unsigned int i = n + 1; i < N; i++)   // n+1번째 좌표부터 살피면서 0번, 1번, n번 좌표평면 상에 있는지 확인
                if (a * x[i] + b * y[i] + c * z[i] + d)
                {
                    possible = false;
                    break;
                }
        }

        possible ? cout << "TAK\n" : cout << "NIE\n";
    }

    return 0;
}
