#include <iostream>
#include <queue>
using namespace std;

struct Node {
	int r, c, rotated_R, rotated_C, num;
	char map[7][8];
} node;
priority_queue<Node> q;
int M, N;
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };	// 동 서 남 북 순
const char gate[] = { 'D', 'D', 'C', 'C' };
bool visited[7][7][1 << 7][1 << 7];

bool operator<(Node n1, Node n2) 
{
	return n1.num > n2.num;
}

void rotate(Node& n) 
{
	for (int i = 0; i < N; i++) {
		if (n.map[i][n.c] == 'C')
			n.map[i][n.c] = 'D';
		else if (n.map[i][n.c] == 'D')
			n.map[i][n.c] = 'C';
	}
	for (int i = 0; i < M; i++) {
		if (n.map[n.r][i] == 'C')
			n.map[n.r][i] = 'D';
		else if (n.map[n.r][i] == 'D')
			n.map[n.r][i] = 'C';
	}
}

int BFS() 
{
	q.push(node);
	while (!q.empty()) {
		Node n = q.top();
		q.pop();
		
		if (n.r == N - 1 && n.c == M - 1)
			return n.num;

		for (int d = 0; d < 4; d++) {		// 현 위치에서 4방향으로 살피며 갈 수 있는 곳 탐색
			int R = n.r + dr[d];
			int C = n.c + dc[d];
			if (R >= 0 && R < N && C >= 0 && C < M && !visited[R][C][n.rotated_R][n.rotated_C]) {
				if ((n.map[n.r][n.c] == 'A' || n.map[n.r][n.c] == gate[d]) && (n.map[R][C] == 'A' || n.map[R][C] == gate[d])) {
					visited[R][C][n.rotated_R][n.rotated_C] = true;
					Node new_node = n;
					new_node.r = R, new_node.c = C, new_node.num++;
					q.push(new_node);
				}
			}
		}
											// 현 위치에서 돌릴 수 있을 때 회전
		if (!visited[n.r][n.c][n.rotated_R | (1 << n.r)][n.rotated_C | (1 << n.c)]) {
			rotate(n);
			n.rotated_R = n.rotated_R | (1 << n.r);
			n.rotated_C = n.rotated_C | (1 << n.c);
			visited[n.r][n.c][n.rotated_R][n.rotated_C] = true;
			n.num++;
			q.push(n);
		}
	}
	return -1;
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		cin >> node.map[i];
	
	cout << BFS();
	return 0;
}