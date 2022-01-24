#include <iostream>
using namespace std;

int N, x, heap[200001], Size;

void heapinsert(int n)
{
	heap[++Size] = n;

	int idx = Size;
	while (idx > 1 && heap[idx / 2] > heap[idx]) {		// �θ� �ڽĺ��� Ŭ ���
		swap(heap[idx / 2], heap[idx]);					// �θ� �ڽ� ��ġ �ٲ�
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
		if (!heap[cur * 2])								// �ڽ��� ���ٸ� break
			break;

		if (heap[cur * 2] && !heap[cur * 2 + 1]) {		// ���� �ڽĸ� ������ ���
			if (heap[cur] > heap[cur * 2])
				swap(heap[cur], heap[cur * 2]);			// �θ� �ڽĺ��� ũ�ٸ� �ٲ�
			break;
		}
		else {											// �� �ڽ��� ��� ������ ���
			if (heap[cur] > heap[cur * 2] || heap[cur] > heap[cur * 2 + 1]) {		// �� �ڽ� �� �ϳ��� �θ𺸴� ���� ���
				if (heap[cur * 2] < heap[cur * 2 + 1]) {	// ���� �ڽ��� �����ʺ��� ���� ���
					swap(heap[cur * 2], heap[cur]);
					cur *= 2;
				}
				else {
					swap(heap[cur * 2 + 1], heap[cur]);		// ������ �ڽ��� ���ʺ��� ���� ���
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