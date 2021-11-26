#include <iostream>
#include <algorithm>
#define MAX 10000
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, map[100][100];

void Floyd()
{
	for(int pass = 0; pass < N; pass++)
		for(int s = 0; s < N; s++)
			for (int d = 0; d < N; d++)
				map[s][d] = min(map[s][d], map[s][pass] + map[pass][d]);
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] < MAX)
				cout << 1 << " ";
			else
				cout << 0 << " ";
		}
		cout << "\n";
	}
}

int main()
{
	FAST;
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++){
			cin >> map[i][j];
			if (!map[i][j])
				map[i][j] = MAX;
		}
	
	Floyd();
	return 0;
}