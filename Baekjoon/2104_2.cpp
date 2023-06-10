#include <iostream>
#include <stack>
using namespace std;

int N, A[100002];
long long sum[100002];

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N;

    stack<int> s;
    register long long ans = 0;

    for (register int i = 1; i <= N + 1; ++i)
    {
        if (i <= N)
        {
            cin >> A[i];
            sum[i] = sum[i - 1] + A[i];
        }
        while (!s.empty() && A[s.top()] > A[i])
        {
            long long h = A[s.top()];
            s.pop();

            int leftidx = s.empty() ? 0 : s.top();
            ans = max(ans, (sum[i - 1] - sum[leftidx]) * h);
        }
        s.emplace(i);
    }

    cout << ans;

    return 0;
}
