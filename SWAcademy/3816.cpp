#include <iostream>
using namespace std;

int T;
string s1, s2;

bool is_anagram(int a[], int b[])
{
    for (int i = 0; i < 26; i++)
        if (a[i] != b[i])
            return false;
    return true;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        int s1_char[26] = { 0, }, s2_char[26] = { 0, }, ans = 0;
        cin >> s1 >> s2;

        for (int i = 0; i < s1.length() - 1; i++) {
            s1_char[s1[i] - 'a']++;
            s2_char[s2[i] - 'a']++;
        }
        s1_char[s1.back() - 'a']++;

        for (int i = s1.length() - 1; i < s2.length(); i++) {
            s2_char[s2[i] - 'a']++;

            if (is_anagram(s1_char, s2_char))
                ans++;

            s2_char[s2[i - s1.length() + 1] - 'a']--;
        }

        cout << '#' << test_case << ' ' << ans << "\n";
    }
    return 0;
}
