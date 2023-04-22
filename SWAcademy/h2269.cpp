#include <vector>
#include <queue>
#include <tuple>
#include <cstring>
using namespace std;

int timegraph[60][60][24];              // timegraph[i][j][t] : i에서 j로 t시각에 갈 수 있는 최소 소요 시간
int pricegraph[60][60];                 // pricegraph[i][j] : i에서 j로의 최소 비용
int n, min_time[60], min_cost[60];      // min_time[i] : i에 도착할 때의 최소 소요 시간, min_cost[i] : i에 도착할 때의 최소 비용

void init(int N)
{
    n = N;
    memset(timegraph, 0, sizeof(timegraph));
    memset(pricegraph, 0, sizeof(pricegraph));
}

void add(int mStartAirport, int mEndAirport, int mStartTime, int mTravelTime, int mPrice)
{
    if (!timegraph[mStartAirport][mEndAirport][mStartTime])
        timegraph[mStartAirport][mEndAirport][mStartTime] = mTravelTime;
    else
        timegraph[mStartAirport][mEndAirport][mStartTime] = min(mTravelTime, timegraph[mStartAirport][mEndAirport][mStartTime]);

    if (!pricegraph[mStartAirport][mEndAirport])
        pricegraph[mStartAirport][mEndAirport] = mPrice;
    else
        pricegraph[mStartAirport][mEndAirport] = min(mPrice, pricegraph[mStartAirport][mEndAirport]);
}

int minTravelTime(int mStartAirport, int mEndAirport, int mStartTime)
{
    priority_queue<tuple<int, int, int>> pq;        // (총 걸린 시간, 현재 시간, 현재 공항)으로 저장
    memset(min_time, -1, sizeof(min_time));

    pq.push({ 0, mStartTime, mStartAirport });
    min_time[mStartAirport] = 0;

    while (!pq.empty())
    {
        int elapsed = -get<0>(pq.top());
        int current = get<1>(pq.top());
        int airport = get<2>(pq.top());
        pq.pop();

        if (airport == mEndAirport)
            return elapsed;

        for (register unsigned int to = 0; to < n; to++)
        {
            for (register unsigned int time = 0; time < 24; time++)
            {
                if (timegraph[airport][to][time])
                {
                    int wait = time < current ? time + 24 - current : time - current;
                    int take = wait + timegraph[airport][to][time];
                    int arrive = (current + take) % 24;
                    if (min_time[to] == -1 || min_time[to] > take + elapsed)
                    {
                        min_time[to] = take + elapsed;
                        pq.push({ -min_time[to], arrive, to });
                    }
                }
            }
        }
    }

    return -1;
}

int minPrice(int mStartAirport, int mEndAirport)
{
    priority_queue<pair<int, int>> pq;              // (총 비용, 현재 공항)으로 저장
    memset(min_cost, -1, sizeof(min_cost));

    pq.push({ 0, mStartAirport });
    min_cost[mStartAirport] = 0;

    while (!pq.empty())
    {
        int cost = -pq.top().first;
        int curr = pq.top().second;
        pq.pop();

        if (curr == mEndAirport)
            return cost;

        for (register unsigned int to = 0; to < n; to++)
        {
            if (pricegraph[curr][to] && (min_cost[to] == -1 || min_cost[to] > cost + pricegraph[curr][to]))
            {
                min_cost[to] = cost + pricegraph[curr][to];
                pq.push({ -min_cost[to], to });
            }
        }
    }

    return -1;
}
