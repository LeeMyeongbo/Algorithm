#include <iostream>
#include <string>
using namespace std;

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    register int T;
    register string str;

    cin >> T;

    for (register int test_case = 1; test_case <= T; ++test_case)
    {
        cin >> str;
        cout << '#' << test_case << ' ';

        register int len = str.length();
        register int n1 = atoi(str.substr(0, len >> 1).c_str()), n2 = atoi(str.substr(len >> 1, (len >> 1) + 1).c_str());

        if (len & 1)       // str의 길이가 홀수라면
        {
            register int n3 = atoi(str.substr(0, (len >> 1) + 1).c_str()), n4 = atoi(str.substr((len >> 1) + 1, len >> 1).c_str());
            cout << min(n1 + n2, n3 + n4) << '\n';
        }
        else
            cout << n1 + n2 << '\n';
    }

    return 0;
}
