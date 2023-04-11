#include <iostream>
#include <map>
using namespace std;

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    string str, keys[10] = { "ZRO", "ONE", "TWO", "THR", "FOR", "FIV", "SIX", "SVN", "EGT", "NIN" };
    map<string, int> val;
    int T, test;
    char c;

    cin >> T;

    for (int i = 0; i < 10; i++)
        val[keys[i]] = i;

    for (int test_case = 1; test_case <= T; ++test_case) 
    {
        int num[10] = {0, }, N;
        cin >> c >> test >> N;
        
        for (int i = 0; i < N; i++)         // counting sort
        {
            cin >> str;
            num[val[str]]++;
        }

        cout << '#' << test_case << "\n";
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < num[i]; j++)
                cout << keys[i] << ' ';
        
        cout << '\n';
    }

    return 0;
}
