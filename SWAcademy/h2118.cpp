#include <list>
using namespace std;

pair<int, int> soldier[100001];             // soldier[ID] = (소속팀, 점수 변동 횟수) -> 소속팀이 0이면 없는 상태
list<pair<int, int>> soldierInfo[6][6];     // soliderInfo[i][j] : {i팀 소속의 평판 점수가 j인 병사의 id, 그 병사의 점수 변동 횟수}

void init()
{
    for (register int i = 0; i < 100001; i++)
        soldier[i] = {0, 0};

    for (register int i = 1; i <= 5; i++)
        for (register int j = 1; j <= 5; j++)
            soldierInfo[i][j].clear();
}

void hire(int mID, int mTeam, int mScore)
{
    soldier[mID] = { mTeam, 0 };
    soldierInfo[mTeam][mScore].emplace_back(make_pair(mID, 0));
}

void fire(int mID)
{
    soldier[mID] = { 0, 0 };
}

void updateSoldier(int mID, int mScore)
{
    soldierInfo[soldier[mID].first][mScore].emplace_back(make_pair(mID, ++soldier[mID].second));
}

void updateTeam(int mTeam, int mChangeScore)
{
    if (mChangeScore > 0)
    {
        for (register int s = 4; s >= 1; s--)
        {
            if (!soldierInfo[mTeam][s].empty())
            {
                register int score = s + mChangeScore > 5 ? 5 : s + mChangeScore;
                soldierInfo[mTeam][score].splice(soldierInfo[mTeam][score].end(), soldierInfo[mTeam][s]);
            }
        }
    }
    else if (mChangeScore < 0)
    {
        for (register int s = 2; s <= 5; s++)
        {
            if (!soldierInfo[mTeam][s].empty())
            {
                register int score = s + mChangeScore < 1 ? 1 : s + mChangeScore;
                soldierInfo[mTeam][score].splice(soldierInfo[mTeam][score].end(), soldierInfo[mTeam][s]);
            }
        }
    }
}

int bestSoldier(int mTeam)
{
    register int bestId = 0;

    for (register int s = 5; s >= 1; s--)
    {
        if (!soldierInfo[mTeam][s].empty())
        {
            for (register auto it = soldierInfo[mTeam][s].begin(); it != soldierInfo[mTeam][s].end(); )
            {
                // 병사가 해고된 상태이거나 업데이트 횟수가 다르다면 제거
                if (!soldier[it->first].first || soldier[it->first].second != it->second)
                    it = soldierInfo[mTeam][s].erase(it);
                else    // 그렇지 않다면 bestId 최댓값 갱신
                {
                    bestId = max(bestId, it->first);
                    it++;
                }
            }
        }
        if (bestId)
            break;
    }

    return bestId;
}
