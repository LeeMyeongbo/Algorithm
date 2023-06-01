#define SIZE 10000000

int bucket[128][SIZE / 80];
int front[128], rear[128];

void sort(double* arr, int n)
{
    for (register int i = 1; ; i *= 100)
    {
        register int p = -1;

        if (i == 1000000)
        {
            for (register int j = 0; j < n; ++j)
            {
                register int num = (int)(arr[j] * 128);
                bucket[num / i % 128][rear[num / i % 128]++] = num;
            }

            for (register int j = 0; j < 128; ++j)
            {
                while (front[j] != rear[j])
                    arr[++p] = (double)bucket[j][front[j]++] / 128;

                front[j] = rear[j] = 0;
            }

            break;
        }
        for (register int j = 0; j < n; ++j)
        {
            register int num = (int)(arr[j] * 128);
            bucket[num / i % 100][rear[num / i % 100]++] = num;
        }

        for (register int j = 0; j < 100; ++j)
        {
            while (front[j] != rear[j])
                arr[++p] = (double)bucket[j][front[j]++] / 128;

            front[j] = rear[j] = 0;
        }
    }
}
