#include <iostream>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define MAX 11
using namespace std;

int N, X, Y, depth[2002], parent[2002][MAX], info[4004], cur, index;
string binary;

int LCA(int x, int y)
{
	for (int j = 1; j < MAX; j++)
		for (int i = 1; i <= N; i++)
			parent[i][j] = parent[parent[i][j - 1]][j - 1];

	if (depth[x] < depth[y])
		swap(x, y);
	
	int gap = depth[x] - depth[y];
	for (int i = 0; gap; i++) {
		if (gap % 2)
			x = parent[x][i];
		gap /= 2;
	}
	if (x == y)
		return x;

	for(int i = MAX - 1; i >= 0; i--)
		if (parent[x][i] != parent[y][i]) {
			x = parent[x][i];
			y = parent[y][i];
		}

	return parent[x][0];
}

int main()
{
	FAST;
	cin >> N >> binary >> X >> Y;				// 항상 문제를 잘 읽자!

	for (int i = 0; i < binary.length(); i++) {
		if (binary[i] == '0') {
			parent[++index][0] = cur;
			depth[index] = depth[cur] + 1;
			info[i] = index;
			cur = index;
		}
		else {
			info[i] = cur;
			cur = parent[cur][0];
		} 
	}
	int cut = LCA(info[X - 1], info[Y - 1]);	// 이진 표현에서 X번째 정점이랑 Y번째 정점이라 했으므로

	for (int i = 0; i < binary.length(); i++) {
		if (info[i] == cut) {
			if (binary[i] == '0')
				cout << i + 1 << " ";
			if (binary[i] == '1')
				cout << i + 1;
		}
	}

	return 0;
}