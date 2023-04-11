#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int len;
    string str[8];

	for(int t = 0; t < 10; t++)
	{
        int ans = 0;

        cin >> len;
        for (int i = 0; i < 8; i++)
            cin >> str[i];
        
        if (len != 1)
        {
            int limit = len >> 2 - 1;
            for (int r = 0; r < 8; r++)     // 가로 회문들 먼저 구함
            {
                for (int c = 0; c <= 8 - len; c++)
                {
                    int start = c, end = start + len - 1;
                    bool find = true;
                    for (int f = 0; f <= limit; f++)
                    {
                        if (str[r][start + f] != str[r][end - f])
                        {
                            find = false;
                            break;
                        }
                    }
                    if (find) ans++;
                }
            }

            for (int c = 0; c < 8; c++)     // 세로 회문들 구함
            {
                for (int r = 0; r <= 8 - len; r++)
                {
                    int start = r, end = start + len - 1;
                    bool find = true;
                    for (int f = 0; f <= limit; f++)
                    {
                        if (str[start + f][c] != str[end - f][c])
                        {
                            find = false;
                            break;
                        }
                    }
                    if (find) ans++;
                }
            }
            cout << '#' << t + 1 << ' ' << ans << '\n';
        }
        else
            cout << '#' << t + 1 << ' ' << 64 << '\n';
	}
	return 0;
}