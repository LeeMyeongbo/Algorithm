#include <cstring>
#include <cmath>
#include <queue>
using namespace std;

struct Result {
    int id, num;
};
const int dr[] = { 0, 1, 0, -1 }, dc[] = { 1, 0, -1, 0 };   // 동 남 서 북 순서
int n, S, theater[2001][10][10];
int emptySeatsTree[4096];                       // 각 영화관 별로 가장 큰 연결된 빈 좌석을 저장하는 Max_IndexedTree
int emptySeatsTreeByTheater[2001][256];         // 영화관 마다 시작 좌석 별 연결된 빈 좌석 저장하는 Max_IndexedTree
Result reservation[50001];
queue<int> q;

void updateTree(int tree[], int index, int val)
{
    tree[index] = val;
    index >>= 1;

    while (index)
    {
        tree[index] = max(tree[index << 1], tree[(index << 1) + 1]);
        index >>= 1;
    }
}

int searchTree(int tree[], int K, int S)
{
    register int index = 1;

    if (tree[index] < K)
        return 0;

    while (index < S)
    {
        if (tree[index << 1] >= K)
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
    memset(emptySeatsTreeByTheater, 0, sizeof(emptySeatsTreeByTheater));

    n = N;
    S = 1 << (int)ceil(log2(N));

    for (register int i = 1; i <= N; i++)
    {
        register int idx = S + i - 1;
        updateTree(emptySeatsTree, idx, 100);

        idx = 128;
        updateTree(emptySeatsTreeByTheater[i], idx, 100);
    }
}

void countLeftSeats(int cinemaNum)
{
    register int maxEmpty = 0;
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

                updateTree(emptySeatsTreeByTheater[cinemaNum], 128 + startNum, cnt);
                maxEmpty = max(maxEmpty, cnt);
            }
        }

    updateTree(emptySeatsTree, cinemaNum + S - 1, maxEmpty);
}

Result reserveSeats(int mID, int K)
{
    register Result res = { 0, 0 };
    register int idx = searchTree(emptySeatsTree, K, S);

    if (idx)
    {
        res.id = idx - S + 1;
        res.num = searchTree(emptySeatsTreeByTheater[res.id], K, 128) - 127;
        reservation[mID] = res;

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
                memset(emptySeatsTreeByTheater[res.id], 0, sizeof(emptySeatsTreeByTheater[res.id]));
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
    register Result res = reservation[mID];
    register int ans = 0;

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

    memset(emptySeatsTreeByTheater[res.id], 0, sizeof(emptySeatsTreeByTheater[res.id]));
    countLeftSeats(res.id);

    return { res.id, ans };
}
