#include <iostream>
using namespace std;

bool findPattern(string str, string pattern)
{
    for (int i = 0; i < (int)(str.length() - pattern.length()); i++)
    {
        bool find = true;
        for (int j = 0; j < (int)pattern.length(); j++)
        {
            if (str[i + j] != pattern[j])
            {
                find = false;
                break;
            }
        }
        if (find) return true;
    }
    return false;
}

int main()
{
    string str, pattern;
    cin >> str >> pattern;

    findPattern(str, pattern) ? cout << "발견!" : cout << "없음!";

    return 0;
}