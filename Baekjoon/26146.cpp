#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> graph[200001];
stack<int> s;
int sccNum, cnt, order[200001];
bool complete[200001];

int findSCC(int cur)
{
    order[cur] = ++cnt;
    register int p = order[cur];
    s.push(cur);

    for (int& v : graph[cur])
    {
        if (!order[v])
            p = min(p, findSCC(v));
        else if (!complete[v])
            p = min(p, order[v]);
    }

    if (p == order[cur])
    {
        ++sccNum;
        while (!s.empty())
        {
            register int v = s.top();
            s.pop();

            complete[v] = true;

            if (p == order[v])
                break;
        }
    }

    return p;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    register int N, M, v, w;
    cin >> N >> M;

    while (M--)
    {
        cin >> v >> w;
        graph[v].push_back(w);
    }

    for (register int v = 1; v <= N; v++)
        if (!complete[v])
            findSCC(v);

    if (sccNum == 1)
        cout << "Yes";
    else
        cout << "No";

    return 0;
}
