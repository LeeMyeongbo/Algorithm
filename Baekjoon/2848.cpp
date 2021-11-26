#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> graph[26];
string str[100];
bool appear[26];        // ��Ÿ�� ���ĺ��� ����
int N, inorder[26];

void topological()
{
    vector<char> ans;
    bool multiple = false;                  // ������ ������ ���� �� �ִ��� �Ǻ�
    queue<int> q;
    for (int i = 0; i < 26; i++) {
        if (appear[i] && !inorder[i])       // ��Ͽ� ��Ÿ�� ���ĺ��� �� ���������� 0�� ���ĺ� ť�� ����
            q.push(i);
    }

    while(!q.empty()) {                     // ���� ���� ����
        if (q.size() > 1)
            multiple = true;                // ť�� ũ�Ⱑ 1���� ũ�ٸ� ������ ���� ���� ���� ��
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
        if (appear[i] && inorder[i]) {      // ���� ���������� 0���� ū ���� ���� = ����Ŭ�� �����Ѵٴ� �ǹ�
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
            if (j == str[i + 1].length()) {         // ���� �� �ܾ�� �ٸ� ���ĺ��� ���µ� �� �ܾ �� ��ٸ� ���� ���� x
                cout << "!";
                return 0;
            }
            if (str[i][j] != str[i + 1][j]) {       // �ٷ� �� �ܾ�� ���� �ڸ����� ���Ͽ� �ٸ� ���ĺ� ���� �� ���� + �������� ����
                graph[str[i][j] - 'a'].push_back(str[i + 1][j] - 'a');
                inorder[str[i + 1][j] - 'a']++;
                break;
            }
        }
    }
    topological();
	return 0;
}