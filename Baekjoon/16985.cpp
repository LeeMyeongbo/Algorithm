#include <iostream>
#include <cstring>
#include <queue>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define VAL 5
using namespace std;

struct Node {
	int l, r, c, move;							// 각각 층, 행, 열, 움직인 횟수
};
int map[VAL][VAL][VAL], src[VAL][VAL][VAL], Ans = -1;
const int dl[] = { 0, 0, 0, 0, 1, -1 }, dr[] = { 0, 0, 1, -1, 0, 0 }, dc[] = { 1, -1, 0, 0, 0, 0 };

bool Rotate(int layer)							// (VAL - 1 - j, i)에 있던 것이 (i, j)로 이동
{
	bool is_Same = true;
	int tmp[VAL][VAL], tmp2[VAL][VAL];
	memcpy(tmp2, map[layer], sizeof(tmp2));

	for (int i = 0; i < VAL; i++)
		for (int j = 0; j < VAL; j++)
			tmp[i][j] = map[layer][VAL - j - 1][i];
	
	for (int i = 0; i < VAL; i++)
		for (int j = 0; j < VAL; j++) {
			map[layer][i][j] = tmp[i][j];
			if (tmp[i][j] != tmp2[i][j])
				is_Same = false;
		}
	return is_Same;
}

int BFS()										
{
	if (!map[0][0][0])							// 어차피 회전하므로 (0, 0, 0)에서 (4, 4, 4)로 가는 것만 확인해도 무방
		return -1;

	queue<Node> q;
	bool visited[VAL][VAL][VAL] = { false, };
	q.push({ 0, 0, 0, 0 });
	visited[0][0][0] = true;

	while (!q.empty()) {
		Node node = q.front();
		q.pop();

		if (node.l == VAL - 1 && node.r == VAL - 1 && node.c == VAL - 1)
			return node.move;

		for (int d = 0; d < 6; d++) {
			int L = node.l + dl[d];
			int R = node.r + dr[d];
			int C = node.c + dc[d];

			if (L >= 0 && L < VAL && R >= 0 && R < VAL && C >= 0 && C < VAL && map[L][R][C] && !visited[L][R][C]) {
				q.push({ L, R, C, node.move + 1 });
				visited[L][R][C] = true;
			}
		}
	}
	return -1;
}

void DFS(int layer)
{
	if (layer == VAL) {
		int p = BFS();
		Ans = p != -1 ? Ans != -1 ? min(Ans, p) : p : Ans;
		return;
	}
	for (int r = 1; r <= 4; r++) {
		DFS(layer + 1);
		if (Rotate(layer))					// 현재 층의 회전한 모양이 회전하기 전이랑 똑같으면 현재 층 종료 (가지치기)
			return;
	}
}

void Permut(int depth)
{
	static int seq[VAL];
	static bool visit[VAL] = { false, };

	if (depth == VAL) {
		for (int l = 0; l < VAL; l++)
			memcpy(map[l], src[seq[l]], sizeof(map[l]));

		DFS(0);
		return;
	}
	for (int i = 0; i < VAL; i++)
		if (!visit[i]) {
			visit[i] = true;
			seq[depth] = i;
			Permut(depth + 1);
			visit[i] = false;
		}
}

int main()
{
	FAST;
	for (int i = 0; i < VAL; i++)
		for (int j = 0; j < VAL; j++)
			for (int k = 0; k < VAL; k++)
				cin >> src[i][j][k];

	Permut(0);
	cout << Ans;
	return 0;
}