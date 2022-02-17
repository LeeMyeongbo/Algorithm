#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int T, N;
string name;

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        vector<pair<int, string>> names;
        cin >> N;
        for (int i = 0; i < N; i++) {
            cin >> name;
            names.push_back({ name.length(), name });
        }
        sort(names.begin(), names.end());

        cout << '#' << test_case << "\n";

        string pre = "";
        for (auto& n : names) {
            if (pre != n.second)
                cout << n.second << "\n";
            pre = n.second;
        }
    }
    return 0;
}
