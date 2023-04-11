#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

vector<pair<long long, long long>> tree;        // first는 실제 값, second는 변화량

long long init(int left, int right, int index)
{
    if (left == right) 
        return tree[index].first;
    
    int mid = left + right >> 1;
    return tree[index].first = init(left, mid, index << 1) + init(mid + 1, right, (index << 1) + 1);
}

void prop(int left, int right, int index)                   // 추후에 반영하겠다고 표시해 뒀던 diff를 자식 노드들에게 전파
{
    if (tree[index].second)
    {
        tree[index].first += (right - left + 1) * tree[index].second;
        if (left != right)
        {
            tree[index << 1].second += tree[index].second;
            tree[(index << 1) + 1].second += tree[index].second;
        }
        tree[index].second = 0;
    }
}

long long search(int left, int right, int range1, int range2, int index)
{
    prop(left, right, index);
    if (left > range2 || right < range1)
        return 0;
    
    if (left >= range1 && right <= range2)
        return tree[index].first;
    
    int mid = left + right >> 1;
    return search(left, mid, range1, range2, index << 1) + search(mid + 1, right, range1, range2, (index << 1) + 1);
}

void update(int left, int right, int range1, int range2, int index, int diff)
{
    prop(left, right, index);
    if (left > range2 || right < range1)
        return;
    
    if (left >= range1 && right <= range2)                  // 현 탐색 범위가 원하는 구간 내 포함될 경우
    {
        tree[index].first += diff * (right - left + 1);     // 먼저 해당 노드 값에 변화량 반영
        if (left != right)                                  // 자식이 있는 경우 추후에 diff 반영하겠다고 표시
        {
            tree[index << 1].second += diff;
            tree[(index << 1) + 1].second += diff;
        }
        return;
    }

    int mid = left + right >> 1;
    update(left, mid, range1, range2, index << 1, diff);
    update(mid + 1, right, range1, range2, (index << 1) + 1, diff);
    tree[index].first = tree[index << 1].first + tree[(index << 1) + 1].first;
}

int main()
{
    int N, choice, r1, r2, change;
    cin >> N;

    int S = 1 << (int)ceil(log2(N));
    tree.resize(S << 1, {0, 0});

    for (int i = 0; i < N; i++)
        cin >> tree[S + i].first;
    
    init(1, S, 1);

    while (true)
    {
        cout << "1 입력 시 구간합, 2 입력 시 트리 수정 : ";
        cin >> choice;

        if (cin.eof())
            return 0;
        
        if (choice == 1)
        {
            cout << "구간 입력 : ";
            cin >> r1 >> r2;

            cout << search(1, S, r1, r2, 1) << '\n';
        }
        else
        {
            cout << "수정할 구간 + 구간 내 각 값마다의 변화량 입력 : ";
            cin >> r1 >> r2 >> change;

            update(1, S, r1, r2, 1, change);
        }
    }
}