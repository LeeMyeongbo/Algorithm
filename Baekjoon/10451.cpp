#include <iostream>
#include <cstring>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int T, N, p[1001], ans;
bool visited[1001];

void dfs(int cur)
{
	if (!visited[p[cur]]) {
		visited[p[cur]] = true;
		dfs(p[cur]);
	}
	else
		ans++;
}

int main()
{
	FAST;
	cin >> T;
	for (int t = 0; t < T; t++) {
		cin >> N;
		for (int i = 1; i <= N; i++)
			cin >> p[i];

		for (int i = 1; i <= N; i++) {
			if (!visited[i]) {
				visited[i] = true;
				dfs(i);
			}
		}
		cout << ans << "\n";
		ans = 0;
		memset(visited, false, sizeof(visited));
		memset(p, 0, sizeof(p));
	}
	return 0;
}