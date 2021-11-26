#include <iostream>
#include <vector>
using namespace std;

int N, M, map[49][49], d[101], s[101], exploded[4];
const int dr[] = { 0, -1, 1, 0, 0 }, dc[] = { 0, 0, 0, -1, 1 };
vector<int> beads;

void Exploding()						// Ʋ�� ���� 1 : ���߷� ������ ��� ����� �� �ִ� ��쵵 ������ ����
{
	while (!beads.empty()) {
		int seq = 1, pre = beads[0];	// seq : �׷��� �̷�� ���� ����, pre : ���� ������ ����
		bool complete = true;

		for (int i = 1; i < (int)beads.size(); i++) {
			if (beads[i] == pre)
				seq++;					// �� ������ ���� �����̶� ���ڰ� ������ seq�� ����
			else {						// �� ������ ���� �����̶� ���ڰ� �� �޶����� ��
				if (seq > 3) {			// �׷��� �̷�� ������ 4�� �̻��� ��
					for (int j = i - seq; j < i; j++) {
						exploded[beads[j]]++;
						beads[j] = 0;
						complete = false;
					}
				}
				seq = 1;
				pre = beads[i];
			}
		}
		if (seq > 3) {					// Ʋ�� ���� 2 : �迭���� '����'�̷� ���� ������ ���������� �����ؾ� �ϴ� �� ����
			for (int j = (int)beads.size() - seq; j < (int)beads.size(); j++) {
				exploded[beads[j]]++;
				beads[j] = 0;
				complete = false;
			}
		}
		if (complete) 
			break;
		
		vector<int> tmp;
		for (int i = 0; i < (int)beads.size(); i++)
			if (beads[i])
				tmp.push_back(beads[i]);
		beads = tmp;
	}
}

void Changing()
{
	if (beads.empty())					// Ʋ�� ���� 1 : ���߷� ������ ��� ����� �� �ִ� ��츦 ������
		return;

	vector<int> new_beads;
	int seq = 1, pre = beads[0];		// �̹� �ռ� ������ ��� ������� ��츦 ���������Ƿ� seq ���� 1���� ����

	for (int i = 1; i < (int)beads.size(); i++) {
		if (beads[i] == pre)
			seq++;
		else {
			new_beads.push_back(seq);
			new_beads.push_back(pre);
			seq = 1;
			pre = beads[i];
		}
	}
	new_beads.push_back(seq);			// Ʋ�� ���� 2 : �迭���� '����'�̷� ���� ������ �׻� ���������� �����ؾ� �ϴµ� ����
	new_beads.push_back(pre);
	beads = new_beads;
}

int Blizard()
{
	for (int m = 1; m <= M; m++) {
		for (int i = 1; i <= s[m]; i++)
			map[N / 2 + dr[d[m]] * i][N / 2 + dc[d[m]] * i] = 0;	// ���� ���� ���ְ�

		int R = N / 2, C = N / 2;
		for (int i = 1; i <= N - 1; i++) {			// ���� ���� beads ���Ϳ� ����ȭ�ؼ� ���� ����
			if (i % 2) {							// i�� Ȧ���� ���
				for (int j = 1; j <= i; j++) {
					R += dr[3], C += dc[3];
					if (map[R][C]) beads.push_back(map[R][C]);
				}
				for (int j = 1; j <= i; j++) {
					R += dr[2], C += dc[2];
					if (map[R][C]) beads.push_back(map[R][C]);
				}
			}
			else {									// i�� ¦���� ���
				for (int j = 1; j <= i; j++) {
					R += dr[4], C += dc[4];
					if (map[R][C]) beads.push_back(map[R][C]);
				}
				for (int j = 1; j <= i; j++) {
					R += dr[1], C += dc[1];
					if (map[R][C]) beads.push_back(map[R][C]);
				}
			}
		}
		for (int i = 1; i <= N - 1; i++) {
			R += dr[3], C += dc[3];
			if (map[R][C]) beads.push_back(map[R][C]);
		}

		// ���� �ɸ� ���� 1 : ���� ���߽�Ű�� ��ȭ��Ű�� ���ȿ��� �ҿ뵹�� �� �ȿ� ���� �ʿ� ���µ� �װ� ��������
		Exploding();
		Changing();

		int index = 0;
		R = N / 2, C = N / 2;
		for (int i = 1; i <= N - 1; i++) {			// �� �� �� �ϰ� ���ǿ� �ٽ� �ҿ뵹�� �ʿ� �������
			if (i % 2) {							// i�� Ȧ���� ���
				for (int j = 1; j <= i; j++) {
					R += dr[3], C += dc[3];
					map[R][C] = index < (int)beads.size() ? beads[index++] : 0;
				}
				for (int j = 1; j <= i; j++) {
					R += dr[2], C += dc[2];
					map[R][C] = index < (int)beads.size() ? beads[index++] : 0;
				}
			}
			else {									// i�� ¦���� ���
				for (int j = 1; j <= i; j++) {
					R += dr[4], C += dc[4];
					map[R][C] = index < (int)beads.size() ? beads[index++] : 0;
				}
				for (int j = 1; j <= i; j++) {
					R += dr[1], C += dc[1];
					map[R][C] = index < (int)beads.size() ? beads[index++] : 0;
				}
			}
		}
		for (int i = 1; i <= N - 1; i++) {
			R += dr[3], C += dc[3];
			map[R][C] = index < (int)beads.size() ? beads[index++] : 0;
		}

		beads.clear();
	}
	return exploded[1] + 2 * exploded[2] + 3 * exploded[3];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];
	for (int i = 1; i <= M; i++)
		cin >> d[i] >> s[i];

	cout << Blizard();
	return 0;
}