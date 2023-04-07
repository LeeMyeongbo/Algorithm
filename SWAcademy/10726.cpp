#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
        int N, M;
        bool on = true;

        cin >> N >> M;

        for (int n = 0; n < N; n++) 
        {
            if (M % 2 == 0)
            {
                on = false;
                cout << '#' << test_case << ' ' << "OFF\n";
                break;
            }
            M /= 2;
        }

        if (on)
            cout << '#' << test_case << ' ' << "ON\n";
	}
	return 0;
}