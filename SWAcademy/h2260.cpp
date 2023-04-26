#include <vector>
#include <queue>
#include <cstring>
#include <set>
using namespace std;

const int powering[] = { 10, 5, 3, 2 };
struct Rank {
    int power, member;

    bool operator<(const Rank& r) const {
        if (power > r.power)
            return true;
        else if (power == r.power)
            return member < r.member;
        return false;
    }
};
set<Rank> ranking;
vector<int> graph[20000];
queue<pair<int, int>> q;                        // (이동 거리, 현재 위치)
int n, purchase[20000], influence[20000];
bool visited[20000];

void update(int member)
{
    memset(visited, false, sizeof(visited));

    q.emplace(make_pair(0, member));
    visited[member] = true;

    ranking.erase({ influence[member], member });
    influence[member] = 0;

    while (!q.empty())
    {
        register int dist = q.front().first;
        register int curr = q.front().second;
        q.pop();

        influence[member] += powering[dist] * purchase[curr];

        if (dist == 3) continue;

        for (int& friends : graph[curr])
            if (!visited[friends])
            {
                q.emplace(make_pair(dist + 1, friends));
                visited[friends] = true;
            }
    }
    ranking.insert({ influence[member], member });
}

void init(int N, int mPurchasingPower[20000], int M, int mFriend1[20000], int mFriend2[20000])
{
    n = N;
    ranking.clear();
    for (register unsigned int i = 0; i < N; i++)
    {
        graph[i].clear();
        purchase[i] = mPurchasingPower[i];
    }

    for (register unsigned int i = 0; i < M; i++)
    {
        graph[mFriend1[i]].emplace_back(mFriend2[i]);
        graph[mFriend2[i]].emplace_back(mFriend1[i]);
    }

    for (register unsigned int i = 0; i < N; i++)
        update(i);
}

int influencer(int mRank)
{
    register unsigned int i = 0;
    for (auto it = ranking.begin(); it != ranking.end(); it++)
    {
        i++;
        if (i == mRank)
            return it->member;
    }

    return 0;
}

int addPurchasingPower(int mID, int mPower)
{
    purchase[mID] += mPower;

    memset(visited, false, sizeof(visited));
    vector<int> friend_list;

    q.emplace(make_pair(0, mID));
    visited[mID] = true;

    while (!q.empty())
    {
        register int dist = q.front().first;
        register int curr = q.front().second;
        q.pop();

        ranking.erase({ influence[curr], curr });
        influence[curr] += powering[dist] * mPower;
        ranking.insert({ influence[curr], curr });

        if (dist == 3) continue;

        for (int& friends : graph[curr])
            if (!visited[friends])
            {
                q.emplace(make_pair(dist + 1, friends));
                visited[friends] = true;
            }
    }

    return influence[mID];
}

int addFriendship(int mID1, int mID2)
{
    graph[mID1].emplace_back(mID2);
    graph[mID2].emplace_back(mID1);

    vector<int> updateList;
    memset(visited, false, sizeof(visited));

    q.emplace(make_pair(0, mID1));
    q.emplace(make_pair(0, mID2));
    visited[mID1] = visited[mID2] = true;

    while (!q.empty())
    {
        register int dist = q.front().first;
        register int curr = q.front().second;
        q.pop();

        updateList.emplace_back(curr);
        if (dist == 2) continue;

        for (int& friends : graph[curr])
        {
            if (!visited[friends])
            {
                q.emplace(make_pair(dist + 1, friends));
                visited[friends] = true;
            }
        }
    }

    for (int& member : updateList)
        update(member);

    return influence[mID1] + influence[mID2];
}
