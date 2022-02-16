#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, recom, student;
struct Node {
	int student, recommend, time;
};
vector<Node> list;
vector<int> ans;

bool compare(Node n1, Node n2)
{
	if (n1.recommend > n2.recommend || n1.recommend == n2.recommend && n1.time > n2.time)
		return true;

	return false;
}

int main()
{
	cin >> N >> recom;
	for (int i = 0; i < recom; i++) {
		bool added = true;
		cin >> student;
		for (int k = 0; k < list.size(); k++) {
			if (list[k].student == student) {
				list[k].recommend++;
				added = false;
				break;
			}
		}
		if (added) {
			if (list.size() >= N)
				list.pop_back();
			list.push_back({ student, 1, i });
		}

		sort(list.begin(), list.end(), compare);
	}
	
	for (Node& n : list)
		ans.push_back(n.student);
	sort(ans.begin(), ans.end());

	for (int i : ans)
		cout << i << ' ';
	return 0;
}