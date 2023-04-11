#include <iostream>
using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int num;
    string sentence, word;
    for (int t = 1; t <= 10; t++)
    {
        int ans = 0;

        cin >> num >> word >> sentence;
        
        for (int i = 0; i <= sentence.length() - word.length(); i++)
        {
            bool find = true;
            for (int j = 0; j < word.length(); j++)
            {
                if (sentence[i + j] != word[j])
                {
                    find = false;
                    break;
                }
            }
            if (find) ans++;
        }

        cout << '#' << t << ' ' << ans << '\n';
    }

    return 0;
}