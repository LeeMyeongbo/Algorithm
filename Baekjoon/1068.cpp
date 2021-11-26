#include <iostream>
#include <vector>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, parent, E, ans, root;
vector<int> tree[50];

void dfs(int cur)
{
	if (cur == E)
		return;

	if (tree[cur].empty())
		ans++;

	for (int i : tree[cur])
		dfs(i);
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> parent;
		if (parent != -1)
			tree[parent].push_back(i);
		else
			root = i;
	}
	cin >> E;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < tree[i].size(); j++)			// E로 향하는 간선 제거
			if (tree[i][j] == E)
				tree[i].erase(tree[i].begin() + j);
	dfs(root);

	cout << ans;
	return 0;
}