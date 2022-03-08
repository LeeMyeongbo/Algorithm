#include <iostream>
//#include <fstream>
#include <algorithm>
using namespace std;

int T, L, sa[200000], isa[200000], ranking[200000];     // sa[i] : 사전 순위가 i번째인 접미사의 index
string S;                                               // isa[i] : index가 i인 접미사의 사전 순위
pair<int, int> sr[200000];                              // sr[i] : (i번째 접미사의 순위, i + d/2 번째 접미사의 순위)

bool cmp(int a, int b)
{
    return sr[a] < sr[b];
}

int solve()
{
    for (int i = 0; i < L; i++) {
        sa[i] = i;
        ranking[i] = S[i] - 'a' + 1;            // 각 문자마다 ranking 저장
    }

    for (int d = 2; d < L; d = d << 1) {        // d는 2, 4, 8, ... 이렇게 진행
        for (int i = 0; i < L; i++) {           // i번째 접미사와 i + d/2 번째 접미사의 순서를 저장
            if (i + d / 2 < L)
                sr[i] = { ranking[i], ranking[i + d / 2] };
            else
                sr[i] = { ranking[i], 0 };
        }
        sort(sa, sa + L, cmp);                  // sa 사전순으로 오도록 정렬

        ranking[sa[0]] = 1;
        for (int i = 1; i < L; i++)
            ranking[sa[i]] = sr[sa[i]] == sr[sa[i - 1]] ? ranking[sa[i - 1]] : ranking[sa[i - 1]] + 1;
    }
    
    for (int i = 0; i < L; i++)
        isa[sa[i]] = i;

    int ans = 0;
    for (int pos = 0, i = 0; i < L; i++) {          // 가장 긴 접미사부터 진행
        if (!isa[i])                                // 사전순으로 가장 앞서는 접미사는 제외
            continue;
        int pre = sa[isa[i] - 1];                   // i번 접미사보다 사전순으로 바로 앞에 있는 접미사의 index 구함

        while (i + pos < L && pre + pos < L && S[i + pos] == S[pre + pos])      // kasai algorithm
            pos++;                                  // 각 접미사와 사전순으로 바로 앞에 있는 접미사를 비교하며
                                                    // 공통 접두사 길이만큼 pos 증가
        ans = max(ans, pos);                        // pos의 최댓값 = 2번 이상 나타나는 최장 부분문자열의 길이
        if (pos)
            pos--;                                  // 다음 i+1번 접미사로 진행할 땐 공통 접두사 길이가 최소 pos-1부터 시작
    }

    return ans;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    //ifstream fin;
    //fin.open("C:/Users/myeon/Downloads/input.txt");

    cin >> T;
    //fin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> L >> S;
        //fin >> L >> S;

        cout << '#' << test_case << ' ' << solve() << '\n';
        for (int i = 0; i < L; i++)
            sr[i] = { 0, 0 };
    }
    return 0;
}
