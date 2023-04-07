#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;
    long long N;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
        cin >> N;
        bool chk[10] = {false, };

        for (int re = 1; ; re++)
        {
            long long xN = N * re;
            bool complete = true;

            while (xN) 
            {
                chk[xN % 10] = true;
                xN /= 10;
            }
            for (int i = 0; i < 10; i++) 
            {
                if (!chk[i]) 
                {
                    complete = false;
                    break;
                }
            }
            if (complete)
            {
                printf("#%d %ld\n", test_case, N * re);
                break;
            }
        }
	}
	return 0;
}