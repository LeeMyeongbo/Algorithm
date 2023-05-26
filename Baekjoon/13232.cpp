#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int order[5001], cnt, ans;
bool complete[5001];
vector<int> graph[5001];
stack<int> s;

int getSCC(int cur)
{
    int p = order[cur] = ++cnt;
    s.push(cur);

    for (int& to : graph[cur])
    {
        if (!order[to])
            p = min(p, getSCC(to));
        else if (!complete[to])
            p = min(p, order[to]);
    }

    if (p == order[cur])
    {
        register int size = 0;
        while (!s.empty())
        {
            register int v = s.top();
            s.pop();

            complete[v] = true;
            ++size;

            if (p == order[v])
                break;
        }

        ans = max(ans, size);
    }

    return p;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    register int D, L, x, y;
    cin >> D >> L;

    while (L--)
    {
        cin >> x >> y;
        graph[x].emplace_back(y);
    }

    for (register int v = 1; v <= D; ++v)
        if (!complete[v])
            getSCC(v);

    cout << ans;

    return 0;
}
