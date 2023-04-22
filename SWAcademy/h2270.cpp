#include <string.h>

struct Node {
    int Max, Min, cnt;          // cnt : 구간 내 수의 개수
} tree[1 << 19];
int n, S = 1 << 18;

void updateTree(int start, int num, int mValue[])
{
    for (int i = 0; i < num; i++)
    {
        int idx = S + i + start;
        tree[idx] = { mValue[i], mValue[i], 1 };

        idx >>= 1;
        while (idx)
        {
            tree[idx].cnt++;

            int left_cnt = tree[idx << 1].cnt;
            int right_cnt = tree[(idx << 1) + 1].cnt;
            int left_Max = tree[idx << 1].Max;
            int right_Max = tree[(idx << 1) + 1].Max;
            int left_Min = tree[(idx << 1)].Min;
            int right_Min = tree[(idx << 1) + 1].Min;

            tree[idx].Max = left_Max > right_Max ? left_Max : right_Max;

            if (left_cnt && right_cnt)
                tree[idx].Min = left_Min > right_Min ? right_Min : left_Min;
            else if (left_cnt)
                tree[idx].Min = tree[idx << 1].Min;
            else if (right_cnt)
                tree[idx].Min = tree[(idx << 1) + 1].Min;

            idx >>= 1;
        }
    }
}

Node search(int index, int left, int right, int r1, int r2)
{
    if (left > r2 || right < r1)
        return { 0, 0, 0 };

    if (left >= r1 && right <= r2)
        return tree[index];

    Node n1 = search(index << 1, left, (left + right) >> 1, r1, r2);
    Node n2 = search((index << 1) + 1, ((left + right) >> 1) + 1, right, r1, r2);

    int Max = n1.Max > n2.Max ? n1.Max : n2.Max;
    int Min = 0;
    if (n1.cnt && n2.cnt)
        Min = n1.Min > n2.Min ? n2.Min : n1.Min;
    else if (n1.cnt)
        Min = n1.Min;
    else if (n2.cnt)
        Min = n2.Min;

    return { Max, Min, n1.cnt + n2.cnt };
}

void init(int N, int mValue[])
{
    memset(tree, 0, sizeof(tree));

    updateTree(0, N, mValue);
    n = N;
}

void add(int M, int mValue[])
{
    updateTree(n, M, mValue);
    n += M;
}

void erase(int mFrom, int mTo)                  // mFrom이 실제로 어느 index를 가리키는 지 찾아서 삭제
{
    for (int i = mFrom; i <= mTo; i++)
    {
        int index = 1, real_idx = mFrom;

        while (index < S)
        {
            if (tree[index << 1].cnt >= real_idx)   // 왼쪽 서브트리에 있는 수의 개수가 mFrom 이상이면 그대로 왼쪽 자식으로 이동
                index <<= 1;
            else                                    // 그렇지 않다면 오른쪽 자식으로 이동하면서
            {
                real_idx -= tree[index << 1].cnt;   // 왼쪽 서브트리에 있는 수의 개수를 뺀 만큼 적용
                index = (index << 1) + 1;
            }
        }

        tree[index] = { 0, 0, 0 };
        index >>= 1;

        while (index)
        {
            tree[index].cnt--;

            int left_cnt = tree[index << 1].cnt;
            int right_cnt = tree[(index << 1) + 1].cnt;
            int left_Max = tree[index << 1].Max;
            int right_Max = tree[(index << 1) + 1].Max;
            int left_Min = tree[(index << 1)].Min;
            int right_Min = tree[(index << 1) + 1].Min;

            tree[index].Max = left_Max > right_Max ? left_Max : right_Max;

            if (left_cnt && right_cnt)
                tree[index].Min = left_Min > right_Min ? right_Min : left_Min;
            else if (left_cnt)
                tree[index].Min = tree[index << 1].Min;
            else if (right_cnt)
                tree[index].Min = tree[(index << 1) + 1].Min;

            index >>= 1;
        }
    }
}

int find(int K)
{
    int index = 1, real_idx = K;

    while (index < S)
    {
        if (tree[(index << 1) + 1].cnt >= real_idx)
            index = (index << 1) + 1;
        else
        {
            real_idx -= tree[(index << 1) + 1].cnt;
            index = index << 1;
        }
    }

    Node ans = search(1, 1, S, index - S + 1, n);

    return ans.Max - ans.Min;
}
