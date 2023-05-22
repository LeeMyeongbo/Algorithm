#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

string S;

vector<int> getSuffixArray(int l)
{
    vector<int> sa(l), rank(l);         // sa : 각 접미사들의 번호 저장, rank : 각 접미사들의 사전 순서 저장
    vector<pair<int, int>> sr(l);       // (i번 index로 시작하는 접미사의 사전 순서, i+d/2번 index로 시작하는 접미사의 사전 순서)

    for (int i = 0; i < l; i++) 
    {
        sa[i] = i;
        rank[i] = S[i] - 'a' + 1;
    }

    for (int d = 2; d < l; d = d << 1)  // d=2, 4, 8... 순으로 진행
    {
        for (int i = 0; i < l; i++) 
        {
            if (i + d / 2 < l)
                sr[i] = { rank[i], rank[i + d / 2] };
            else
                sr[i] = { rank[i], 0 };
        }

        auto cmp = [&sr](int a, int b) -> bool {
            return sr[a] < sr[b];
        };

        sort(sa.begin(), sa.end(), cmp);    // sr에 저장된 (rank[i], rank[i + d / 2])에 따라 sa 정렬

        rank[sa[0]] = 0;
        for (int i = 1; i < l; i++)
            rank[sa[i]] = sr[sa[i]] == sr[sa[i - 1]] ? rank[sa[i - 1]] : rank[sa[i - 1]] + 1;
    }

    return sa;
}

vector<int> getLCPArray(vector<int>& sa, int l)     // kasai algorithm
{                                                   // sa[i] : 사전순으로 i번째인 접미사의 시작 index
    vector<int> isa(l), lcp(l);                     // isa[i] : i번 index로 시작하는 접미사의 사전적 순위

    for (int i = 0; i < l; i++)
        isa[sa[i]] = i;

    for (int len = 0, i = 0; i < l; i++) 
    {
        if (!isa[i])
            continue;                               // 사전적으로 가장 빠른 접미사는 skip
        
        int pre = sa[isa[i] - 1];                   // pre : 현재 i번 index로 시작하는 접미사보다 사전적으로 바로 앞에 있는 접미사의 index
        while (i + len < l && pre + len < l && S[i + len] == S[pre + len])
            len++;

        lcp[isa[i]] = len ? len-- : 0;      // len이 자연수라면 -1
    }

    return lcp;
}

int main()
{
    cin >> S;

    int l = S.length();
    vector<int> sa = getSuffixArray(l);
    vector<int> lcp = getLCPArray(sa, l);

    cout << "\n접미사 순서 및 최장 공통 접두사 길이\n";
    for (int i = 0; i < l; i++) 
    {
        for (int j = sa[i]; j < l; j++)
            cout << S[j];
        cout << ' ' << lcp[i] << '\n';
    }

    return 0;
}
