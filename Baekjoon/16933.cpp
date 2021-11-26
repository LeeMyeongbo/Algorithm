#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
using namespace std;				// �� ���� �� ����!

struct Node {
	int R, C, sum, broken;
	bool is_day;					// true��� ��, false��� ��
};
int N, M, K;
char map[1001][1001];
bool visited[11][1000][1000];		// �μ� �� ������ ���� �湮 üũ ���� �� �� �ֵ��� �ϱ�! (0���� 10�����Ƿ� 11�� ��� ��!)
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };
queue<Node> q;

int Solve()
{
	q.push({ 0, 0, 1, 0, true });	// �� ó���� [0][0]���� �湮�� ĭ ���� 1, �μ� �� ���� 0, ���� ���·� ���
	visited[0][0][0] = true;
	while (!q.empty()) {
		Node node = q.front();
		q.pop();

		if (node.R == N - 1 && node.C == M - 1)									// �������� �����ϸ� �ٷ� �ִ� ��� ����
			return node.sum;
		for (int i = 0; i < 4; i++) {											// ������������ �����̸� üũ
			int R = node.R + dr[i];
			int C = node.C + dc[i];
			if (R >= 0 && R < N && C >= 0 && C < M) {							// �̵��� ���� �� ���� ���� ���� ���
				if (map[R][C] == '0' && !visited[node.broken][R][C]) {			// �̵��� ���� �湮�� �� ���� ��ĭ�� ���
					visited[node.broken][R][C] = true;							// broken�� �״��, �湮�� ĭ ���� + 1, ������ȯ
					q.push({ R, C, node.sum + 1, node.broken, !node.is_day });
				}
				// �̵��� ���� �湮�� �� ���� ���̸鼭 ���� �μ� �� �ִ� Ƚ���� �����ִ� ���
				else if (map[R][C] == '1' && node.broken + 1 <= K && !visited[node.broken + 1][R][C]) {
					if (node.is_day) {								// ���̸� broken�� +1�ϰ� 
						visited[node.broken + 1][R][C] = true;
						q.push({ R, C, node.sum + 1, node.broken + 1, !node.is_day });
					}
					else											// ���̶�� �μ� �� �����Ƿ� �̵� x,�湮�� ĭ ������ +1, ������ȯ
						q.push({ node.R, node.C, node.sum + 1, node.broken, !node.is_day });
				}
			}
		}
	}
	return -1;
}

int main()
{
	if (!scanf("%d %d %d", &N, &M, &K))
		return 1;
	for (int i = 0; i < N; i++)
		if (!scanf("%s", map[i]))
			return 1;
	printf("%d\n", Solve());
	return 0;
}