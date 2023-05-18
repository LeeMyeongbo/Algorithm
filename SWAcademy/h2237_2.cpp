#include <string.h>
#define MAX_N 100

struct Node {
    int e, pos;                 // pos = row * n + col
} cell[10000];                  // 힙에 저장된 포인터가 참조하는 실제 데이터 저장
const int dr[] = { 0, 1, 0, -1 }, dc[] = { 1, 0, -1, 0 };           // 동 남 서 북 순서
int n, bacteriaNum[3], energy[MAX_N][MAX_N], bacteria[MAX_N][MAX_N], heapSize, cellCnt;
Node* heap[10000];

void init(int N, int mDish[MAX_N][MAX_N])
{
    n = N;
    memcpy(energy, mDish, sizeof(energy));
    memset(bacteria, 0, sizeof(bacteria));
    bacteriaNum[1] = bacteriaNum[2] = 0;
}

void heapPush(Node* node)
{
    heap[++heapSize] = node;

    register int cur = heapSize, par = cur >> 1;
    while (par)
    {
        if (heap[cur]->e > heap[par]->e || (heap[cur]->e == heap[par]->e && heap[cur]->pos < heap[par]->pos))
        {
            register Node* tmp = heap[cur];
            heap[cur] = heap[par];
            heap[par] = tmp;
        }
        else
            break;

        cur = par, par >>= 1;
    }
}

Node* heapPop()
{
    register Node* top = heap[1];
    heap[1] = heap[heapSize--];

    register int cur = 1, chi = 2;
    while (chi <= heapSize)
    {
        if (chi + 1 <= heapSize && (heap[chi]->e < heap[chi + 1]->e || (heap[chi]->e == heap[chi + 1]->e && heap[chi]->pos > heap[chi + 1]->pos)))
            chi++;

        if (heap[cur]->e < heap[chi]->e || (heap[cur]->e == heap[chi]->e && heap[cur]->pos > heap[chi]->pos))
        {
            register Node* tmp = heap[cur];
            heap[cur] = heap[chi];
            heap[chi] = tmp;
        }
        else
            break;

        cur = chi, chi <<= 1;
    }

    return top;
}

void activateBacteria(bool visited[MAX_N][MAX_N], int r, int c, int target)
{
    for (register int d = 0; d < 4; d++)
    {
        register int R = r + dr[d];
        register int C = c + dc[d];
        if (R >= 0 && R < n && C >= 0 && C < n && !visited[R][C])
        {
            visited[R][C] = true;
            if (bacteria[R][C] == target)                           // 종류가 같은 세균이 있을 경우 큐 저장(활성화)
                activateBacteria(visited, R, C, target);
            else if (!bacteria[R][C])                               // 비어있는 셀은 pq에 저장(인접한 셀로 번식하기 위함)
            {
                cell[cellCnt] = { energy[R][C], R * n + C };
                heapPush(cell + cellCnt++);
            }
        }
    }
}

void removeBacteria(int r, int c, int target)
{
    bacteriaNum[target]--;
    for (register int d = 0; d < 4; d++)
    {
        register int R = r + dr[d];
        register int C = c + dc[d];
        if (R >= 0 && R < n && C >= 0 && C < n && bacteria[R][C] == target)
        {
            bacteria[R][C] = 0;
            removeBacteria(R, C, target);
        }
    }
}

int dropMedicine(int mTarget, int mRow, int mCol, int mEnergy)
{
    mRow--, mCol--;
    if (bacteria[mRow][mCol] && bacteria[mRow][mCol] != mTarget)    // 다른 종류의 세균 존재 시 종료
        return bacteriaNum[mTarget];

    cellCnt = 0, heapSize = 0;
    bool visited[MAX_N][MAX_N] = { false, };

    visited[mRow][mCol] = true;
    if (bacteria[mRow][mCol])                                       // 같은 종류 세균 존재 시 연결된 세균들 모두 활성화하고
        activateBacteria(visited, mRow, mCol, mTarget);             // 거기에 인접한 비어있는 셀 모두 pq에 삽입
    else                                                            // 세균 없으면 pq에 바로 삽입
    {
        cell[cellCnt] = { energy[mRow][mCol], mRow * n + mCol };
        heapPush(cell + cellCnt++);
    }

    while (heapSize)                                                // 세균 번식
    {
        register Node node = *heapPop();

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
                    cell[cellCnt] = { energy[R][C], R * n + C };
                    heapPush(cell + cellCnt++);
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
    bacteria[mRow][mCol] = 0;
    removeBacteria(mRow, mCol, target);

    return bacteriaNum[target];
}
