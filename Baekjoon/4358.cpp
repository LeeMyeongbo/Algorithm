#include <iostream>
#include <string>
#include <map>
using namespace std;

double tot;
string name;
map<string, int> eco;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cout.precision(4);																// 소수점 4자리까지 표현하기 위함

	while (true) {
		getline(cin, name);
		if (cin.eof())
			break;
		eco[name]++;
		tot++;
	}
	for (auto iter = eco.begin(); iter != eco.end(); iter++)
		cout << fixed << iter->first << ' ' << iter->second / tot * 100. << "\n";	// fixed : 소수점 고정
	return 0;
}