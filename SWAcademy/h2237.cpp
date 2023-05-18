#include <queue>
#include <cstring>
#define MAX_N 100
using namespace std;

struct Node {
    int e, pos;                                                     // e : 에너지, pos = row * n + col

    bool operator<(const Node& n) const {
        if (e == n.e)
            return pos > n.pos;

        return e < n.e;
    }
};
const int dr[] = { 0, 1, 0, -1 }, dc[] = { 1, 0, -1, 0 };           // 동 남 서 북 순서
int n, bacteriaNum[3], energy[MAX_N][MAX_N], bacteria[MAX_N][MAX_N];
priority_queue<Node> pq;
queue<int> q;

void init(int N, int mDish[MAX_N][MAX_N])
{
    n = N;
    memcpy(energy, mDish, sizeof(energy));
    memset(bacteria, 0, sizeof(bacteria));
    bacteriaNum[1] = bacteriaNum[2] = 0;
}

void activateBacteria(bool visited[MAX_N][MAX_N], int r, int c, int target)
{
    visited[r][c] = true;
    q.emplace(r * n + c);

    while (!q.empty())
    {
        register int cur = q.front();
        q.pop();

        for (register int d = 0; d < 4; d++)
        {
            register int R = cur / n + dr[d];
            register int C = cur % n + dc[d];
            if (R >= 0 && R < n && C >= 0 && C < n && !visited[R][C])
            {
                visited[R][C] = true;
                if (bacteria[R][C] == target)                   // 종류가 같은 세균이 있을 경우 큐 저장(활성화)
                    q.push(R * n + C);
                else if (!bacteria[R][C])                       // 비어있는 셀은 pq에 저장(인접한 셀로 번식하기 위함)
                    pq.push({ energy[R][C], R * n + C });
            }
        }
    }
}

int dropMedicine(int mTarget, int mRow, int mCol, int mEnergy)
{
    mRow--, mCol--;
    if (bacteria[mRow][mCol] && bacteria[mRow][mCol] != mTarget)    // 다른 종류의 세균 존재 시 종료
        return bacteriaNum[mTarget];
    
    bool visited[MAX_N][MAX_N] = { false, };
    pq = {};

    if (bacteria[mRow][mCol])                                       // 같은 종류 세균 존재 시 연결된 세균들 모두 활성화하고
        activateBacteria(visited, mRow, mCol, mTarget);             // 거기에 인접한 비어있는 셀 모두 pq에 삽입
    else                                                            // 세균 없으면 pq에 바로 삽입
    {
        visited[mRow][mCol] = true;
        register Node node = { energy[mRow][mCol], mRow * n + mCol };
        pq.emplace(node);
    }

    while (!pq.empty())                                             // 세균 번식
    {
        register Node node = pq.top();
        pq.pop();

        bacteria[node.pos / n][node.pos % n] = mTarget;
        mEnergy -= node.e;
        bacteriaNum[mTarget]++;

        if (mEnergy <= 0)
            return bacteriaNum[mTarget];                            // 번식 에너지가 없으면 종료

        for (register int d = 0; d < 4; d++)
        {
            register int R = node.pos / n + dr[d];
            register int C = node.pos % n + dc[d];
            if (R >= 0 && R < n && C >= 0 && C < n && !visited[R][C])
            {
                if (!bacteria[R][C])
                {
                    visited[R][C] = true;
                    register Node new_node = { energy[R][C], R * n + C };
                    pq.emplace(new_node);
                }
                else if (bacteria[R][C] == mTarget)                 // 종류가 같은 세균 존재 시 연결된 세균들 모두 활성화하고
                    activateBacteria(visited, R, C, mTarget);       // 인접한 비어있는 셀 모두 pq에 삽입
            }
        }
    }
    
    return bacteriaNum[mTarget];
}

int cleanBacteria(int mRow, int mCol)
{
    mRow--, mCol--;
    if (!bacteria[mRow][mCol])                      // 셀이 비어있는 곳에 약품 떨어뜨리면 소멸 진행 안하고 종료
        return -1;

    register int target = bacteria[mRow][mCol];

    q.emplace(mRow * n + mCol);
    bacteria[mRow][mCol] = 0;

    while (!q.empty())
    {
        register int cur = q.front();
        q.pop();

        bacteriaNum[target]--;

        for (register int d = 0; d < 4; d++)
        {
            register int R = cur / n + dr[d];
            register int C = cur % n + dc[d];
            if (R >= 0 && R < n && C >= 0 && C < n && bacteria[R][C] == target)
            {
                q.emplace(R * n + C);
                bacteria[R][C] = 0;
            }
        }
    }
    
    return bacteriaNum[target];
}
