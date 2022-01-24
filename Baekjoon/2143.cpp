#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int T, n, m, A[1000], B[1000];
long long Ans;
vector<int> subA, subB;			// A�� B�� �κ����� �����ϴ� �迭

void getSum(vector<int>& v, int arr[], int size)		// �κ��� ����
{
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			if (i == j)
				v.push_back(arr[i]);
			else
				v.push_back(v.back() + arr[j]);
		}
	}
}

long long solve()
{
	int left = 0, right = (int)subB.size() - 1;

	while (left < (int)subA.size() && right >= 0) {
		if (subA[left] + subB[right] > T)
			right--;
		else {
			if (subA[left] + subB[right] == T) {						// ���� T�� ��찡 ���� ��
				long long n_A = 0;
				int Aval = subA[left];
				while (left < (int)subA.size() && subA[left] == Aval)	// subA�� ���������� ���� ���� �� ���� ��Ƹ�
					left++, n_A++;

				long long n_B = 0;
				int Bval = subB[right];
				while (right >= 0 && subB[right] == Bval)				// subB�� �������� ���� ���� �� ���� ��Ƹ�
					right--, n_B++;

				Ans += n_A * n_B;										// ���� ���� (�ִ� 50��*50��=2500���̶� int ���� �ʰ� ����)
			}
			else
				left++;
		}
	}

	return Ans;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> T >> n;
	for (int i = 0; i < n; i++)
		cin >> A[i];
	
	cin >> m;
	for (int i = 0; i < m; i++)
		cin >> B[i];
	
	getSum(subA, A, n);
	getSum(subB, B, m);

	sort(subA.begin(), subA.end());
	sort(subB.begin(), subB.end());
	
	cout << solve();
	return 0;
}