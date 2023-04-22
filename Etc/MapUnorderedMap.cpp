#include <iostream>
#include <map>
#include <unordered_map>
#include <time.h>
using namespace std;

map<int, int> mapping;
unordered_map<int, int> omapping;

int main()
{
    clock_t start = clock();
    for (int i = 0; i < 2000000; i++)
        mapping[i] = i + 1;
    
    for (int i = 0; i < 2000000; i++)
        int n = mapping[i];
    clock_t end = clock();

    cout << "map duration : " << (double)(end - start) / CLOCKS_PER_SEC << '\n';

    start = clock();
    for (int i = 0; i < 2000000; i++)
        omapping[i] = i + 1;
    
    for (int i = 0; i < 2000000; i++)
        int n = omapping[i];
    end = clock();

    cout << "unordered_map duration : " << (double)(end - start) / CLOCKS_PER_SEC << '\n';

    return 0;
}