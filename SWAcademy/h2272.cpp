#include <queue>
#include <set>
#include <cstring>
#include <cmath>
using namespace std;

struct Node {
    int time;           // 도시에 도착하는 시간
    int city;           // 도착하는 도시
    int tax;            // 세금

    bool operator<(const Node& n) const {
        return time > n.time;
    }
};
set<pair<int, int>> cities[200];                 // cities[i] : (세금이 도시 i에 도착하는 시간, 세금의 양)
priority_queue<Node> manager;
priority_queue<pair<int, int>> arrivalTime;
int cityCnt, managerCnt, ans;
int reservedCity[200];                           // reservedCity[i] : 도시 i에 관리가 파견되었을 때 예정 도착 시간 저장

void init(int N, int M)
{
    ans = 0;
    cityCnt = N;
    managerCnt = M;
}

void destroy()
{
    for (register int i = 1; i < cityCnt; i++)
        cities[i].clear();
    memset(reservedCity, 0, sizeof(reservedCity));
    manager = {};
}

void dispatch(int tStamp)
{
    while (manager.size() < managerCnt)
    {
        int max_tax = 0, city = 0;
        for (register int i = 1; i < cityCnt; i++)
        {
            if (reservedCity[i])
                continue;

            int tax = 0;
            for (register auto it = cities[i].begin(); it != cities[i].end(); it++)
            {
                if (it->first <= tStamp + i)
                    tax += it->second;
                else
                    break;
            }
            if (tax > max_tax)
                max_tax = tax, city = i;
        }

        if (city)                                           // 파견할 도시가 있다면
        {
            manager.push({ tStamp + city, city });          // 해당 도시 도착 에정 시간 저장하고
            reservedCity[city] = tStamp + city;             // 파견 중인 도시 표시
        }
        else                                                // 파견할 도시가 없다면 break
            break;
    }
}

void progress(int tStamp)
{
    while (!manager.empty() && manager.top().time <= tStamp)
    {
        Node n = manager.top();
        manager.pop();

        if (!n.city)                // 수도에 도착했을 경우
        {
            ans += n.tax;
            dispatch(n.time);       // 곧바로 파견 나갈 수 있는지 살핌
        }
        else                        // 그 외의 도시에 도착했을 경우
        {
            reservedCity[n.city] = 0;

            int tax = 0;
            for (register auto it = cities[n.city].begin(); it != cities[n.city].end(); )
            {
                if (it->first <= n.time)
                {
                    tax += it->second;
                    it = cities[n.city].erase(it);
                }
                else break;
            }

            manager.push({ n.time + n.city, 0, tax });
        }
    }
}

int order(int tStamp, int mCityA, int mCityB, int mTax)
{
    while (!manager.empty() && manager.top().time < tStamp)
        progress(manager.top().time);

    cities[mCityB].insert({ tStamp + abs(mCityA - mCityB), mTax });
    dispatch(max(tStamp + mCityB, tStamp + abs(mCityA - mCityB)) - mCityB);

    return ans;
}

int check(int tStamp)
{
    while (!manager.empty() && manager.top().time <= tStamp)
        progress(manager.top().time);

    return ans;
}
