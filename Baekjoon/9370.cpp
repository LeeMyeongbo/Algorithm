#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
#define MAX 2001
using namespace std;

priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
vector<pair<int, int>> graph[MAX];				// (����� ������, ���� ����) �÷� ����
int T, n, m, t, s, g, h, must;					// must : g, h ������ ����
int s_sum[MAX], g_sum[MAX], h_sum[MAX];			// s_sum : s����, g_sum : g����, h_sum : h���� ����Ͽ� �� �����α����� �ִ� �Ÿ� ����

void Dijkstra(int start_arr[], int start)
{
	memset(start_arr, -1, sizeof(int) * MAX);
	start_arr[start] = 0;
	q.push({ 0, start });
	while (!q.empty()) {
		int sum = q.top().first;
		int cur = q.top().second;
		q.pop();

		for (auto p : graph[cur]) {
			if (start_arr[p.first] == -1 || start_arr[p.first] > sum + p.second) {
				start_arr[p.first] = sum + p.second;
				q.push({ start_arr[p.first], p.first });
			}
		}
	}
}

vector<int> Solve(int dest[])
{
	vector<int> ans_list;
	Dijkstra(s_sum, s);
	Dijkstra(g_sum, g);
	Dijkstra(h_sum, h);						// s, g, h �� �����ηκ��� ��� �����α����� �ִ� �Ÿ� �����ؼ� ����

	// s���� g(h)������ �ִ� �Ÿ� + g-h ���� + h(g)���� ������������ �ִ� �Ÿ� = s���� ���������� �ִ� �Ÿ� => �� �������� ����!
	for (int i = 0; i < t; i++) {
		if (s_sum[g] + must + h_sum[dest[i]] == s_sum[dest[i]] || s_sum[h] + must + g_sum[dest[i]] == s_sum[dest[i]])
			ans_list.push_back(dest[i]);
	}
	sort(ans_list.begin(), ans_list.end());
	return ans_list;
}

int main()
{
	int a, b, d;
	if (!scanf("%d", &T))
		return 1;
	for (int test = 0; test < T; test++) {
		int dest[100] = { 0, };					// ���� ������ ����

		if (!scanf("%d %d %d %d %d %d", &n, &m, &t, &s, &g, &h))
			return 1;
		for (int i = 0; i < m; i++) {
			if (!scanf("%d %d %d", &a, &b, &d))
				return 1;
			graph[a].push_back({ b, d });
			graph[b].push_back({ a, d });
			if ((a == g && b == h) || (a == h && b == g))
				must = d;
		}
		for (int i = 0; i < t; i++)
			if (!scanf("%d", dest + i))
				return 1;

		vector<int> ans = Solve(dest);
		for (int i : ans)
			printf("%d ", i);
		printf("\n");

		for (int gr = 1; gr <= n; gr++)
			if (!graph[gr].empty())
				graph[gr].clear();
	}
	return 0;
}