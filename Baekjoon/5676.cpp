#include <iostream>
#include <vector>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

char query;
int N, M, X[100001], tree[400004], i, j;
vector<char> Ans;

int init(int index, int start, int end)
{
	if (start == end) {
		if (X[start] > 0)
			return tree[index] = 1;
		if (X[start] < 0)
			return tree[index] = -1;
		return tree[index] = 0;
	}
	return tree[index] = init(index * 2, start, (start + end) / 2) * init(index * 2 + 1, (start + end) / 2 + 1, end);
}

int update(int index, int start, int end)
{
	if (start > i || end < i)
		return tree[index];
	if (start == end) {
		X[start] = j;
		if (X[start] > 0)
			return tree[index] = 1;
		if (X[start] < 0)
			return tree[index] = -1;
		return tree[index] = 0;
	}
	return tree[index] = update(index * 2, start, (start + end) / 2) * update(index * 2 + 1, (start + end) / 2 + 1, end);
}

int find(int index, int start, int end)
{
	if (start > j || end < i)
		return 1;
	if (start >= i && end <= j)
		return tree[index];
	return find(index * 2, start, (start + end) / 2) * find(index * 2 + 1, (start + end) / 2 + 1, end);
}

int main()
{
	FAST;
	while (1) {
		cin >> N >> M;
		if (cin.eof())
			return 0;
		
		for (int a = 1; a <= N; a++)
			cin >> X[a];
		init(1, 1, N);

		for (int a = 0; a < M; a++) {
			cin >> query >> i >> j;
			if (query == 'C')
				update(1, 1, N);
			else {
				int ans = find(1, 1, N);
				if (ans > 0)
					Ans.push_back('+');
				else if (ans < 0)
					Ans.push_back('-');
				else
					Ans.push_back('0');
			}
		}
		for (char c : Ans)
			cout << c;
		cout << "\n";

		Ans.clear();
	}
}