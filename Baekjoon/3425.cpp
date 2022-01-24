#include <iostream>
#include <stack>
#include <vector>
#include <cmath>
using namespace std;

long long num_x, input;
int input_num;
string command;
exception e;

int main()
{
	while (true) {
		vector<string> commands;
		vector<long long> num_list;

		while (true) {
			cin >> command;

			if (command == "QUIT")
				return 0;

			if (command == "END")
				break;

			commands.push_back(command);
			if (command == "NUM") {
				cin >> num_x;
				num_list.push_back(num_x);
			}
		}

		cin >> input_num;
		for (int i = 0; i < input_num; i++) {
			stack<long long> s;
			int idx = 0;
			bool flag = true;

			cin >> input;
			s.push(input);

			for (string c : commands) {
				try {
					if (c == "NUM")
						s.push(num_list[idx++]);
					else if (c == "POP") {
						if (s.empty())
							throw e;
						s.pop();
					}
					else if (c == "INV") {
						if (s.empty())
							throw e;
						int n = s.top();
						s.pop();
						s.push(-n);
					}
					else if (c == "DUP") {
						if (s.empty())
							throw e;
						s.push(s.top());
					}
					else if (c == "SWP") {
						if (s.size() < 2)
							throw e;

						long long first = s.top();
						s.pop();
						long long second = s.top();
						s.pop();

						s.push(first);
						s.push(second);
					}
					else if (c == "ADD") {
						if (s.size() < 2)
							throw e;

						long long first = s.top();
						s.pop();
						long long second = s.top();
						s.pop();

						s.push(second + first);
					}
					else if (c == "SUB") {
						if (s.size() < 2)
							throw e;

						long long first = s.top();
						s.pop();
						long long second = s.top();
						s.pop();

						s.push(second - first);
					}
					else if (c == "MUL") {
						if (s.size() < 2)
							throw e;

						long long first = s.top();
						s.pop();
						long long second = s.top();
						s.pop();

						s.push(second * first);
					}
					else if (c == "DIV") {
						if (s.size() < 2)
							throw e;

						long long first = s.top();
						s.pop();
						long long second = s.top();
						s.pop();

						if (!first)
							throw e;

						if (first > 0 && second < 0 || first < 0 && second > 0) {
							second = abs(second);
							first = abs(first);
							s.push(-(second / first));
						}
						else
							s.push(second / first);
					}
					else {
						if (s.size() < 2)
							throw e;

						long long first = s.top();
						s.pop();
						long long second = s.top();
						s.pop();

						if (!first)
							throw e;

						if (second > 0)
							s.push(second % first);
						else {
							second = abs(second);
							first = abs(first);
							s.push(-(second % first));
						}
					}
					if (!s.empty() && abs(s.top()) > 1000000000)
						throw e;
				}
				catch (...) {
					cout << "ERROR\n";
					flag = false;
					break;
				}
			}
			if (flag) {
				if (s.size() == 1)
					cout << s.top() << "\n";
				else
					cout << "ERROR\n";
			}
			while (!s.empty())
				s.pop();
		}
		cout << endl;
	}
}