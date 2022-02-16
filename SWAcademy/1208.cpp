#include <iostream>
#include <stack>
using namespace std;

int height[100], dump;

int main(int argc, char** argv)
{
    for (int test_case = 1; test_case <= 10; ++test_case) {
        cin >> dump;
        for (int i = 0; i < 100; i++)
            cin >> height[i];

        for (int i = 0; i < dump; i++) {
            int max_index = 0, min_index = 0;
            int Max = 0, Min = 101;

            for (int j = 0; j < 100; j++) {
                if (height[j] > Max) {
                    max_index = j;
                    Max = height[j];
                }
                if (height[j] < Min) {
                    min_index = j;
                    Min = height[j];
                }
            }
            if (Max - Min <= 1)
                break;
            height[max_index]--, height[min_index]++;
        }

        int M = 0, m = 101;
        for (int i = 0; i < 100; i++) {
            M = max(M, height[i]);
            m = min(m, height[i]);
        }

        cout << '#' << test_case << ' ' << M - m << endl;
    }
    return 0;
}
