#include <iostream>
#include <vector>
using namespace std;

vector<int> ans;

void dfs(int depth, int cur_depth, int cur, int sum, int arr[])
{
    if (depth == cur_depth)
    {
        if (sum == 0)
        {
            for (int i : ans)
                cout << i << ' ';
            cout << '\n';
        }
        return;
    }

    for (int i = cur; i < 10; i++)
    {
        ans.push_back(arr[i]);
        dfs(depth, cur_depth + 1, i + 1, sum + arr[i], arr);
        ans.pop_back();
    }
}

int main()
{
    int arr[10];
    for (int i = 0; i < 10; i++)
        cin >> arr[i];

    for (int depth = 1; depth <= 10; depth++)
        dfs(depth, 0, 0, 0, arr);

    return 0;
}