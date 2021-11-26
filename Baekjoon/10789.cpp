#include <iostream>
#include <queue>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

struct Node {
	int r, c, move, index;		// move : �Է� Ƚ��, index : ���� �Է��Ϸ��� �ؽ�Ʈ�� index
};
queue<Node> q;
const int dr[] = { 0, 0, 1, -1 }, dc[] = { 1, -1, 0, 0 };	// ��-��-��-�� ����
int r, c, visited[10001][50][50], ans;
char map[50][51];
string input;
pair<int, int> go[4][50][50];	// Ű���� ���� �� ��ġ���� �� �� �� �� ������ �������� �� ��� ��ġ�� ���� �Ǵ��� ���� (���� ����� (-1, -1))

int BFS()
{
	q.push({ 0, 0, 0, 0 });
	while (!q.empty()) {
		Node node = q.front();
		q.pop();
		// �ؽ�Ʈ ��� �Է��ϰ� �� �ڿ� ����Ű�� �������� ���
		if (node.index == (int)input.length() && map[node.r][node.c] == '*') {
			if (!ans)
				ans = node.move + 1;
			ans = min(ans, node.move + 1);
			continue;
		}
		// �Է��Ϸ��� ���ĺ��� Ű�� �������� ��� select & ���� ���� �Է��ؾ� �ϹǷ� index + 1�ϰ� �Է� Ƚ�� ����, ť ����
		else if (node.index < (int)input.length() && map[node.r][node.c] == input[node.index]) {
			q.push({ node.r, node.c, node.move + 1, node.index + 1 });
			visited[node.index + 1][node.r][node.c] = node.move + 1;
			continue;
		}
		// �� �� �� �� 4�������� ���Ǹ� �� �� �ִ� ��ġ�� ���Ͽ� �Է� Ƚ�� ����, ť ����
		for (int d = 0; d < 4; d++) {
			int R = go[d][node.r][node.c].first;
			int C = go[d][node.r][node.c].second;
			if (R != -1 && (!visited[node.index][R][C] || visited[node.index][R][C] > node.move + 1)) {
				q.push({ R, C, node.move + 1, node.index });
				visited[node.index][R][C] = node.move + 1;
			}
		}
	}
	return ans;
}

int main()
{
	FAST;
	cin >> r >> c;
	for (int i = 0; i < r; i++)
		cin >> map[i];
	
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			for (int d = 0; d < 4; d++) {		// ���� [i][j] �������� �� �� �� �� 4�������� �������� �� ��� ��ġ�� ���� �Ǵ����� ����
				int R = i + dr[d];
				int C = j + dc[d];
				while (1) {
					if (R < 0 || R >= r || C < 0 || C >= c) {	// ���� ����� (-1, -1) ����
						go[d][i][j] = { -1, -1 };
						break;
					}
					else if (map[R][C] != map[i][j]) {			// ���� Ű�� ���ĺ��� �ٸ� ��ġ�� �����ϸ� �� ��ġ�� ���� ����
						go[d][i][j] = { R, C };
						break;
					}
					R += dr[d], C += dc[d];
				}
			}
		}
	}
	cin >> input;
	cout << BFS();

	return 0;
}