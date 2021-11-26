#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define MAX 30
using namespace std;

int N, M, n1, n2, order, seq[2 * MAX + 1], scc_num, scc_index[2 * MAX + 1];
bool complete[2 * MAX + 1];
char h_w1, h_w2;
vector<int> graph[2 * MAX + 1];		// h�� ��쿡�� MAX���� ũ�� w�� ��쿡�� MAX���� ����
stack<int> s;

int dfs(int cur)				// ���� �������� ������ ��ҳ��� SCC�� ������
{
	seq[cur] = ++order;
	int par = order;
	s.push(cur);

	for (int& i : graph[cur]) {
		if (!seq[i])
			par = min(par, dfs(i));
		else if (!complete[i])
			par = min(par, seq[i]);
	}
	if (par == seq[cur]) {
		scc_num++;
		while (!s.empty()) {
			int v = s.top();
			s.pop();

			complete[v] = true;
			scc_index[v] = scc_num;
			if (v == cur)
				break;
		}
	}
	return par;
}

bool chk()			// -x�� x�� ���� scc�� ���ϴ��� üũ (���ϸ� ����x)
{
	for (int i = 1; i <= N; i++)
		if (scc_index[MAX - i] && scc_index[MAX + i] && scc_index[MAX - i] == scc_index[MAX + i])
			return false;
	return true;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	while (1) {
		cin >> N >> M;
		if (!N && !M)
			return 0;

		for (int i = 0; i < M; i++) {			// ���⼭ �����ϸ� �ȵ� �� : ö���̿� �����̵� �ҷ� ������ �� ����!
			cin >> n1 >> h_w1 >> n2 >> h_w2;	// �Է����� �־����� ���� ���� + 1�� �ϰ� �׷��� ���� (0->1, 1->2, ...  (n-1)->n)
			n1++, n2++;
			if (h_w1 == 'w')
				n1 *= -1;
			if (h_w2 == 'w')
				n2 *= -1;
			graph[MAX + n1].push_back(MAX - n2);	// �ҷ����� ���� ������ �ȵǹǷ�
			graph[MAX + n2].push_back(MAX - n1);
		}
		graph[MAX - 1].push_back(MAX + 1);		// ö���̸� ������ �̴´� ���� (1 �� 1) (�׻� �̰� ���� �� ������ �̷��� �ϴ� �� ���!)

		for (int i = MAX - N; i <= MAX + N; i++)
			if (i != MAX && !complete[i])
				dfs(i);

		if (chk()) {
			for (int i = 2; i <= N; i++) {		// ������ +x�� scc ��ȣ�� -x���� Ŭ ��� x��°�� false(='w')�� ó���ϴ� �� ���� (ö���� ��)
				cout << i - 1;
				scc_index[MAX - i] < scc_index[MAX + i] ? cout << "h " : cout << "w ";		// ������ �� : ö���̰� ���� ���� �ݴ�� ó��
			}
			cout << "\n";
		}
		else
			cout << "bad luck\n";

		order = scc_num = 0;
		fill(seq, seq + 2 * MAX + 1, 0);
		fill(scc_index, scc_index + 2 * MAX + 1, 0);
		fill(complete, complete + 2 * MAX + 1, false);
		for (int i = MAX - N; i <= MAX + N; i++)
			graph[i].clear();
	}
}