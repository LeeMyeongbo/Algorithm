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
	cout.precision(4);																// �Ҽ��� 4�ڸ����� ǥ���ϱ� ����

	while (true) {
		getline(cin, name);
		if (cin.eof())
			break;
		eco[name]++;
		tot++;
	}
	for (auto iter = eco.begin(); iter != eco.end(); iter++)
		cout << fixed << iter->first << ' ' << iter->second / tot * 100. << "\n";	// fixed : �Ҽ��� ����
	return 0;
}