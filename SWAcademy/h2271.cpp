#include <cstring>
#include <cmath>
#include <queue>
#include <set>
#include <unordered_map>
using namespace std;

struct Result {
    int id, num;
};
const int dr[] = { 0, 1, 0, -1 }, dc[] = { 1, 0, -1, 0 };
int n, S, theater[2001][10][10];
int emptySeatsTree[4096];                       // emptySeatsTree : 각 영화관 별로 가장 큰 연결된 빈 좌석을 저장하는 Max_IndexedTree
unordered_map<int, Result> reserved;            // (예약 번호 : (영화관 번호, 시작 좌석 번호))
set<pair<int, int>> emptySeatsByCinema[2001];   // 영화관 별로 (시작 좌석 번호(0 ~ 99), 연결된 빈 좌석 수) 저장

void updateTree(int index, int val)
{
    emptySeatsTree[index] = val;
    index >>= 1;

    while (index)
    {
        emptySeatsTree[index] = max(emptySeatsTree[index << 1], emptySeatsTree[(index << 1) + 1]);
        index >>= 1;
    }
}

int searchTree(int val)
{
    register int index = 1;
    if (emptySeatsTree[index] < val)
        return 0;

    while (index < S)
    {
        if (emptySeatsTree[index << 1] >= val)
            index <<= 1;
        else
            index = (index << 1) + 1;
    }

    return index;
}

void init(int N)
{
    memset(theater, 0, sizeof(theater));
    memset(emptySeatsTree, 0, sizeof(emptySeatsTree));
    reserved.clear();

    n = N;
    S = 1 << (int)ceil(log2(N));
    for (register int i = 1; i <= N; i++)
    {
        emptySeatsByCinema[i].clear();
        emptySeatsByCinema[i].insert({ 0, 100 });

        register int idx = S + i - 1;
        updateTree(idx, 100);
    }
}

void countLeftSeats(int cinemaNum)
{
    register int maxEmpty = 0;
    queue<int> q;
    bool visited[10][10] = { false, };

    for (register int r = 0; r < 10; r++)
        for (register int c = 0; c < 10; c++)
        {
            if (!theater[cinemaNum][r][c] && !visited[r][c])
            {
                register int startNum = r * 10 + c, cnt = 0;
                visited[r][c] = true;
                q.emplace(startNum);

                while (!q.empty())
                {
                    register int cur = q.front();
                    q.pop();

                    cnt++;
                    for (int d = 0; d < 4; d++)
                    {
                        register int R = cur / 10 + dr[d];
                        register int C = cur % 10 + dc[d];
                        if (R >= 0 && R < 10 && C >= 0 && C < 10 && !visited[R][C] && !theater[cinemaNum][R][C])
                        {
                            visited[R][C] = true;
                            q.emplace(R * 10 + C);
                        }
                    }
                }

                emptySeatsByCinema[cinemaNum].insert({ startNum, cnt });
                maxEmpty = max(maxEmpty, cnt);
            }
        }

    updateTree(cinemaNum + S - 1, maxEmpty);
}

Result reserveSeats(int mID, int K)
{
    register Result res = { 0, 0 };
    register int idx = searchTree(K);

    if (idx)
    {
        res.id = idx - S + 1;
        for (auto& p : emptySeatsByCinema[res.id])
            if (p.second >= K)
            {
                res.num = p.first + 1;
                break;
            }
        reserved.insert({ mID, res });

        emptySeatsByCinema[res.id].clear();

        priority_queue<int, vector<int>, greater<int>> pq;
        bool visited[10][10] = { false, };

        pq.emplace(res.num - 1);
        visited[(res.num - 1) / 10][(res.num - 1) % 10] = true;

        while (!pq.empty())
        {
            register int cur = pq.top();
            pq.pop();

            theater[res.id][cur / 10][cur % 10] = mID;
            if (!(--K))
            {
                countLeftSeats(res.id);
                return res;
            }

            for (register int d = 0; d < 4; d++)
            {
                register int R = cur / 10 + dr[d];
                register int C = cur % 10 + dc[d];
                if (R >= 0 && R < 10 && C >= 0 && C < 10 && !visited[R][C] && !theater[res.id][R][C])
                {
                    visited[R][C] = true;
                    pq.emplace(R * 10 + C);
                }
            }
        }
    }

    return res;
}

Result cancelReservation(int mID)
{
    register Result res = reserved[mID];
    reserved.erase(mID);

    register int ans = 0;
    queue<int> q;

    theater[res.id][(res.num - 1) / 10][(res.num - 1) % 10] = 0;
    q.emplace(res.num - 1);

    while (!q.empty())
    {
        register int cur = q.front();
        q.pop();

        ans += cur + 1;
        
        for (register int d = 0; d < 4; d++)
        {
            register int R = cur / 10 + dr[d];
            register int C = cur % 10 + dc[d];
            if (R >= 0 && R < 10 && C >= 0 && C < 10 && theater[res.id][R][C] == mID)
            {
                theater[res.id][R][C] = 0;
                q.emplace(R * 10 + C);
            }
        }
    }

    emptySeatsByCinema[res.id].clear();

    countLeftSeats(res.id);

    return { res.id, ans };
}
