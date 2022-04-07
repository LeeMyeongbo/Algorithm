#include <iostream>
#include <string>
#include <vector>
#define INF 100000000
using namespace std;

int floyd[201][201];

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            floyd[i][j] = INF;
        floyd[i][i] = 0;
    }

    for (auto& f : fares) {
        floyd[f[0]][f[1]] = f[2];
        floyd[f[1]][f[0]] = f[2];
    }

    for (int pass = 1; pass <= n; pass++)
        for (int start = 1; start <= n; start++)
            for (int end = 1; end <= n; end++)
                floyd[start][end] = min(floyd[start][end], floyd[start][pass] + floyd[pass][end]);

    int answer = INF;

    for (int p = 1; p <= n; p++) {          // s에서 p까지 같이 가고 p에서 각자 헤어져서 a, b로 가는 경우의 최단 거리 도출
        answer = min(answer, floyd[s][p] + floyd[p][a] + floyd[p][b]);
    }
    return answer;
}