#include <vector>
#include <queue>
#include <cstring>
#include <tuple>
using namespace std;

const vector<vector<int>> comb = { {0}, {1}, {2}, {0, 1}, {0, 2}, {1, 2}, {0, 1, 2} };
int n, limitDist, centralcity[3], centralIdx[3001], price[3001], dij[3][3001], distSum[7][3001];     // dij[i][j] : 중심도시 i와 도시 j 사이의 최소 거리
vector<pair<int, int>> graph[3001];         // graph[i] : (연결된 도시 j 와의 거리, j)로 저장
priority_queue<pair<int, int>> pq;          // (현재까지의 거리, 현재 도시)로 저장
priority_queue<tuple<int, int, int>> recommend[7]; // recommend : comb[i] 조합에 해당하는 출근 거리 합 중 한계 거리 이내의 도시만 (가격, 출근 거리 합, 도시 id)로 저장

int getCentralCombIdx(int size, int centralList[])
{
    if (size == 3)
        return 6;
    
    if (size == 1)
        return centralIdx[centralList[0]];
    
    else
    {
        if (!centralIdx[centralList[0]] && centralIdx[centralList[1]] == 1 || centralIdx[centralList[0]] == 1 && !centralIdx[centralList[1]])
            return 3;

        if (!centralIdx[centralList[0]] && centralIdx[centralList[1]] == 2 || centralIdx[centralList[0]] == 2 && !centralIdx[centralList[1]])
            return 4;

        return 5;
    }
}

void init(int N, int mDownTown[])
{
    memset(price, 0, sizeof(price));
    for (unsigned register int i = 1; i <= N; i++)
        graph[i].clear();

    n = N;
    centralcity[0] = mDownTown[0];
    centralcity[1] = mDownTown[1];
    centralcity[2] = mDownTown[2];

    centralIdx[mDownTown[0]] = 0;
    centralIdx[mDownTown[1]] = 1;
    centralIdx[mDownTown[2]] = 2;
}

void newLine(int M, int mCityIDs[], int mDistances[])
{
    for (unsigned register int i = 0; i < M - 1; i++)
    {
        pair<int, int> p1 = { mDistances[i], mCityIDs[i + 1] };
        graph[mCityIDs[i]].emplace_back(p1);

        p1 = { mDistances[i], mCityIDs[i] };
        graph[mCityIDs[i + 1]].emplace_back(p1);
    }
}

void changeLimitDistance(int mLimitDistance)
{
    memset(dij, -1, sizeof(dij));
    limitDist = mLimitDistance;

    for (register unsigned int i = 0; i < 3; i++)             // 먼저 0번에서 2번까지 각 중심도시에서 다른 도시까지의 거리 저장
    {
        pq.push({ 0, centralcity[i] });
        dij[i][centralcity[i]] = 0;

        while (!pq.empty())
        {
            unsigned register int dist = -pq.top().first;
            unsigned register int curr = pq.top().second;
            pq.pop();

            if (dist > dij[i][curr])
                continue;

            for (pair<int, int>& p : graph[curr])
            {
                if (dij[i][p.second] == -1 || dij[i][p.second] > dist + p.first)
                {
                    dij[i][p.second] = dist + p.first;
                    pq.push({ -dij[i][p.second], p.second });
                }
            }
        }
    }

    for (register unsigned int i = 0; i < 7; i++)         // 0번 중심도시 -> 1번 중심도시 -> 2번 중심도시 -> 0,1번 중심도시... 순으로 진행
    {
        recommend[i] = {};
        for (register int city = 1; city <= n; city++)
        {
            distSum[i][city] = 0;
            if (city == centralcity[0] || city == centralcity[1] || city == centralcity[2])
                continue;

            for (int idx : comb[i])
            {
                if (dij[idx][city] != -1)
                    distSum[i][city] += dij[idx][city];
                else
                {
                    distSum[i][city] = 1 << 31;
                    break;
                }
            }

            if (distSum[i][city] <= mLimitDistance)
            {
                tuple<int, int, int> t = { -price[city], -distSum[i][city], -city };
                recommend[i].emplace(t);
            }
        }
    }
}

int findCity(int mOpt, int mDestinations[])
{
    register unsigned int i = getCentralCombIdx(mOpt, mDestinations);
    if (!recommend[i].empty())
    {
        while (!recommend[i].empty())
        {
            int cost = -get<0>(recommend[i].top());
            int dist = -get<1>(recommend[i].top());
            int curr = -get<2>(recommend[i].top());
            recommend[i].pop();

            if (cost == price[curr])
            {
                price[curr]++;
                tuple<int, int, int> t = { -price[curr], -dist, -curr };
                recommend[i].emplace(t);

                return curr;
            }

            tuple<int, int, int> t = { -price[curr], -dist, -curr };
            recommend[i].emplace(t);
        }
    }

    return -1;
}
