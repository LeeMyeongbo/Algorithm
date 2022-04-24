#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int map[201][201], N, K;                                // 맨 밑에는 map[200][c]에 저장
const int dr[] = {0, -1}, dc[] = {1, 0};                // 오른쪽, 위쪽 이렇게 비교

void rotate(vector<pair<int, pair<int, int>>> &list)    // 평행이동 + 회전 + 평행이동
{
    int M = 0, min_r = 1000000, min_c = 1000000;

    // 각 좌표 (r, c)마다 r의 최솟값, c의 최솟값 구함
    for (auto &p : list) {
        min_r = min(min_r, p.second.first);
        min_c = min(min_c, p.second.second);
    }

    // r의 최솟값, c의 최솟값 만큼 각 좌표를 빼주고 (최대한 왼쪽 위로 밀착해준다 생각) 전체 좌표 중에서 가장 큰 숫자 M 구함
    for (auto &p : list) {
        p.second.first -= min_r;
        p.second.second -= min_c;
        M = max(M, max(p.second.first, p.second.second));
    }

    // 그리고 회전 (반시계 : (r, c)->(M - c, r), 시계 : (r, c)->(c, M - r))
    min_r = 1000000, min_c = 1000000;
    for (auto &p : list) {
        p.second = {p.second.second, M - p.second.first};
        min_r = min(min_r, p.second.first), min_c = min(min_c, p.second.second);
    }

    // 다시 평행이동 (왼쪽 위로 밀착)
    for (auto &p : list)
        p.second = {p.second.first - min_r, p.second.second - min_c};
}

void adjust(int start)    // 물고기 수 조정 (start : 시작 열)
{
    int change[201][201] = {0, }, roll_back[201] = {0, };   // change[r][c] : (r, c)에서 물고기 수가 얼만큼 변화하는지 저장

    for (int c = start; c < N; c++) {
        for (int r = 200; map[r][c]; r--) {

            // 2방향씩만 비교 (4방향으로 비교하면 중복해서 살피게 됨!)
            for (int di = 0; di < 2; di++) {
                int R = r + dr[di], C = c + dc[di];

                // 오른쪽, 위쪽하고만 비교하므로 R이 200보다 커지거나 C가 start보다 작아질 일 x
                if (C < N && map[R][C]) {
                    if (map[R][C] > map[r][c]) {
                        int d = (map[R][C] - map[r][c]) / 5;
                        change[R][C] -= d, change[r][c] += d;
                    }
                    else {
                        int d = (map[r][c] - map[R][C]) / 5;
                        change[R][C] += d, change[r][c] -= d;
                    }
                }
            }
        }
    }

    // 인접한 어항마다 change 설정했으면 map에다가 반영
    for (int c = start; c < N; c++)
        for (int r = 200; map[r][c]; r--)
            map[r][c] += change[r][c];

    // 왼쪽->위쪽 순으로 물고기 수 roll_back에다가 임시 저장
    int i = 0;
    for (int c = start; c < N; c++)
        for (int r = 200; map[r][c]; r--)
            roll_back[i++] = map[r][c];
    
    // 임시 저장돼 있던 roll_back으로 map 갱신 (맨 밑의 행이 200이라는 것 명심)
    memset(map, 0, sizeof(map));
    for (i = 0; i < N; i++)
        map[200][i] = roll_back[i];
}

void step1()   // 물고기 수 가장 작은 어항에 1마리씩 추가
{
    int Min = 10000000;
    for (int i = 0; i < N; i++)
        Min = min(Min, map[200][i]);
    for (int i = 0; i < N; i++)
        if (map[200][i] == Min)
            map[200][i]++;
}

void step2()    // 순차적 공중 부양 + 물고기 수 조정
{
    map[199][1] = map[200][0];

    int start = 1, pre_start = 0;
    while (true) {
        vector<pair<int, pair<int, int>>> list;

        // 현재 start 열에서의 어항 수가 2 이상일 경우
        for (; map[199][start]; start++)
            for (int h = 200; map[h][start]; h--)
                list.push_back({map[h][start], {h, start}});    // (물고기 수, (r, c)) 꼴로 해당 어항들 모두 저장

        rotate(list);

        bool flag = true;
        int height = 0;                 // 회전한 어항들의 최대 높이 지정
        for (auto &l : list) {

            // 만약 현재 start에서 c만큼 더해서 N 이상 -> 더 이상 진행 x
            if (l.second.second + start >= N) {
                flag = false;
                break;
            }
            height = max(height, l.second.first);
        }

        // 진행 가능하다면 (199 - height)행 start열 만큼 평행이동해서 어항 저장
        if (flag)
            for (auto &l : list)
                map[l.second.first + (199 - height)][l.second.second + start] = l.first;
        else {
            // 그게 아니면 바로 이전 start열에서부터 차례로 살피며 물고기 수 조정
            adjust(pre_start);
            break;
        }
        pre_start = start;
    }
}

void step3()    // (N / 2), (N / 4) 공중 부양 + 물고기 수 조정
{
    int start = 0, num = N / 2;

    for (int re = 0; re < 2; re++) {
        vector<pair<int, pair<int, int>>> list;

         // 첫 번째는 0에서부터 (N / 2)개, 두 번째는 (N / 2)에서부터 (N / 4)개의 열의 어항들 저장
        for (; start < num; start++)
            for (int r = 200; map[r][start]; r--)
                list.push_back({map[r][start], {r, start}});

        rotate(list);
        rotate(list);

        int height = 0;
        for (auto &l : list)
            height = max(height, l.second.first);

        // - re 하는 이유 : 첫 번째 할 때는 기존 어항들 높이가 다 1이고 두 번째에서는 높이가 다 2임
        for (auto &l : list)
            map[l.second.first + (199 - height - re)][l.second.second + start] = l.first;
        
        num += num / 2;
    }
    adjust(N / 2 + N / 4);
}

int main()
{
    cin >> N >> K;
    for (int i = 0; i < N; i++)
        cin >> map[200][i];

    for (int s = 0; ; s++) {
        int Max = 0, Min = 100000000;

        for (int c = 0; c < N; c++) {
            Max = max(Max, map[200][c]);
            Min = min(Min, map[200][c]);
        }
        if (Max - Min <= K) {
            cout << s;
            return 0;
        }
        step1();
        step2();
        step3();
    }
}