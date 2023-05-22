#include <iostream>
#include <vector>
using namespace std;

int N, x, y, chk[1001], ans;		                // chk[i] : i번 정점의 깊이
vector<int> graph[1001];

void DFS(int prev, int cur, int depth)              // prev : 이전 정점, cur : 현재 정점, depth : 깊이
{
    chk[cur] = depth;

    for (int next : graph[cur]) 
    {
        if (ans)
            return;                                 // ans가 0이 아니면 이미 사이클 찾은 거

        if (chk[next])                              // 방문한 적이 있는데 
        {
            if (next != prev)                       // 이전에 방문한 정점이 아니라면 사이클!
            {
                ans = chk[cur] - chk[next] + 1;
                return;
            }
        }
        else
            DFS(cur, next, depth + 1);
    }
}

int main(int argc, char** argv)                     // 혹은 위상정렬을 활용해도 됨!!
{
	cin >> N;
	for (int i = 0; i < N; i++) 
    {
		cin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}

	DFS(0, 1, 1);

	cout << "사이클 길이 : " << ans << endl;
	return 0;
}
