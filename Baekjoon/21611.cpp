#include <iostream>
#include <vector>
using namespace std;

int N, M, map[49][49], d[101], s[101], exploded[4];
const int dr[] = { 0, -1, 1, 0, 0 }, dc[] = { 0, 0, 0, -1, 1 };
vector<int> beads;

void Exploding()						// 틀린 이유 1 : 폭발로 구슬이 모두 사라질 수 있는 경우도 있음을 간과
{
	while (!beads.empty()) {
		int seq = 1, pre = beads[0];	// seq : 그룹을 이루는 구슬 개수, pre : 이전 구슬의 숫자
		bool complete = true;

		for (int i = 1; i < (int)beads.size(); i++) {
			if (beads[i] == pre)
				seq++;					// 현 구슬이 이전 구슬이랑 숫자가 같으면 seq만 증가
			else {						// 현 구슬이 이전 구슬이랑 숫자가 딱 달라졌을 때
				if (seq > 3) {			// 그룹을 이루는 구슬이 4개 이상일 때
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
		if (seq > 3) {					// 틀린 이유 2 : 배열에서 '연속'이런 말이 나오면 마지막까지 생각해야 하는 걸 깜빡
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
	if (beads.empty())					// 틀린 이유 1 : 폭발로 구슬이 모두 사라질 수 있는 경우를 간과함
		return;

	vector<int> new_beads;
	int seq = 1, pre = beads[0];		// 이미 앞서 구슬이 모두 사라지는 경우를 제외했으므로 seq 역시 1부터 시작

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
	new_beads.push_back(seq);			// 틀린 이유 2 : 배열에서 '연속'이런 말이 나오면 항상 마지막까지 생각해야 하는데 못함
	new_beads.push_back(pre);
	beads = new_beads;
}

int Blizard()
{
	for (int m = 1; m <= M; m++) {
		for (int i = 1; i <= s[m]; i++)
			map[N / 2 + dr[d[m]] * i][N / 2 + dc[d[m]] * i] = 0;	// 먼저 구슬 없애고

		int R = N / 2, C = N / 2;
		for (int i = 1; i <= N - 1; i++) {			// 남은 구슬 beads 벡터에 직렬화해서 집어 넣음
			if (i % 2) {							// i가 홀수일 경우
				for (int j = 1; j <= i; j++) {
					R += dr[3], C += dc[3];
					if (map[R][C]) beads.push_back(map[R][C]);
				}
				for (int j = 1; j <= i; j++) {
					R += dr[2], C += dc[2];
					if (map[R][C]) beads.push_back(map[R][C]);
				}
			}
			else {									// i가 짝수일 경우
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

		// 오래 걸린 이유 1 : 구슬 폭발시키고 변화시키는 동안에는 소용돌이 맵 안에 넣을 필요 없는데 그걸 생각못함
		Exploding();
		Changing();

		int index = 0;
		R = N / 2, C = N / 2;
		for (int i = 1; i <= N - 1; i++) {			// 할 거 다 하고 막판에 다시 소용돌이 맵에 집어넣음
			if (i % 2) {							// i가 홀수일 경우
				for (int j = 1; j <= i; j++) {
					R += dr[3], C += dc[3];
					map[R][C] = index < (int)beads.size() ? beads[index++] : 0;
				}
				for (int j = 1; j <= i; j++) {
					R += dr[2], C += dc[2];
					map[R][C] = index < (int)beads.size() ? beads[index++] : 0;
				}
			}
			else {									// i가 짝수일 경우
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