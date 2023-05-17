/* boj 3830이랑 비슷... 잘 익히기! */

#include <utility>
using namespace std;

int n;
pair<int, int> player[100001];          // player[i] = {루트(집합 내 번호가 가장 작은 정점), 현재 정점 i의 점수 - 루트 점수}

void init(int N)
{
    n = N;
    for (int i = 1; i <= N; i++)
        player[i] = { i, 0 };
}

pair<int, int> findRootNupdate(int v)
{
    if (v == player[v].first)           // 루트에 도달하면 루트의 번호만 반환 (gap = 0)
        return { v, 0 };

    pair<int, int> p = findRootNupdate(player[v].first);        // 루트에 도달할 때까지 탐색

    player[v].first = p.first, player[v].second += p.second;    // 재귀에서 돌아오며 현 정점 v의 루트 갱신 + 차이 누적
    return player[v];
}

void updateScore(int mWinnerID, int mLoserID, int mScore)       // mWinner와 mLoser의 루트를 찾아서 점수 갱신
{
    pair<int, int> p1 = findRootNupdate(mWinnerID);
    pair<int, int> p2 = findRootNupdate(mLoserID);

    player[p1.first].second += mScore, player[p2.first].second -= mScore;
}

void unionTeam(int mPlayerA, int mPlayerB)                      // 역시 mPlayerA와 mPlayerB의 루트를 찾아서 연결
{
    pair<int, int> p1 = findRootNupdate(mPlayerA);
    pair<int, int> p2 = findRootNupdate(mPlayerB);

    if (p1.first < p2.first)    // 번호가 작은 정점을 루트로 삼아야 하므로 번호가 더 큰 루트의 부모가 번호가 더 작은 루트가 됨
        swap(p1, p2);

    player[p1.first] = { p2.first, player[p1.first].second - player[p2.first].second };
}

int getScore(int mID)                                           // mID가 루트일 수도 있으므로 주의
{
    pair<int, int> p = findRootNupdate(mID);

    return p.first != mID ? player[p.first].second + player[mID].second : player[mID].second;
}
