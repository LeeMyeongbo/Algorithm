#include <iostream>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define MAX 1000000000
using namespace std;

int TC, N, M, W, S, E, T, map[501][501];
long long weight_sum[501];

bool Bellman()				// 시작점이 1번 정점이라 가정 (2번, 3번으로 둬도 됨. 니맘임 ㅇㅇ)
{
	fill(weight_sum, weight_sum + N + 1, MAX);
	weight_sum[1] = 0;		// 시작점은 0으로 하고 시작
												// edge relaxation 과정
	for (int i = 0; i < N - 1; i++)				// start와 end 사이 간선 존재 시 end 정점의 가중치 합 최솟값으로 갱신 => N - 1번 반복
		for (int start = 1; start <= N; start++)
			for (int end = 1; end <= N; end++)	
				if (map[start][end] != MAX && weight_sum[start] != MAX)
					weight_sum[end] = min(weight_sum[end], weight_sum[start] + map[start][end]);
	
	for(int start = 1; start <= N; start++)		// 마지막 N번째에 end 정점의 가중치 합 최소로 갱신해 봄
		for (int end = 1; end <= N; end++) 
        {
			if (map[start][end] != MAX) 
            {
				long long Min = min(weight_sum[end], weight_sum[start] + map[start][end]);
				if (Min != weight_sum[end])		// end 정점의 가중치 합 최솟값이 또 갱신될 경우 해당 end 정점은 사이클에 포함
					return true;
			}
		}

	return false;
}

int main()
{
	FAST;
	cin >> TC;
	for (int t = 1; t <= TC; t++) 
    {
		cin >> N >> M >> W;
		for (int i = 1; i <= N; i++)
			fill(map[i], map[i] + N + 1, MAX);

		for (int e = 0; e < M; e++) 
        {
			cin >> S >> E >> T;
			map[S][E] = min(map[S][E], T);
			map[E][S] = min(map[E][S], T);
		}

		for (int w = 0; w < W; w++) 
        {
			cin >> S >> E >> T;
			map[S][E] = -T;
		}

		if (Bellman())
			cout << "YES\n";
		else
			cout << "NO\n";
	}

	return 0;
}
