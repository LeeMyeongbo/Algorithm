#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cmath>
using namespace std;

int tree[1 << 21], S;

int getSum(int index, int start, int end, int left, int right)      // 해당 [start, end] 구간의 행 개수의 합 구함
{
    if (left > end || right < start)
        return 0;
    if (left >= start && right <= end)
        return tree[index];

    return getSum(index * 2, start, end, left, (left + right) / 2) + getSum(index * 2 + 1, start, end, (left + right) / 2 + 1, right);
}

int left_search(int sum, int k, int left, int right)    // x(0 <= x < k)부터 k-1까지의 행 개수 합이 sum을 만족하는 가장 큰 x 구함
{
    int ans = 0;
    while (left <= right) {
        int mid = (left + right) / 2;
        int Sum = getSum(1, mid, k - 1, 0, S - 1);
        if (Sum >= sum) {
            ans = mid;
            left = mid + 1;
        }
        else
            right = mid - 1;
    }
    return ans;
}

int right_search(int sum, int k, int left, int right)   // k+1부터 x(k < x < n)까지의 행 개수 합이 sum을 만족하는 가장 작은 x 구함
{
    int ans = 0;
    while (left <= right) {
        int mid = (left + right) / 2;
        int Sum = getSum(1, k + 1, mid, 0, S - 1);
        if (Sum >= sum) {
            ans = mid;
            right = mid - 1;
        }
        else
            left = mid + 1;
    }
    return ans;
}

string solution(int n, int k, vector<string> cmd) {
    string answer = "";
    stack<int> s;
    S = 1 << (int)ceil(log2(n));
    for (int i = S; i < n + S; i++)                 // 말단노드 [S, n + S) 중에서 삭제된 것은 0, 삭제 안 된 건 1로 저장
        tree[i] = 1;

    for (int i = S - 1; i > 0; i--)
        tree[i] = tree[i * 2] + tree[i * 2 + 1];
    
    for (string c : cmd) {
        if (c[0] == 'U' || c[0] == 'D') {
            string X;
            X.assign(c, 2, c.length() - 2);
            int x = stoi(X);

            k = c[0] == 'U' ? left_search(x, k, 0, k - 1) : right_search(x, k, k + 1, n - 1);
        }
        else if (c[0] == 'C') {
            int idx = S + k;
            while (idx) {
                tree[idx]--;
                idx /= 2;
            }
            s.push(k);

            if (!getSum(1, k + 1, S - 1, 0, S - 1))         // 마지막 행을 삭제했을 경우 
                k = left_search(1, k, 0, k - 1);            // k 이전 행들 중에서 k와 가장 가까운 이전 행 탐색
            else                                            // k 이후 행들이 남아있을 경우
                k = right_search(1, k, k + 1, n - 1);       // k 이후 행들 중에서 k와 가장 가까운 이후 행 탐색
        }
        else {
            int rollback = s.top();
            int idx = S + rollback;
            while (idx) {
                tree[idx]++;
                idx /= 2;
            }
            s.pop();
        }
    }

    for (int i = S; i < n + S; i++) {
        if (tree[i])
            answer.push_back('O');
        else
            answer.push_back('X');
    }

    return answer;
}

int main()
{
    int n, k, c;
    string cm, X;
    vector<string> cmd;

    cin >> n >> k >> c;
    while (c--) {
        cin >> cm;
        if (cm == "U" || cm == "D") {
            cin >> X;
            cm.append(" ");
            cm.append(X);
        }
        cmd.push_back(cm);
    }

    cout << solution(n, k, cmd);

    return 0;
}
