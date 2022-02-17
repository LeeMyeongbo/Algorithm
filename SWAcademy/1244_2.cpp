#include <iostream>
#include <string>
using namespace std;

int T, change, Max;
string nums;

void dfs(int depth, int index)
{
    if (depth == change) {
        Max = max(Max, stoi(nums));
        return;
    }

    int len = nums.length();
    for (int first = index; first < len - 1; first++) {
        for (int second = first + 1; second < len; second++) {
            swap(nums[first], nums[second]);
            dfs(depth + 1, first);
            swap(nums[first], nums[second]);
        }
    }
}

int main(int argc, char** argv)
{
    cin >> T;
    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> nums >> change;
        int len = nums.length();
        
        if (len < 2)
            Max = stoi(nums);       // 숫자판 길이 1일 때 예외처리 (굳이 할 필요는 없을듯함...)
        else {                      // 꼭 교환 횟수대로 교환할 필요 없이 숫자판 길이-1 내지 숫자판 길이-2 정도만 교환해도 됨        
            if (change > len)       // 교환 횟수와 길이가 모두 짝수거나 홀수면 len-2만큼, 아니면 len-1만큼 교환
                change = (change & 1) == (len & 1) ? len - 2 : len - 1;
            dfs(0, 0);
        }
        cout << '#' << test_case << ' ' << Max << endl;
        Max = 0;
    }
    return 0;
}
