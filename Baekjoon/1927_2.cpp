#include <iostream>
using namespace std;

int N, x, heap[200001], Size;

void heapinsert(int n)
{
	heap[++Size] = n;

	int idx = Size;
	while (idx > 1 && heap[idx / 2] > heap[idx]) {		// 부모가 자식보다 클 경우
		swap(heap[idx / 2], heap[idx]);					// 부모 자식 위치 바꿈
		idx /= 2;
	}
}

int heapdelete()
{
	if (!Size)
		return 0;

	int top = heap[1];
	heap[1] = heap[Size];
	heap[Size--] = 0;

	int cur = 1;

	while (true) {
		if (!heap[cur * 2])								// 자식이 없다면 break
			break;

		if (heap[cur * 2] && !heap[cur * 2 + 1]) {		// 왼쪽 자식만 존재할 경우
			if (heap[cur] > heap[cur * 2])
				swap(heap[cur], heap[cur * 2]);			// 부모가 자식보다 크다면 바꿈
			break;
		}
		else {											// 두 자식이 모두 존재할 경우
			if (heap[cur] > heap[cur * 2] || heap[cur] > heap[cur * 2 + 1]) {		// 두 자식 중 하나라도 부모보다 작을 경우
				if (heap[cur * 2] < heap[cur * 2 + 1]) {	// 왼쪽 자식이 오른쪽보다 작을 경우
					swap(heap[cur * 2], heap[cur]);
					cur *= 2;
				}
				else {
					swap(heap[cur * 2 + 1], heap[cur]);		// 오른쪽 자식이 왼쪽보다 작을 경우
					cur = cur * 2 + 1;
				}
			}
			else break;
		}
	}
	return top;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> x;
		if (x)
			heapinsert(x);
		else
			cout << heapdelete() << "\n";
	}
	return 0;
}