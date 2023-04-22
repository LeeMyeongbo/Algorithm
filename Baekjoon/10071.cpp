#include "game.h"

int U[1500], C[1500];           // U : 각 정점이 어느 집합에 속해있는지, C : i번 정점을 몇 번 연결 시도했는지 저장

bool query(int u, int v)        // i번 정점을 i번 연결 시도했을 때 비로소 연결
{
    return ++C[u > v ? u : v] == (u > v ? u : v);
}

int getUnion(int v)
{
    if (U[v] == v)
        return v;
    
    return U[v] = getUnion(U[v]);
}

void merge(int u, int v)
{
    u = getUnion(u);
    v = getUnion(v);

    U[u] = v;
}

void initialize(int n) 
{
    for (int i = 0; i < n; i++)
        U[i] = i;
}

int hasEdge(int u, int v) 
{
    if (query(u, v) && getUnion(u) != getUnion(v))
    {
        merge(u, v);
        return 1;
    }
    return 0;
}