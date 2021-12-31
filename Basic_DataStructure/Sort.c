#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define BUCKETS 10
#define DIGITS 4
#define MAX_QUEUE_SIZE 100

typedef int element;
typedef struct { // 큐 타입
	element  data[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

// 오류 함수
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 공백 상태 검출 함수
void init_queue(QueueType *q)
{
	q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 삽입 함수
void enqueue(QueueType *q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

int list[MAX_SIZE];
int n;
int sorted[MAX_SIZE]; // 합병 정렬을 위한 추가 공간

// 선택정렬 (안정성 만족 x)
void selection_sort(int list[], int n)
{
	int i, j, least, temp;
	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++) 	// 최소값 탐색
			if (list[j] < list[least]) 
				least = j;
		SWAP(list[i], list[least], temp);
	}
}

// 삽입정렬
// 1. 인덱스 1부터 시작.(인덱스 0은 이미 정렬된 것으로)
// 2. 현재 삽입될 숫자인 i번째 정수를 key 변수로 복사
// 3. 현재 정렬된 배열은 i-1까지이므로 i-1번째부터 역순으로 조사
// 4. j값이 음수가 아니어야 되고 key값보다 정렬된 배열에 있는 값이 크면 j번째를 j+1번째로 이동
// 5. j를 하나 감소시킴
// 6. j번째 정수가 key보다 작으므로 j+1번째가 key값이 들어갈 위치
void insertion_sort(int list[], int n)
{
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] > key; j--)
			list[j + 1] = list[j];	 /* 레코드의 오른쪽 이동 */
		list[j + 1] = key;
	}
}

// 버블정렬
void bubble_sort(int list[], int n)
{
	int i, j, temp;
	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++)
			/* 앞뒤의 레코드를 비교한 후 교체 */
			if (list[j] > list[j + 1])
				SWAP(list[j], list[j + 1], temp);
	}
}

// 셸 정렬
// gap 만큼 떨어진 요소들을 삽입 정렬
// 정렬의 범위는 first에서 last
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
		for (i = 0; i < gap; i++)		// 부분 리스트의 개수는 gap
			inc_insertion_sort(list, i, n - 1, gap);
	}
}

// 합병정렬
void merge(int list[], int left, int mid, int right)
{
	// i는 정렬된 왼쪽 리스트에 대한 인덱스, j는 정렬된 오른쪽 리스트에 대한 인덱스, k는 정렬된 리스트에 대한 인덱스
	int i, j, k, l;
	i = left; 
	j = mid + 1;
	k = left;

	// 분할 정렬된 list의 합병
	while (i <= mid && j <= right)
	{
		if (list[i] <= list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[i++];
	}
	if (i > mid) // 남아 있는 레코드의 일괄 복사
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	else // 남아 있는 레코드의 일괄 복사
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];

	// 배열 sorted의 리스트를 배열 list로 재복사
	for (l = left; l <= right; l++)
		list[l] = sorted[l];
}

merge_sort(int list[], int left, int right)
{
	int mid;
	if (left < right)
	{
		int mid = (left + right) / 2; // 리스트의 균등 분할
		merge_sort(list, left, mid); // 부분 리스트 정렬
		merge_sort(list, mid + 1, right); // 부분 리스트 정렬
		merge(list, left, mid, right); // 합병
	}
}

// 퀵 정렬
int partition(int list[], int left, int right) // pivot의 위치 반환 
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
		quick_sort(list, left, q - 1); // pivot 바로 앞 까지를 순환호출
		quick_sort(list, q + 1, right); // pivot 바로 뒤부터 순환호출
	}
}

// 기수 정렬
int radix_sort(int list[], int n)
{
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS];

	for (b = 0; b < BUCKETS; b++)
		init_queue(&queues[b]); // 큐들의 초기화
	for (d = 0; d < DIGITS; d++)
		for (i = 0; i < n; i++)
			enqueue(&queues[(list[i] / factor) % 10], list[i]); // 데이터들을 자리수에 따라 큐에 삽입
	for (b = i = 0; b < BUCKETS; b++) // 버킷에서 꺼내어 list로 합친다.
		while (!is_empty(&queues[b]))
			list[i++] = dequeue(&queues[b]);
	factor *= 10; // 그 다음 자리수로 간다.
}

int main(void)
{
	int i;
	n = MAX_SIZE;
	srand(time(NULL));

	for (i = 0; i < n; i++)      	// 난수 생성 및 출력 
		list[i] = rand() % 100; // 난수 발생 범위 0~99
	selection_sort(list, n); // 선택정렬 호출 
	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");

	for (i = 0; i < n; i++)      	// 난수 생성 및 출력 
		list[i] = rand() % 100; // 난수 발생 범위 0~99
	insertion_sort(list, n); // 삽입정렬 호출
	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");

	for (i = 0; i < n; i++)      	// 난수 생성 및 출력 
		list[i] = rand() % 100; // 난수 발생 범위 0~99
	quick_sort(list, 0, n - 1); // 퀵 정렬 호출
	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
	return 0;
}