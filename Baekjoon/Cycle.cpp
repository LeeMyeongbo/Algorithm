#include <iostream>
#include <vector>
using namespace std;

int N, x, y, chk[1001], ans;		                // chk[i] : i�� ������ ����
vector<int> graph[1001];

void DFS(int prev, int cur, int depth) {            // prev : ���� ����, cur : ���� ����, depth : ����
    chk[cur] = depth;

    for (int next : graph[cur]) {
        if (ans)
            return;                                 // ans�� 0�� �ƴϸ� �̹� ����Ŭ ã�� ��

        if (chk[next]) {                            // �湮�� ���� �ִµ� 
            if (next != prev) {                     // ������ �湮�� ������ �ƴ϶�� ����Ŭ!
                ans = chk[cur] - chk[next] + 1;
                return;
            }
        }
        else
            DFS(cur, next, depth + 1);
    }
}

int main(int argc, char** argv)                     // Ȥ�� ���������� Ȱ���ص� ��!!
{
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	DFS(0, 1, 1);

	cout << "����Ŭ ���� : " << ans << endl;
	return 0;
}