#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> graph[26];
string str[100];
bool appear[26];        // 나타난 알파벳들 저장
int N, inorder[26];

void topological()
{
    vector<char> ans;
    bool multiple = false;                  // 가능한 정렬이 여러 개 있는지 판별
    queue<int> q;
    for (int i = 0; i < 26; i++) {
        if (appear[i] && !inorder[i])       // 목록에 나타난 알파벳들 중 진입차수가 0인 알파벳 큐에 저장
            q.push(i);
    }

    while(!q.empty()) {                     // 위상 정렬 시행
        if (q.size() > 1)
            multiple = true;                // 큐의 크기가 1보다 크다면 가능한 정렬 수가 여러 개
        int cur = q.front();
        q.pop();

        ans.push_back(cur + 'a');
        for (int i : graph[cur]) {
            inorder[i]--;
            if (!inorder[i])
                q.push(i);
        }
    }

    for (int i = 0; i < 26; i++) {
        if (appear[i] && inorder[i]) {      // 아직 진입차수가 0보다 큰 정점 존재 = 사이클이 존재한다는 의미
            cout << "!";
            return;
        }
    }
    if (multiple)
        cout << "?";
    else
        for(char c : ans)
            cout << c;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> str[i];
        for (char c : str[i])
            appear[c - 'a'] = true;
    }
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < str[i].length(); j++) {
            if (j == str[i + 1].length()) {         // 만약 뒤 단어와 다른 알파벳이 없는데 앞 단어가 더 길다면 순서 존재 x
                cout << "!";
                return 0;
            }
            if (str[i][j] != str[i + 1][j]) {       // 바로 뒤 단어와 왼쪽 자리부터 비교하여 다른 알파벳 존재 시 연결 + 진입차수 증가
                graph[str[i][j] - 'a'].push_back(str[i + 1][j] - 'a');
                inorder[str[i + 1][j] - 'a']++;
                break;
            }
        }
    }
    topological();
	return 0;
}