#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int T, n, m, A[1000], B[1000];
long long Ans;
vector<int> subA, subB;			// A와 B의 부분합을 저장하는 배열

void getSum(vector<int>& v, int arr[], int size)		// 부분합 저장
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
			if (subA[left] + subB[right] == T) {						// 합이 T인 경우가 나올 때
				long long n_A = 0;
				int Aval = subA[left];
				while (left < (int)subA.size() && subA[left] == Aval)	// subA는 오른쪽으로 가며 같은 값 개수 헤아림
					left++, n_A++;

				long long n_B = 0;
				int Bval = subB[right];
				while (right >= 0 && subB[right] == Bval)				// subB는 왼쪽으로 가며 같은 값 개수 헤아림
					right--, n_B++;

				Ans += n_A * n_B;										// 둘이 곱함 (최대 50만*50만=2500억이라 int 범위 초과 가능)
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