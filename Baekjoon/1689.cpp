#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

pair<int, int> segment[1000000];
int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    register int N, ans = 1;
    cin >> N;

    for (register int i = 0; i < N; i++)
        cin >> segment[i].first >> segment[i].second;
    
    sort(segment, segment + N);

    priority_queue<int, vector<int>, greater<int>> pq;
    pq.push(segment[0].second);

    for (register int i = 1; i < N; i++)
    {
        while (!pq.empty() && pq.top() <= segment[i].first)
            pq.pop();

        pq.push(segment[i].second);
        
        ans = max(ans, (int)pq.size());
    }

    cout << ans;

    return 0;
}
