#include <iostream>
using namespace std;

int T, N, oper[4], num[12], operation[11], Max = -100000000, Min = 100000000;

void dfs(int depth)
{
    if (depth == N - 1) {
        int tmp = num[0];

        for (int i = 0; i < N - 1; i++) {   // 다 진행 했으면 순서대로 계산
            if (operation[i] == 1)
                tmp += num[i + 1];
            else if (operation[i] == 2)
                tmp -= num[i + 1];
            else if (operation[i] == 3)
                tmp *= num[i + 1];
            else
                tmp /= num[i + 1];
        }

        Max = max(Max, tmp);
        Min = min(Min, tmp);
        return;
    }

    for (int i = 0; i < 4; i++) {           // 각 연산자 자리마다 +, -, *, / 번갈아 가며 넣으면서 진행
        if (oper[i]) {
            oper[i]--;                      // 넣었으면 개수 1 줄이고 저장 (+는 1, -는 2, *는 3, /는 4)
            operation[depth] = i + 1;
            dfs(depth + 1);
            operation[depth] = 0;
            oper[i]++;
        }
    }
}

int main(int argc, char** argv)
{
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N;
        for (int i = 0; i < 4; i++)
            cin >> oper[i];

        for (int i = 0; i < N; i++)
            cin >> num[i];

        dfs(0);
        cout << '#' << test_case << ' ' << Max - Min << "\n";

        Max = -100000000, Min = 100000000;
    }
    return 0;
}
