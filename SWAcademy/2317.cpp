#include <iostream>
#include <vector>
using namespace std;

int query[100000];

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    register int T, N, Q, special, sum, a;
    cin >> T;

    for (register int test_case = 1; test_case <= T; test_case++)
    {
        vector<int> a_i;
        sum = 0;

        cin >> N;
        for (register int i = 0; i < N; i++)
        {
            cin >> a;
            a_i.push_back(a);
            sum += a;
        }

        cin >> Q;
        for (register int q = 0; q < Q; q++)
        {
            cin >> query[q];
            query[q]--;
        }

        for (register int i = N; ; i++)
        {
            bool complete = true;
            a = sum / N;
            a_i.push_back(a);

            for (register int j = i - 1; j > i - N; j--)
            {
                if (a_i[i] != a_i[j])
                {
                    complete = false;
                    break;
                }
            }

            if (complete)
            {
                special = i;
                break;
            }

            sum -= a_i[i - N];
            sum += a_i[i];
        }

        for (register int q = 0; q < Q; q++)
        {
            if (query[q] < special)
                cout << a_i[query[q]] << ' ';
            else
                cout << a_i[special] << ' ';
        }
        cout << '\n';
    }

    return 0;
}
