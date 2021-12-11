#include <stdio.h>
#include <stdlib.h>

typedef struct Data {
    int data, address;
} Data;

typedef struct Cache {
    int valid, dirt, tag, top;
    Data* arr;
} Cache;

int main()
{
    int cacheindex = 10;
    int set_size = 2;
    Cache** cache = NULL;
    int block_size = 8;

    if (!(cache = (Cache**)malloc(sizeof(Cache*) * cacheindex)))
        return 1;

    for (int i = 0; i < cacheindex; i++) {
        if (!(cache[i] = (Cache*)calloc(set_size, sizeof(Cache))))
            return 1;

        for (int j = 0; j < set_size; j++)
        {
            cache[i][j].valid = cache[i][j].dirt = cache[i][j].tag = 0;
            cache[i][j].top = -1;
            cache[i][j].arr = NULL;

            if (!(cache[i][j].arr = (Data*)calloc(block_size / 4, sizeof(Data))))
                return 1;

            for (int k = 0; k < block_size / 4; k++)
                cache[i][j].arr[k].data = cache[i][j].arr[k].address = 0;
        }
    }
    for (int i = 0; i < cacheindex; i++) {
        for (int j = 0; j < set_size; j++) {
            printf("cache[%d][%d] : valid=%d, dirt=%d, tag=%d\n", i, j, cache[i][j].valid, cache[i][j].dirt, cache[i][j].tag);
            printf("cache[%d][%d]'s arr\n", i, j);

            for (int k = 0; k < block_size / 4; k++)
                printf("arr[%d] : data=%d, address=%d\n", k, cache[i][j].arr[k].data, cache[i][j].arr[k].address);

            printf("\n");
            free(cache[i][j].arr);
        }
        free(cache[i]);
    }
    free(cache);

    return 0;
}