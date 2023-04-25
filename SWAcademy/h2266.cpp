#include <string>
#include <cstring>
#include <vector>
#include <unordered_map>
#define MAXN			(500)
#define MAXL			(11)
using namespace std;

int cnt, numA, numB, project[500][1000];    // project[root1][root2] : 동맹의 루트 1(나라 A)과 동맹의 루트 2(나라 B)가 결성한 프로젝트 수
pair<int, int> companies[1000];             // companies[c] : (기업 c가 속한 동맹의 루트 (idx가 가장 작은 기업이 루트), 동맹의 크기)
unordered_map<string, int> company;

int findRoot(int c)
{
    if (c == companies[c].first)
        return companies[c].first;

    return companies[c].first = findRoot(companies[c].first);
}

void updateAlly(int ally1, int ally2)       // ally2의 기업들이 맺은 공동 프로젝트 총 개수를 ally1에 합침
{
    vector<pair<int, int>> tmp;

    if (ally1 < numA)                       // ally1, ally2가 나라 A에 속할 경우
    {
        for (int i = numA; i < numA + numB; i++)    // ally2가 하고 있던 공동 프로젝트들 모두 가져다가
        {
            if (project[ally2][i])
            {
                tmp.push_back({ i, project[ally2][i] });
                project[ally2][i] = 0;
            }
        }
        for (auto& p : tmp)                         // ally1에다가 다 합침 (루트에 몰아주기)
            project[ally1][p.first] += p.second;
    }
    else                                    // ally1, ally2가 나라 B에 속할 경우
    {
        for (int i = 0; i < numA; i++)
        {
            if (project[i][ally2])
            {
                tmp.push_back({ i, project[i][ally2] });
                project[i][ally2] = 0;
            }
        }
        for (auto& p : tmp)
            project[p.first][ally1] += p.second;
    }
}

void merge(int c1, int c2)
{
    c1 = findRoot(c1);
    c2 = findRoot(c2);

    if (c1 == c2)
        return;

    if (c1 > c2)
        swap(c1, c2);

    updateAlly(c1, c2);
    companies[c2].first = companies[c1].first;
    companies[c1].second += companies[c2].second;
}

void init(int mNumA, char mCompanyListA[MAXN][MAXL], int mNumB, char mCompanyListB[MAXN][MAXL])
{
    cnt = 0;
    numA = mNumA, numB = mNumB;
    company.clear();
    memset(project, 0, sizeof(project));

    for (int a = 0; a < mNumA; a++)
    {
        string name(mCompanyListA[a]);
        companies[cnt] = { cnt, 1 };
        company.insert({ name, cnt++ });
    }
    for (int b = 0; b < mNumB; b++)
    {
        string name(mCompanyListB[b]);
        companies[cnt] = { cnt, 1 };
        company.insert({ name, cnt++ });
    }
}

void startProject(char mCompanyA[MAXL], char mCompanyB[MAXL])
{
    string companyA(mCompanyA);
    string companyB(mCompanyB);

    int cA = company[companyA], cB = company[companyB];
    project[findRoot(cA)][findRoot(cB)]++;
}

void finishProject(char mCompanyA[MAXL], char mCompanyB[MAXL])
{
    string companyA(mCompanyA);
    string companyB(mCompanyB);

    int cA = company[companyA], cB = company[companyB];
    project[findRoot(cA)][findRoot(cB)]--;
}

void ally(char mCompany1[MAXL], char mCompany2[MAXL])
{
    string company1(mCompany1);
    string company2(mCompany2);

    int c1 = company[company1], c2 = company[company2];
    merge(c1, c2);
}

int conflict(char mCompany1[MAXL], char mCompany2[MAXL])
{
    bool visited[1000] = { false, };
    string company1(mCompany1);
    string company2(mCompany2);

    int c1 = findRoot(company[company1]), c2 = findRoot(company[company2]), ans = 0;
    if (c1 < numA)
    {
        for (int i = numA; i < numA + numB; i++)
        {
            int root_i = findRoot(i);
            if (project[c1][root_i] && project[c2][root_i] && !visited[root_i])
            {
                visited[root_i] = true;
                ans += companies[root_i].second;
            }
        }
    }
    else
    {
        for (int i = 0; i < numA; i++)
        {
            int root_i = findRoot(i);
            if (project[root_i][c1] && project[root_i][c2] && !visited[root_i])
            {
                visited[root_i] = true;
                ans += companies[root_i].second;
            }
        }
    }

    return ans;
}
