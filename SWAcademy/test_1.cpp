#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int T, num, card;
vector<int> even, odd;

int main() 
{
	cin >> T;
	for (int t = 1; t <= T; t++) {
		int ans = 0;
		cin >> num;
		for (int n = 0; n < num; n++) {
			cin >> card;
			if (card % 2)
				odd.push_back(card);
			else
				even.push_back(card);
		}
		sort(even.begin(), even.end());
		sort(odd.begin(), odd.end());

		for (int i = even.size() - 1; i >= even.size() / 2; i--)
			ans += even[i];
		
		for (int i = odd.size() - 1; i >= odd.size() / 2; i--)
			ans += odd[i];

		if (even.size() % 2)
			ans -= max(even[even.size() / 2], odd[odd.size() / 2]);

		cout << '#' << t << ' ' << ans << endl;
		
		even.clear();
		odd.clear();
	}
	return 0;
}