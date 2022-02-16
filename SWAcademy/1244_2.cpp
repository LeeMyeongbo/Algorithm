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
    for (int first = index; first < nums.length() - 1; first++) {
        for (int second = first + 1; second < nums.length(); second++) {
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
        if (change > nums.length()) {
            if ((change % 2 && nums.length() % 2) || (!(change % 2) && !(nums.length() % 2)))
                change = nums.length();
            else
                change = nums.length() + 1;
        }

        dfs(0, 0);
        cout << '#' << test_case << ' ' << Max << endl;
        Max = 0;
    }
    return 0;
}
