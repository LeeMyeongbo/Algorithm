#include <iostream>
#include <vector>
using namespace std;

string passage, word;

vector<int> getCommonpresuffix()        // 찾고자 하는 단어(word)의 최장공통 접두ㆍ접미사의 길이를 각 index마다 저장
{
    int l = word.length(), cur = 0;
    vector<int> len(l);

    for (int i = 1; i < l; ) {
        if (word[i] == word[cur])       // i번째 글자와 cur번째 글자가 같다면 현재까지의 공통접두ㆍ접미사 길이 + 1해서 저장
            len[i++] = ++cur;
        else {
            if (cur)
                cur = len[cur - 1];     // 같지 않다면 cur 길이를 현재까지의 공통접두ㆍ접미사 길이 - 1 만큼으로 맞춤
            else
                i++;
        }
    }

    return len;
}

vector<int> kmp()
{
    int l = passage.length(), cur = 0;
    vector<int> ans, len = getCommonpresuffix();

    for (int i = 0; i < l; ) {
        if (passage[i] == word[cur]) {
            i++, ++cur;
            if (cur == word.length()) {     // 찾고자 하는 단어를 찾았을 경우
                ans.push_back(i - cur);     // 답 저장하고
                cur = len[cur - 1];         // 적절하게 건너뜀
            }
        }
        else {
            if (cur)
                cur = len[cur - 1];
            else
                i++;
        }
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cout << "본문\n";
    cin >> passage;
    cout << "찾는 단어\n";
    cin >> word;

    vector<int> ans = kmp();

    cout << "찾는 단어의 시작 index\n";
    for (int i : ans)
        cout << i << ' ';

    return 0;
}
