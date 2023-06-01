#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#define SIZE 10000000

extern void sort(double* out, int n);

double g_arr[SIZE];

static int seed;
static unsigned int pseudo_rand(void) {
    seed = seed * 214013 + 2531011;
    return (seed >> 16) & 0x7FFF;
}

void init(double* arr, int n) {
    for (register int i = 0; i < n; i++) {
        arr[i] = 0.0078125 * (pseudo_rand() % 128);
        arr[i] += (pseudo_rand() + pseudo_rand() * 32768) % 1000000;
    }
}

double get_result(double* arr, int n) {
    double ret = 0;
    for (register int i = 0; i < n; i += 4) {
        ret += arr[i];
        ret -= arr[i + 1];
        ret -= arr[i + 2];
        ret += arr[i + 3];
    }
    return ret;
}

double answer[10] = {
  -169.0312500,
  7.7968750,
  376.8046875,
  99.7968750,
  47.7968750,
  -63.1562500,
  239.2421875,
  -327.4609375,
  109.3203125,
  -436.3515625
};

int main() {
    scanf("%d", &seed);
    int SCORE = 0;

    clock_t start = clock();
    for (int T = 0; T < 10; T++) {
        init(g_arr, SIZE);
        sort(g_arr, SIZE);

        const double result = get_result(g_arr, SIZE);
        if (result == answer[T]) {
            SCORE += 10;
        }
        else {
            printf("T: %d, result: %.7lf\n", T, result);
        }
    }
    
    printf("SCORE: %d\n", SCORE);
    printf("Time : %f\n", (double)(clock() - start));
    return 0;
}
