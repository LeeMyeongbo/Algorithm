#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define BUCKETS 10
#define DIGITS 4
#define MAX_QUEUE_SIZE 100

typedef int element;
typedef struct { // ť Ÿ��
	element  data[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

// ���� �Լ�
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// ���� ���� ���� �Լ�
void init_queue(QueueType *q)
{
	q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}

// ��ȭ ���� ���� �Լ�
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// ���� �Լ�
void enqueue(QueueType *q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// ���� �Լ�
element dequeue(QueueType *q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

int list[MAX_SIZE];
int n;
int sorted[MAX_SIZE]; // �պ� ������ ���� �߰� ����

// �������� (������ ���� x)
void selection_sort(int list[], int n)
{
	int i, j, least, temp;
	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++) 	// �ּҰ� Ž��
			if (list[j] < list[least]) 
				least = j;
		SWAP(list[i], list[least], temp);
	}
}

// ��������
// 1. �ε��� 1���� ����.(�ε��� 0�� �̹� ���ĵ� ������)
// 2. ���� ���Ե� ������ i��° ������ key ������ ����
// 3. ���� ���ĵ� �迭�� i-1�����̹Ƿ� i-1��°���� �������� ����
// 4. j���� ������ �ƴϾ�� �ǰ� key������ ���ĵ� �迭�� �ִ� ���� ũ�� j��°�� j+1��°�� �̵�
// 5. j�� �ϳ� ���ҽ�Ŵ
// 6. j��° ������ key���� �����Ƿ� j+1��°�� key���� �� ��ġ
void insertion_sort(int list[], int n)
{
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] > key; j--)
			list[j + 1] = list[j];	 /* ���ڵ��� ������ �̵� */
		list[j + 1] = key;
	}
}

// ��������
void bubble_sort(int list[], int n)
{
	int i, j, temp;
	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++)
			/* �յ��� ���ڵ带 ���� �� ��ü */
			if (list[j] > list[j + 1])
				SWAP(list[j], list[j + 1], temp);
	}
}

// �� ����
// gap ��ŭ ������ ��ҵ��� ���� ����
// ������ ������ first���� last
inc_insertion_sort(int list[], int first, int last, int gap)
{
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {
		key = list[i];
		for (j = i - gap; j >= first && key < list[j]; j = j - gap)
			list[j + gap] = list[j];
		list[j + gap] = key;
	}
}

void shell_sort(int list[], int n)   // n = size
{
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; i++)		// �κ� ����Ʈ�� ������ gap
			inc_insertion_sort(list, i, n - 1, gap);
	}
}

// �պ�����
void merge(int list[], int left, int mid, int right)
{
	// i�� ���ĵ� ���� ����Ʈ�� ���� �ε���, j�� ���ĵ� ������ ����Ʈ�� ���� �ε���, k�� ���ĵ� ����Ʈ�� ���� �ε���
	int i, j, k, l;
	i = left; 
	j = mid + 1;
	k = left;

	// ���� ���ĵ� list�� �պ�
	while (i <= mid && j <= right)
	{
		if (list[i] <= list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[i++];
	}
	if (i > mid) // ���� �ִ� ���ڵ��� �ϰ� ����
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	else // ���� �ִ� ���ڵ��� �ϰ� ����
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];

	// �迭 sorted�� ����Ʈ�� �迭 list�� �纹��
	for (l = left; l <= right; l++)
		list[l] = sorted[l];
}

merge_sort(int list[], int left, int right)
{
	int mid;
	if (left < right)
	{
		int mid = (left + right) / 2; // ����Ʈ�� �յ� ����
		merge_sort(list, left, mid); // �κ� ����Ʈ ����
		merge_sort(list, mid + 1, right); // �κ� ����Ʈ ����
		merge(list, left, mid, right); // �պ�
	}
}

// �� ����
int partition(int list[], int left, int right) // pivot�� ��ġ ��ȯ 
{
	int pivot, temp, low, high;
	low = left;
	high = right + 1;
	pivot = list[left];
	do {
		do
			low++;
		while (list[low] < pivot);
		do
			high--;
		while (list[high] > pivot);
		if (low < high) SWAP(list[low], list[high], temp);
	} while (low < high);

	SWAP(list[left], list[high], temp);
	return high;
}

void quick_sort(int list[], int left, int right)
{
	if (left < right)
	{
		int q = partition(list, left, right);
		quick_sort(list, left, q - 1); // pivot �ٷ� �� ������ ��ȯȣ��
		quick_sort(list, q + 1, right); // pivot �ٷ� �ں��� ��ȯȣ��
	}
}

// ��� ����
int radix_sort(int list[], int n)
{
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS];

	for (b = 0; b < BUCKETS; b++)
		init_queue(&queues[b]); // ť���� �ʱ�ȭ
	for (d = 0; d < DIGITS; d++)
		for (i = 0; i < n; i++)
			enqueue(&queues[(list[i] / factor) % 10], list[i]); // �����͵��� �ڸ����� ���� ť�� ����
	for (b = i = 0; b < BUCKETS; b++) // ��Ŷ���� ������ list�� ��ģ��.
		while (!is_empty(&queues[b]))
			list[i++] = dequeue(&queues[b]);
	factor *= 10; // �� ���� �ڸ����� ����.
}

int main(void)
{
	int i;
	n = MAX_SIZE;
	srand(time(NULL));

	for (i = 0; i < n; i++)      	// ���� ���� �� ��� 
		list[i] = rand() % 100; // ���� �߻� ���� 0~99
	selection_sort(list, n); // �������� ȣ�� 
	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");

	for (i = 0; i < n; i++)      	// ���� ���� �� ��� 
		list[i] = rand() % 100; // ���� �߻� ���� 0~99
	insertion_sort(list, n); // �������� ȣ��
	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");

	for (i = 0; i < n; i++)      	// ���� ���� �� ��� 
		list[i] = rand() % 100; // ���� �߻� ���� 0~99
	quick_sort(list, 0, n - 1); // �� ���� ȣ��
	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
	return 0;
}