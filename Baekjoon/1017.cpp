#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> graph[50], ans;
int N, num[50], conn[50];
bool not_prime[2000], complete[50];

void get_Prime()                            // 에라토스테네스의 체 -> 소수 판별
{
    for (int i = 2; i * i < 2000; i++)
        if (!not_prime[i])
            for (int j = i * i; j < 2000; j += i)
                not_prime[j] = true;
}

bool dfs(int cur)                           // 이분 매칭
{
    for (int i : graph[cur]) {
        if (complete[i])
            continue;

        complete[i] = true;
        if (!conn[i] || dfs(conn[i])) {
            conn[i] = cur;
            return true;
        }
    }
    return false;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    get_Prime();

    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> num[i];

    for (int i = 0; i < N - 1; i++)
        for (int j = i + 1; j < N; j++)
            if (!not_prime[num[i] + num[j]]) {      // 합치면 소수가 되는 것끼리만 연결하여 그래프 형성
                graph[i].push_back(j);
                graph[j].push_back(i);
            }

    for (int s : graph[0]) {                        // 0번 정점(첫 번째 숫자)과 연결된 모든 정점을 한 번씩 매칭함
        bool possible = true;
        fill(conn, conn + N, 0);
        conn[s] = 0, conn[0] = s;

        for (int i = 1; i < N; i++) {
            fill(complete, complete + N, false);
            complete[0] = complete[s] = true;       // 반드시 0번 정점과 매칭된 정점 모두 완료 처리

            if (i != s && !dfs(i)) {                // i가 s와 같지도 않은데 매칭에 실패하면 짝지을 수 없음
                possible = false;
                break;
            }
        }
        if (possible)
            ans.push_back(s);
    }

    auto cmp = [](int i, int j) -> bool {
        return num[i] < num[j];
    };
    sort(ans.begin(), ans.end(), cmp);

    if (ans.empty())
        cout << -1;
    else
        for (int i : ans)
            cout << num[i] << ' ';
    cout << '\n';
    return 0;
}
