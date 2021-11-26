#include <iostream>
#include <vector>
#include <algorithm>
#define FAST ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int N, K;
string str[20];

struct Tree {
	vector<Tree*> child;
	string str;

	void put(string str[], int num) {
		if (num == K)
			return;

		int right = child.size(), left = 0;
		while (left < right) {						// lower bound를 이용
			int middle = (left + right) / 2;
			if (str[num] > child[middle]->str)
				left = middle + 1;
			else
				right = middle;
		}

		if (right == child.size()) {				// 구한 위치가 end(완전 맨 끝)을 가리킬 경우
			Tree* tree = new Tree();
			tree->str = str[num];
			child.push_back(tree);
		}
		else if (child[right]->str != str[num]) {	// 그게 아니라 
			Tree* tree = new Tree();
			tree->str = str[num];
			child.insert(child.begin() + right, tree);
		}

		child[right]->put(str, num + 1);
	}

	void print(int down) {
		if (down != -1) {
			for (int i = 0; i < down * 2; i++)
				cout << "-";
			cout << str << "\n";
		}
		for (auto v : child)
			v->print(down + 1);
	}
};

int main()
{
	FAST;
	Tree* root = new Tree();
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> K;
		for (int k = 0; k < K; k++)
			cin >> str[k];
		root->put(str, 0);
	}
	root->print(-1);
	return 0;
}