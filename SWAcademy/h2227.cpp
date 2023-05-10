#include <string>
#include <cstring>
#include <unordered_map>
#include <vector>
using namespace std;

const int dr[] = { -1, -1, 0, 1, 1, 1, 0, -1 }, dc[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
unordered_map<string, int> monarch2Pos;
int n, map[25][25], parent[625];
bool ishostile[625][625];

void init(int N, int mSoldier[25][25], char mMonarch[25][25][11])
{
    n = N;
    memcpy(map, mSoldier, sizeof(map));

    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
        {
            string name(mMonarch[r][c]);
            monarch2Pos.insert({ name, r * N + c });

            parent[r * N + c] = r * N + c;
        }
}

void destroy()
{
    monarch2Pos.clear();
    memset(ishostile, false, sizeof(ishostile));
}

int findRoot(int v)
{
    if (v == parent[v])
        return v;

    return parent[v] = findRoot(parent[v]);
}

int ally(char mMonarchA[11], char mMonarchB[11])
{
    register int a = monarch2Pos[string(mMonarchA)];
    register int b = monarch2Pos[string(mMonarchB)];

    a = findRoot(a);
    b = findRoot(b);

    if (a == b)
        return -1;

    if (ishostile[a][b])
        return -2;

    if (a < b)
        swap(a, b);                                         // 무조건 index가 작은 쪽을 부모로 삼음

    for (register int i = 0; i < n * n; i++)                // 자식 노드에게 적대적인 군주는 부모 노드에게도 적대적이 됨
        if (ishostile[a][i])
        {
            ishostile[b][i] = ishostile[i][b] = true;
            ishostile[a][i] = ishostile[i][a] = false;
        }

    parent[a] = b;
    return 1;
}

int attack(char mMonarchA[11], char mMonarchB[11], char mGeneral[11])
{
    register int a = monarch2Pos[string(mMonarchA)];
    register int b = monarch2Pos[string(mMonarchB)];

    register int roota = findRoot(a);
    register int rootb = findRoot(b);

    if (roota == rootb)
        return -1;

    for (int d = 0; d < 8; d++)                                                     // B 주위 8방향을 살핌
    {
        int r = b / n + dr[d];
        int c = b % n + dc[d];
        if (r >= 0 && r < n && c >= 0 && c < n && findRoot(r * n + c) == roota)     // B 주위에 A의 동맹이 있다면 전투 시작
        {
            int attacker = 0, defender = map[b / n][b % n];
            for (int di = 0; di < 8; di++)                                          // 다시 B 주위 8방향 살피며 공격 동맹 + 방어 동맹 군사 모집
            {
                int new_r = b / n + dr[di];
                int new_c = b % n + dc[di];
                if (new_r >= 0 && new_r < n && new_c >= 0 && new_c < n)
                {
                    int rootAdjacent = findRoot(new_r * n + new_c);
                    if (rootAdjacent == roota)
                    {
                        attacker += map[new_r][new_c] / 2;
                        map[new_r][new_c] -= map[new_r][new_c] / 2;
                    }
                    else if (rootAdjacent == rootb)
                    {
                        defender += map[new_r][new_c] / 2;
                        map[new_r][new_c] -= map[new_r][new_c] / 2;
                    }
                }
            }
            if (attacker > defender)                                // 공격 성공했을 경우
            {
                vector<int> allyBList;
                for (register int v = 0; v < n * n; v++)            // B와 동맹인 군주들 쭉 저장
                {
                    int rootv = findRoot(v);
                    if (rootv == rootb)
                        allyBList.push_back(v);
                }

                if (allyBList[0] == b)                              // 점령당한 B가 동맹의 루트였을 경우 (rootb == b 인 경우)
                {
                    for (register int i = 1; i < (int)allyBList.size(); i++)
                        parent[allyBList[i]] = allyBList[1];        // 그 동맹 내 B 다음으로 index가 작은 군주를 루트로 삼음

                    if ((int)allyBList.size() > 1)
                    {
                        for (register int i = 0; i < n * n; i++)    // B의 적대관계 다음 루트에게 승계
                            if (ishostile[b][i])
                                ishostile[allyBList[1]][i] = ishostile[i][allyBList[1]] = true;

                        ishostile[roota][allyBList[1]] = ishostile[allyBList[1]][roota] = true;
                    }
                }
                else
                    ishostile[roota][rootb] = ishostile[rootb][roota] = true;

                monarch2Pos.erase(string(mMonarchB));
                monarch2Pos.insert({ string(mGeneral), b});

                parent[b] = b;                                      // B의 관계 초기화
                for (int i = 0; i < n * n; i++)
                    ishostile[b][i] = ishostile[i][b] = false;      // B의 적대관계 초기화

                map[b / n][b % n] = attacker - defender;
                ally(mMonarchA, mGeneral);
                
                return 1;
            }
            else                                                    // 공격 실패했을 경우
            {
                ishostile[roota][rootb] = ishostile[rootb][roota] = true;
                map[b / n][b % n] = defender - attacker;

                return 0;
            }
        }
    }

    return -2;
}

int recruit(char mMonarch[11], int mNum, int mOption)
{
    register int m = monarch2Pos[string(mMonarch)];
    if (!mOption)
    {
        map[m / n][m % n] += mNum;

        return map[m / n][m % n];
    }

    register int rootm = findRoot(m), ans = 0;
    for (register int i = 0; i < n * n; i++)
    {
        int rooti = findRoot(i);
        if (rooti == rootm)
        {
            map[i / n][i % n] += mNum;
            ans += map[i / n][i % n];
        }
    }

    return ans;
}
