#include <string.h>

extern bool checkCards(int mIndexA, int mIndexB, int mDiff);

int cmp[50000][4];                  // cmp[diff] : cards[0]와 diff만큼 차이나는 index들(2개 or 4개) 저장
int cnt[50000];                     // cnt[diff] : cards[0]와 diff만큼 차이나는 카드 개수

void playGame(int N)
{
    for (register int i = 0; i < (N << 1); i++)
    {
        register int left = 0, right = N - 1, mid = 0, ans = 0;
        while (left <= right)
        {
            mid = (left + right) >> 1;
            if (checkCards(0, i, mid))
            {
                ans = mid;
                right = mid - 1;
            }
            else
                left = mid + 1;
        }
        cmp[ans][cnt[ans]++] = i;
    }

    for (register int i = 0; i < N; i++)
    {
        if (cnt[i] == 2)
            checkCards(cmp[i][0], cmp[i][1], 0);
        else if (cnt[i] == 4)
        {
            if (checkCards(cmp[i][0], cmp[i][1], 0))
                checkCards(cmp[i][2], cmp[i][3], 0);
            else if (checkCards(cmp[i][0], cmp[i][2], 0))
                checkCards(cmp[i][1], cmp[i][3], 0);
            else if (checkCards(cmp[i][0], cmp[i][3], 0))
                checkCards(cmp[i][1], cmp[i][2], 0);
        }
        else
            break;
    }

    memset(cmp, 0, sizeof(int) * N * 4);
    memset(cnt, 0, sizeof(int) * N);

    return;
}
