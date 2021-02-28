#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define INF 10000 //메모리 공간이 무한대에 가깝게 존재한다고 가정.

int arr[INF];
int count = 0;
void addBack(int data) {
	arr[count] = data;
	count++;
}
void addFirst(int data) {
	for (int i = count; i >= 1; i--) {
		arr[i] = arr[i - 1];
	}
	arr[0] = data;
	count++;
}
void show() {
	for (int i = 0; i < count; i++) {
		printf("%d", arr[i]);
	}
}

int main(void) {
	addBack(5);
	addBack(7);
	addBack(8);
	addFirst(3);
	addFirst(4);
	show();
	system("pause");
	return 0;
}
void removeAt(int index) {
	for (int i = index; i < count - 1; i++) {
		arr[i] = arr[i + 1];
	}
	count--;
}

//연결리스트
#include <stdlib.h>

typedef struct {
	int data;
	struct Node *next;
} Node;

Node *head; //연결리스트는 헤드 노드로부터 출발
// 연결리스트는 포인터 변수로 동적 할당을 할 수 있도록 하는 게 일반적임.

void addFront(Node *root, int data) { //root로 삽입 위치 지정
	Node *node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = root->next;
	root->next = node;
}

void removeFront(Node *root) {
	Node *front = root->next; //전에 가리키던 것을 그 다음 노드로 바꿔버리는 것.,
	root->next = front->next;
	free(front); // 메모리 할당을 해제함으로써 삭제.
}

void freeAll(Node *root) {
	Node *cur = head->next;
	while (cur != NULL) {
		Node *next = cur->next;
		free(cur);
		cur = next; //포인터를 다음 노드로 이동.
	}
}

void showAll(Node *root) {
	Node *cur = head->next;
	while (cur != NULL) {
		printf("%d", cur->data);
		cur = cur->next;
	}
}

int main(void) {
	head = (Node*)malloc(sizeof(Node));
	head->next = NULL;//마지막 노드는 명시적으로 NULL이라 해줘야 함.
	addFront(head, 2);
	addFront(head, 1);
	addFront(head, 7);
	addFront(head, 9);
	addFront(head, 8);
	removeFront(head);
	showAll(head);
	freeAll(head);
	system("pause");
	return 0;
}

//양방향 연결 리스트
typedef struct {
	int data;
	struct Node *prev;
	struct Node *next;
}Node;

Node *head, *tail;

void insert(int data) {
	Node* node = (Node*)malloc(sizeof(Node));// 하나의 노드가 들어갈 수 있는 공간할당.
	node->data = data;//데이터값 초기화
	Node* cur;//
	cur = head->next;//노드가 들어갈 위치 지정
	while (cur->data < data && cur != tail) { //우리가 입력하고자 하는 데이터보다 현재 포인터가 가리키고 있는 데이터가 더 작다면
		cur = cur->next; //포인터로 다음 원소를 가리켜주세요,
	}
	Node* prev = cur->prev; //삽입할 노드의 앞쪽 노드를 prev라고 지정.
	prev->next = node; //앞에 있는 노드의 next가 현재 삽입할 노드이고,
	node->prev = prev; //노드의 prev가 앞쪽에 있는 prev가 될 것이고,
	cur->prev = node; //뒤쪽에 있는 노드의 prev가 삽입하고자 하는 노드이고,
	node->next = cur;//노드의 next가 삽입할 노드의 바로 뒤 노드가 되도록.
}

void removeFront() {
	Node* node = head->next;
	head->next = node->next;
	Node* next = node->next;
	next->prev = head; //두 번째 노드의 prev가 head가 되도록 해주는 것.
	free(node);
}

void show() {
	Node* cur = head->next;
	while (cur != tail) {
		printf("%d", cur->data);
		cur = cur->next;
	}
}

int main(void) {
	head = (Node*)malloc(sizeof(Node));
	tail = (Node*)malloc(sizeof(Node));
	head->next = tail;
	head->prev = head;
	tail->next = tail;
	tail->prev = head;
	insert(2);
	insert(1);
	insert(3);
	insert(9);
	insert(7);
	removeFront();
	show();
	system("pause");
	return 0;
}

//스택
#define SIZE 10000
#define INF 9999999

int stack[SIZE]; //스택의 사이즈 지정
int top = -1; //스택의 최상단.

void push(int data) {
	if (top == SIZE - 1) {
		printf("스택 오버플로우가 발생했습니다.\n");
		return;
	}
	stack[++top] = data;
}

int pop() {
	if (top == -1) {
		printf("스택 언더플로우가 발생했습니다.\n");
		return -INF;
	}
	return stack[top--];
 }
void show() {
	printf("---스택의 최상단---\n");
	for (int i = top; i >= 0; i--) {
		printf("%d\n", stack[i]);
	}
	printf("---스택의 최하단---\n");
}

int main(void) {
	push(7);
	push(5);
	push(4);
	pop();
	push(6);
	pop();
	show();
	system("pause");
	return 0;
}

//연결리스트를 활용한 스택 구현
typedef struct {
	int data;
	struct Node *next;
}Node;

typedef struct {
	Node *top; //모든 스택은 탑이라는 노드를 하나 가지고 있어야 함.
}Stack;

void push(Stack *stack, int data) {
	Node *node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = stack->top; //현재 스택의 탑
	stack->top = node; //탑을 마지막에 들어온 데이터로 넣는 것.
}

int pop(Stack *stack) {
	if (stack->top == NULL) {
		printf("스택 언더플로우가 발생했습니다.\n");
		return -INF;
	}
	Node *node = stack->top; //현재의 최상단 노드를 잠깐 node에 담아두었다가
	int data = node->data; //데이터 추출
	stack->top = node->next; //탑을 그 다음 노드로 변경,
	free(node);
	return data;
}

void show(Stack *stack) {
	Node *cur = stack->top;
	printf("---스택의 최상단---\n");
	while (cur != NULL) {
		printf("%d\n", cur->data);
		cur = cur->next;
	}
	printf("---스택의 최하단---\n");
}

int main(void) {
	Stack s;
	s.top = NULL; //반드시 처음 탑은 NULL값이 돼야 함.
	show(&s);
	push(&s, 7);
	push(&s, 5);
	push(&s, 4);
	pop(&s);
	push(&s, 6);
	pop(&s);
	show(&s);
	system("pause");
	return 0;
}

//스택을 활용한 계산기 구현
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	char data[100];
	struct Node *next;
}Node;

typedef struct Stack {
	Node *top;
}Stack;

void push(Stack *stack, char *data) {
	Node *node = (Node*)malloc(sizeof(Node));
	strcpy(node->data, data);
	node->next = stack->top;
	stack->top = node;
}

char* getTop(Stack *stack) {
	Node *top = stack->top;
	return top->data;
}

char* pop(Stack *stack) {
	if (stack->top == NULL) {
		printf("스택 언더플로우가 발생했습니다.\n");
		return NULL;
	}
	Node *node = stack->top;
	char *data = (char*)mallock(sizeof(char));
	strcpy(data, node->data);
	stack->top = node->next;
	free(node);
	return data;
}

int getPriority(char *i) {
	if (!strcmp(i, "(")) return 0;
	if ((!strcmp(i, "+")) || !strcmp(i, "-")) return 1;
	if (!strcmp(i, "*") || !strcmp(i, "/")) return 2;
	return 3;
}

// 후위 표기법 변환 함수
char* transition(Stack *stack, char **s, int size) {
	char res[1000] = "";
	for (int i = 0; i < size; i++) {
		if (!strcmp(s[i], "+") || (!strcmp(s[i], "-")) || (!strcmp(s[i], "*")) || (!strcmp(s[i], "/"))) {
			while (stack->top != NULL && getPriority(getTop(stack)) >= getPriority(s[i])) {
				strcat(res, pop(stack)); strcat(res, " ");
			}
			push(stack, s[i]);
		}
		else if (!strcmp(s[i], "(")) push(stack, s[i]);
		else if (!strcmp(s[i], ")")) {
			while (strcmp(getTop(stack), "(")) {
				strcat(res, pop(stack)); strcat(res, " ");
			}
			pop(stack);
		}
		else {
			strcat(res, s[i]); strcat(res, " ");
		}
	}
	while (stack->top != NULL) {
		strcat(res, pop(stack)); strcat(res, " ");
	}
	return res;
}

void calculate(Stack *stack, char**s, int size) {
	int x, y, z;
	for (int i = 0; i < size; i++) {
		if (!strcmp(s[i], "+") || (!strcmp(s[i], "-")) || (!strcmp(s[i], "*")) || (!strcmp(s[i], "/"))) {
			x = atoi(pop(stack));
			y = atoi(pop(stack)); //y가 먼저 들어간 원소임.
			if (!strcmp(s[i], "+")) z = y + x;
			if (!strcmp(s[i], "-")) z = y - x;
			if (!strcmp(s[i], "*")) z = y * x;
			if (!strcmp(s[i], "/")) z = y / x;
			char buffer[100];
			sprintf(buffer, "%d", z);
			push(stack, buffer);
		}
		else {
			push(stack, s[i]);
		}
	}
	printf("%s", pop(stack));
}

int main(void) {
	Stack stack;
	stack.top = NULL;
	char a[100] = "( ( 3 + 4 ) * 5 ) - 5 * 7 * 5 - 5 * 10";
	int size = 1;
	for (int i = 0; i < strlen(a); i++) {
		if (a[i] == ' ') size++;
	}
	char *ptr = strtok(a, " ");
	char **input = (char**)malloc(sizeof(char*)*size);
	for (int i = 0; i < size; i++) {
		input[i] = (char*)malloc(sizeof(char) * 100);
	}
	for (int i = 0; i < size; i++) {
		strcpy(input[i], ptr);
		ptr = strtok(NULL, " ");
	}
	char b[1000] = "";
	strcpy(b, transition(&stack, input, size));
	printf("후위 표기법: %s\n", b);
	size = 1;
	for (int i = 0; i < strlen(b) - 1; i++) {
		if (b[i] == ' ') size++;
	}
	char *ptr2 = strtok(b, " ");
	for (int i = 0; i < size; i++) {
		strcpy(input[i], ptr2);
		ptr2 = strtok(NULL, " ");
	}
	calculate(&stack, input, size);
	system("pause");
	return 0;
}

//큐의 구현(배열)
#include <stdio.h>
#define SIZE 10000
#define INF 9999999

int queue[SIZE];
int front = 0;
int rear = 0;

void push(int data) {
	if (rear >= SIZE) {
		printf("큐 오버플로우가 발생했습니다.\n");
		return;
	}
	queue[rear++] = data;
}

int pop() {
	if (front == rear) {
		printf("큐 언더플로우가 발생했습니다.\n");
		return -INF;
	}
	return queue[front++];
}

void show() {
	printf("--- 큐의 앞 ---\n");
	for (int i = front; i < rear; i++) {
		printf("%d\n", queue[i]);
	}
	printf("--- 큐의 뒤 ---\n");
}

int main(void) {
	push(7);
	push(5);
	push(4);
	pop();
	push(6);
	pop();
	show();
	system("pause");
	return 0;
}

//큐의 구현(연결리스트)
#include <stdio.h>
#include <stdlib.h>
#define INF 9999999

typedef struct {
	int data;
	struct Node *next;
}Node;

typedef struct {
	Node *front;
	Node *rear;
	int count;
}Queue;

void push(Queue *queue, int data) {
	Node *node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;
	if (queue->count == 0) {
		queue->front = node;//초기 세팅
	}
	else {
		queue->rear->next = node;
	}
	queue->rear = node;
	queue->count++;
}

int pop(Queue *queue) {
	if (queue->count == 0) {
		printf("큐 언더플로우가 발생했습니다.\n");
		return -INF;
	}
	Node *node = queue->front;
	int data = node->data;
	queue->front = node->next;
	free(node);
	queue->count--;
	return data;
}

void show(Queue *queue) {
	Node *cur = queue->front;
	printf("---큐의 앞---\n");
	while (cur != NULL) {
		printf("%d\n", cur->data);
		cur = cur->next;
	}
	printf("---큐의 뒤---\n");
}

int main(void) {
	Queue queue;
	queue.front = queue.rear = NULL;
	queue.count = 0;
	push(&queue, 7);
	push(&queue, 5);
	push(&queue, 4);
	pop(&queue);
	push(&queue, 6);
	pop(&queue);
	show(&queue);
	system("pause");
	return 0;
}

//선택정렬(가장 작은 수를 선택해서 앞으로 보내버리기)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>
#define SIZE 1000

int a[SIZE];

int swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main(void) {
	int n, min, index;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	for (int i = 0; i < n; i++) {
		min = INT_MAX;
		for (int j = i; j < n; j++) {
			if (min > a[j]) {
				min = a[j];
				index = j;
			}
		}
		swap(&a[i], &a[index]);
	}
	for (int i = 0; i < n; i++) printf("%d", a[i]);
	system("pause");
	return 0;
}

// 삽입 정렬
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 1000

int a[SIZE];

int swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main(void) {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	for (int i = 0; i < n - 1; i++) {
		int j = i;
		while (j >= 0 && a[j] > a[j + 1]) {
			swap(&a[j], &a[j + 1]);
			j--;
		}
	}
	for (int i = 0; i < n, i++) printf("%d", a[i]);
	system("pause");
	return 0;
}

//퀵 정렬(배열선언)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 1000

int a[SIZE];
int swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void quickSort(int start, int end) {
	if (start >= end) return;
	int key = start, i = start + i, j = end, temp;
	while (i <= j) {//엇갈릴 때까지 반복
		while (i <= end && a[i] <= a[key])i++;
		while (j > start && a[j] >= a[key]) j--;
		if (i > j) swap(&a[key], &a[j]);
		else swap(&a[i], &a[j]);
	}
	quickSort(start, j - 1);
	quickSort(j + 1, end);
}

int main(void) {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	quickSort(0, n - 1);
	for (int i = 0; i < n; i++) printf("%d", a[i]);
	system("pause");
	return 0;
}

//계수 정렬(배열 안의 수를 크기별로 갯수를 세고 그대로 정렬)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_VALUE 10001

int n, m;
int a[MAX_VALUE];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) { scanf("%d", &m); a[m]++; }
	for (int i = 0; i < MAX_VALUE; i++) {
		while (a[i] != 0) { printf("%d", i); a[i]--; }
	}
	system("pause");
	return 0;
}

// 기수 정렬 : 매 자릿수마다 비교해서 뒤에서부터 정렬
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 100000

void radixSort(int *a, int n) {
	int res[MAX], maxValue = 0;
	int exp = 1;
	for (int i = 0; i < n; i++) {
		if (a[i] > maxValue) maxValue = a[i];
	}
	while (maxValue / exp > 0) {//1의 자리부터 계산
		int bucket[10] = { 0 };
		for (int i = 0; i < n; i++) bucket[a[i] / exp % 10]++; //자릿수 배열 처리, 현재 보고 있는 자릿수의 값을 +1
		for (int i = 1; i < 10; i++) bucket[i] += bucket[i - 1]; //누적 계산
		for (int i = n-1; i>=0;i--){//같은 자릿수끼리는 순서를 유지
			res[--bucket[a[i] / exp % 10]] = a[i];//[--bucket[a[i]/exp%10] : 누적 값에 해당하는 인덱스
		}
		for (int i = 0; i < n; i++) a[i] = res[i]; //기본 배열 갱신
		exp *= 10;
	}
}

int main(void) {
	int a[MAX];
	int i, n;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	radixSort(a, n);
	for (i = 0; i < n; i++) {
		printf("%d", a[i]);
	}
	system("pause");
	return 0;
}

//이진 트리
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int data;
	struct Node *leftChild;
	struct Node *rightChild;
}Node;

Node* initNode(int data, Node* leftChild, Node* rightChild) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->leftChild = leftChild;
	node->rightChild = rightChild;
	return node;
}

//전위 순회
void preorder(Node* root) {
	if (root) {
		printf("%d", root->data);
		preorder(root->leftChild);
		preorder(root->rightChild);
	}
}

//중위 순회
void inorder(Node *root) {
	if (root) {
		inorder(root->leftChild);
		printf("%d", root->data);
		inorder(root->rightChild);
	}
}

//후위 순회
void postorder(Node *root) {
	if (root) {
		postorder(root->leftChild);
		postorder(root->rightChild);
		printf("%d", root->data);
	}
}

int main(void) {
	Node* n7 = initNode(50, NULL, NULL);
	Node* n6 = initNode(37, NULL, NULL);
	Node* n5 = initNode(23, NULL, NULL);
	Node* n4 = initNode(5, NULL, NULL);
	Node* n3 = initNode(48, n6, n7);
	Node* n2 = initNode(17, n4, n5);
	Node* n1 = initNode(30, n2, n3);
	preorder(n1);
	printf("\n");
	inorder(n1);
	printf("\n");
	postorder(n1);
	system("pause");
	return 0;
}

//우선 순위 큐(완전 이진트리 형식으로 보통 구현한다)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_SIZE 10000

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
typedef struct {
	int heap[MAX_SIZE];
	int count;
}priorityQueue;

void push(priorityQueue *pq, int data) {
	if (pq->count >= MAX_SIZE) return;
	pq->heap[pq->count] = data; //완전 이진트리의 마지막 원소로 데이터를 넣겠다.
	int now = pq->count;
	int parent = (pq->count - 1) / 2;
	//새 원소를 삽입한 이후에 상향식으로 힙을 구성합니다.
	while (now > 0 && pq->heap[now] > pq->heap[parent]) {
		swap(&pq->heap[now], &pq->heap[parent]);
		now = parent;
		parent = (parent - 1) / 2;
	}
	pq->count++;
}

int pop(priorityQueue *pq) {
	if (pq->count <= 0) return -9999;
	int res = pq->heap[0];
	pq->count--;
	pq->heap[0] = pq->heap[pq->count];
	int now = 0, leftChild = 1, rightChild = 2;
	int target = now;
	// 새 원소를 추출한 이후에 하향식으로 힙을 구성합니다.
	while (leftChild < pq->count) {
		if (pq->heap[target] < pq->heap[leftChild]) target = leftChild;
		if (pq->heap[target] < pq->heap[rightChild] && rightChild < pq->count) target = rightChild;
		if (target == now) break; // 더 이상 내려가지 않아도 될 때 종료
		else {
			swap(&pq->heap[now], &pq->heap[target]);
			now = target;
			leftChild = now * 2 + 1;
			rightChild = now * 2 + 2;
		}
	}
	return res;
}

int main(void) {
	int n, data;
	scanf("%d", &n);
	priorityQueue pq;
	pq.count = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &data);
		push(&pq, data);
	}
	for (int i = 0; i < n; i++) {
		int data = pop(&pq);
		printf("%d", data);
	}
	system("pause");
	return 0;
}

//순차탐색
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH 1000

char **array;
int founded;

int main(void) {
	int n;
	char *word;
	word = malloc(sizeof(char*) * LENGTH);
	scanf("%d %s", &n, &word);
	array = (char**)malloc(sizeof(char*)*n);
	for (int i = 0; i < n; i++) {
		array[i] = malloc(sizeof(char)*LENGTH);
		scanf("%s", array[i]);
	}
	for (int i = 0; i < n; i++) {
		if (!strcmp[array[i], word]) {
			printf("%d번째 원소입니다.\n", i + 1);
			founded = 1;
		}
	}
	if (!founded) printf("원소를 찾을 수 없습니다.\n");
	system("pause");
	return 0;
}

// 이진 탐색
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_SIZE 100000

int a[MAX_SIZE];
int founded = 0;

int search(int start, int end, int target) {
	if (start > end) return -99999;
	int mid = (start + end) / 2;
	if (a[mid] == target) return mid;
	else if (a[mid] > target) return search(start, mid - 1, target);
	else return search(mid+1,end, target);
}

int main(void) {
	int n, target;
	scanf("%d %d", &n, &target);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	int result = search(0, n - 1, target);
	if (result != -99999) printf("%d번째 원소입니다.\n", result + 1);
	else printf("원소를 찾을 수 없습니다. \n");
	system("pause");
	return 0;
}

//그래프(무방향)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int a[1001][1001];
int n, m; 

int main(void) {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		a[x][y] = 1;
		a[y][x] = 1;
		//서로 연결이 되었다는 것을 알려주는 것
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%d", a[i][j]);
		}
		printf("\n");
	}
	system("pause");
	return 0;
}

//그래프(방향 가중치)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int index;
	int distance;
	struct Node *next;
}Node;

void addFront(Node *root, int index, int distance) {
	Node *node = (Node*)malloc(sizeof(Node));
	node->index = index;
	node->distance = distance;
	node->next = root->next;
	root->next = node;
}

void showAll(Node *root) {
	Node *cur = root->next;
	while (cur != NULL) {
		printf("%d(거리 : %d"), cur->index, cur->distance);
	}
}

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);
	Node** a = (Node**)malloc(sizeof(Node*)*(n + 1));
	for (int i = 1; i <= n; i++) {
		a[i] = (Node*)malloc(sizeof(Node));
		a[i]->next = NULL;
	}
	for (int i = 0; i < m; i++) {
		int x, y, distance;
		scanf("%d %d %d", &x, &y, &distance);
		addFront(a[x], y, distance);
	}
	for (int i = 1; i <= n; i++) {
		printf("원소 [%d]: ", i);
		showAll(a[i]);
		printf("\n");
	}
	system("pause");
	return 0;
}

// 깊이 우선 탐색
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1001

typedef struct {
	int index;
	struct Node *next;
}Node;

Node** a;
int n, m, c[MAX_SIZE]; //c는 현재 방문을 했던 것인지 체크하는 변수

void addFront(Node *root, int index) {
	Node *node = (Node*)malloc(sizeof(Node));
	node->index = index;
	node->next = root->next;
	root->next = node;
}

void dfs(int x) {
	if (c[x]) return;
	c[x] = 1; //방문한 적이 있다면 바로 return하고, 1로 기록
	printf("%d", x);
	Node *cur = a[x]->next;
	while (cur != NULL) {
		int next = cur->index;
		dfs(next);
		cur = cur->next;
	}
}

int main(void) {
	scanf("%d %d", &n, &m);
	a = (Node**)malloc(sizeof(Node*)*MAX_SIZE);
	for (int i = 1; i <= n; i++) {
		a[i] = (Node*)malloc(sizeof(Node));
		a[i]->next = NULL;
	}
	for (int i = 0; i < m; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		addFront(a[x], y);
		addFront(a[y], x);
	}
	dfs(1);
	system("pause");
	return 0;
}

//너비 우선 탐색
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define INF 9999999
#define MAX_SIZE 1001

typedef struct{
	int index;
	struct Node *next;
}Node;

typedef struct {
	Node *front;
	Node *rear;
	int count;
}Queue;

Node** a;
int n, m, c[MAX_SIZE];

void addFront(Node *root, int index) {
	Node *node = (Node*)malloc(sizeof(Node));
	node->index = index;
	node->next = root->next;
	root->next = node;
}

void queuePush(Queue *queue, int index) {
	Node *node = (Node*)malloc(sizeof(Node));
	node->index = index;
	node->next = NULL;
	if (queue->count == 0) {
		queue->front = node;
	}
	else {
		queue->rear->next = node;
	}
	queue->rear = node;
	queue->count++;
}

int queuePop(Queue *queue) {
	if (queue->count == 0) {
		printf("큐 언더플로우가 발생했습니다.\n");
		return -INF;
	}
	Node *node = queue->front;
	int index = node->index;
	queue->front = node->next;
	free(node);
	queue->count--;
	return index;
}

void bfs(int start) {
	Queue q;
	q.front = q.rear = NULL;
	q.count = 0;
	queuePush(&q, start);
	c[start] = 1;
	while (q.count != 0) {
		int x = queuePop(&q);
		printf("%d", x);
		Node *cur = a[x]->next;
		while (cur != NULL) {
			int next = cur->index;
			if (!c[next]) {
				queuePush(&q, next);
				c[next] = 1;
			}
			cur = cur->next;
		}
	}
}

int main(void) {
	scanf("%d %d", &n, &m);
	a = (Node**)malloc(sizeof(Node*)*MAX_SIZE);
	for (int i = 1; i <= n; i++) {
		a[i] = (Node*)malloc(sizeof(Node));
		a[i]->next = NULL;
	}
	for (int i = 0; i < m; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		addFront(a[x], y);
		addFront(a[y], x);
	}
	bfs(1);
	system("pause");
	return 0;
}

//이진탐색트리
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int data;
	struct Node* leftChild;
	struct Node* rightChild;
}Node;

Node* insertNode(Node* root, int data) {
	if (root == NULL) {
		root = (Node*)malloc(sizeof(Node));
		root->leftChild = root->rightChild = NULL;
		root->data = data;
		return root;
	}
	else {
		if (root->data > data) {
			root->leftChild = insertNode(root->leftChild, data);
		}
		else {
			root->rightChild = insertNode(root->rightChild, data);
		}
	}
	return root;
}

Node* findMinNode(Node* root) {
	Node *node = root;
	while (node->leftChild != NULL) {
		node = node->leftChild;
	}
	return node;
}

Node *deleteNode(Node* root, int data) {
	Node* node = NULL;
	if (root == NULL) return NULL;
	if (root->data > data) root->leftChild = deleteNode(root->leftChild, data);
	else if (root->data < data) root->rightChild = deleteNode(root->rightChild, data);
	else {
		if (root->leftChild != NULL && root->rightChild != NULL) {
			node = findMinNode(root->rightChild);
			root->data = node->data;
			root->rightChild = deleteNode(root->rightChild, node->data);
		}
		else {
			node = (root->leftChild != NULL) ? root->leftChild : root->rightChild;
			//왼쪽 자식이 존재하지 않는다면, 오른쪽 자식을 root에 넣고 아니면 왼쪽 자식을 root에 넣어라.
			free(root);
			return node;
		}
	}
	return root;
}

Node* searchNode(Node* root, int data) {
	if (root == NULL) return NULL;
	if (root->data == data) return root;
	else if (root->data > data) return searchNode(root->leftChild, data);
	else return searchNode(root->rightChild, data);
}

void preorder(Node* root) {
	if (root == NULL)return;
	printf("%d", root->data);
	preorder(root->leftChild);
	preorder(root->rightChild);
}

int main(void) {
	Node*root = NULL;
	root = insertNode(root, 30);
	root = insertNode(root, 17);
	root = insertNode(root, 48);
	root = insertNode(root, 5);
	root = insertNode(root, 23);
	root = insertNode(root, 37);
	root = insertNode(root, 50);
	preorder(root);
	system("pause");
	return 0;
}

//AVL 트리
#include <stdio.h>
#include <stdlib.h>

int getMax(int a, int b) {
	if (a > b) return a;
	else return b;
}

typedef struct {
	int data;
	int height;
	struct Node* leftChild;
	struct Node* rightChild;
}Node;

int getHeight(Node* node) {
	if (node == NULL) return 0;
	return node->height;
}

//모든 노드는 회전을 수행한 이후에 높이를 다시 계산
void setHeight(Node* node) {
	node->height = getMax(getHeight(node->leftChild), getHeight(node->rightChild)) + 1;
}

int getDifference(Node* node) {
	if (node == NULL) return 0;
	Node* leftChild = node->leftChild;
	Node* rightChild = node->rightChild;
	return getHeight(leftChild) - getHeight(rightChild);
}

Node* rotateLL(Node *node) {
	Node *leftChild = node->leftChild;
	node->leftChild = leftChild->rightChild;
	leftChild->rightChild = node;
	setHeight(node);
	return leftChild;
}

Node* rotateRR(Node *node) {
	Node *rightChild = node->rightChild;
	node->rightChild = rightChild->leftChild;
	rightChild->leftChild = node;
	setHeight(node);
	return rightChild;
}

Node* rotateLR(Node *node) {//LR 회전은 RR과 LR을 합친 것.
	Node *leftChild = node->leftChild;
	node->leftChild = rotateRR(leftChild);
	setHeight(node->leftChild);
	return rotateLL(node);
}

Node* rotateRL(Node *node) {//LR 회전은 LR과 RR을 합친 것.
	Node *leftChild = node->leftChild;
	node->leftChild = rotateLL(leftChild);
	setHeight(node->leftChild);
	return rotateRR(node);
}

Node *balance(Node *node) {
	int difference = getDifference(node);
	if (difference >= 2) {
		if (getDifference(node->leftChild) >= 1) {
			node = rotateLL(node);
		}
		else {
			node = rotateLR(node);
		}
	}
	else if (difference <= -2) {
		if (getDifference(node->rightChild) <= -1) {
			node = rotateRR(node);
		}
		else {
			node = rotateRL(node);
		}
	}
	setHeight(node);
	return node;
}

Node *insertNode(Node *node, int data) {
	if (!node) {
		node = (Node*)malloc(sizeof(Node));
		node->data = data;
		node->height = 1;
		node->leftChild = node->rightChild = NULL;
	}
	else if (data < node->data) {
		node->leftChild = insertNode(node->leftChild, data);
		node = balance(node);
	}
	else if (data > node->data) {
		node->rightChild = insertNode(node->rightChild, data);
		node = balance(node);
	}
	else {
		printf("데이터 중복이 발생했습니다. \n");
	}
	return node;
}

Node* root = NULL;

void display(Node* node, int level) {
	if (node != NULL) {
		display(node->rightChild, level + 1);
		printf("\n");
		if (node == root) {
			printf("Root:");
		}
		for (int i = 0; i < level && node != root; i++) {
			printf("  ");
		}
		printf("%d(%d)", node->data, getHeight(node));
		display(node->leftChild, level + 1);
	}
}

int main(void) {
	root = insertNode(root, 7);
	root = insertNode(root, 6);
	root = insertNode(root, 5);
	root = insertNode(root, 3);
	root = insertNode(root, 1);
	root = insertNode(root, 9);
	root = insertNode(root, 8);
	root = insertNode(root, 12);
	root = insertNode(root, 16);
	root = insertNode(root, 18);
	root = insertNode(root, 23);
	root = insertNode(root, 21);
	root = insertNode(root, 14);
	root = insertNode(root, 15);
	root = insertNode(root, 19);
	root = insertNode(root, 20);
	display(root, 1); printf("\n");
	system("pause");
}

//해시
// 선형조사법
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TABLE_SIZE 10007
#define INPUT_SIZE 5000

typedef struct {
	int id;
	char name[20];
}Student;

//해시 테이블 초기화
void init(Student** hashTable) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		hashTable[i] = NULL;
	}
}

//해시 테이블의 메모리를 반환합니다.
void destructor(Student** hashTable) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hashTable[i] != NULL) {
			free(hashTable[i]);
		}
	}
}

//해시 테이블 내 빈 공간을 선형 탐색으로 찾습니다.
int findEmpty(Student** hashTable, int id) {
	int i = id % TABLE_SIZE;
	while (1) {
		if (hashTable[i % TABLE_SIZE] == NULL) {
			return i % TABLE_SIZE;
		}
		i++;
	}
}

//특정한 ID 값에 매칭되는 데이터를 해시 테이블 내에서 찾습니다.
int search(Student** hashTable, int id) {
	int i = id % TABLE_SIZE;
	while (1) {
		if (hashTable[i % TABLE_SIZE] == NULL) return -1;
		else if (hashTable[i % TABLE_SIZE]->id == id) return 1;
		i++;
	}
}

// 특정한 키 인덱스에 데이터를 삽입합니다.
void add(Student** hashTable, Student* input, int key) {
	hashTable[key] = input;
}

//해시 테이블에서 특정한 키의 데이터를 반환합니다.
Student* getValue(Student** hashTable, int key) {
	return hashTable[key];
}

//해시 테이블에 존재하는 모든 데이터를 출력합니다.
void show(Student** hashTable) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hashTable[i] != NULL) {
			printf("키:[%d] 이름:[%s]\n", i, hashTable[i]->name);
		}
	}
}

int main(void) {
	Student **hashTable;
	hashTable = (Student**)malloc(sizeof(Student)*TABLE_SIZE);
	init(hashTable);

	for (int i = 0; i < INPUT_SIZE; i++) {
		Student* student = (Student*)malloc(sizeof(Student));
		student->id = rand() % 1000000;
		sprintf(student->name, "사람%d", student->id);
		if (search(hashTable, student->id) == -1) {
			int index = findEmpty(hashTable, student->id);
			add(hashTable, student, index);
		}
	}

	show(hashTable);
	destructor(hashTable);
	system("pause");
	return 0;
}

//해시 - 체이닝 기법
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TABLE_SIZE 10007
#define INPUT_SIZE 5000

typedef struct {
	int id;
	char name[20];
}Student;

typedef struct {
	Student* data;
	struct Bucket* next;
}Bucket;

// 해시 테이블 초기화
void init(Bucket** hashTable) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		hashTable[i] = NULL;
	}
}

//해시 테이블 메모리 반환
void destructor(Bucket** hashTable) {
	for (int i = 0; i < TABLE_SIZE, I++) {
		if (hashTable[i] != NULL) {
			free(hashTable[i]);
		}
	}
}

//체이닝 데이터 탐색
int isExist(Bucket** hashTable, int id) {
	int i = id % TABLE_SIZE;
	if (hashTable[i] == NULL) return 0;
	else {
		Bucket *cur = hashTable[i];
		while (cur != NULL) {
			if (cur->data->id == id) return 1;
			cur = cur->next;
		}
	}
	return 0;
}

//체이닝 데이터 삽입
void add(Bucket** hashTable, Student* input) {
	int i = input->id % TABLE_SIZE;
	if (hashTable[i] == NULL) {
		hashTable[i] = (Bucket*)malloc(sizeof(Bucket));
		hashTable[i]->data = input;
		hashTable[i]->next = NULL;
	}
	else {
		Bucket *cur = (Bucket*)malloc(sizeof(Bucket));
		cur->data = input;
		cur->next = hashTable[i];
		hashTable[i] = cur;
	}
}

//체이닝 데이터 출력 함수
void show(Bucket** hashTable) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hashTable[i] != NULL) {
			Bucket *cur = hashTable[i];
			while (cur != NULL) {
				printf("키: [%d] 이름: [%s]", i, cur->data->name);
				cur = cur->next;
			}
		}
	}
}

int main(void) {
	Bucket **hashTable;
	hashTable = (Bucket**)malloc(sizeof(Bucket)*TABLE_SIZE);
	init(hashTable);

	for (int i = 0; i < INPUT_SIZE; i++) {
		Student* student = (Student*)malloc(sizeof(Student));
		student->id = rand() % 1000000;
		sprintf(student->name, "사람%d", student->id);
		if (!isExist(hashTable, student->id)) {
			add(hashTable, student);
		}
	}

	show(hashTable);
	destructor(hashTable);
	system("pause");
	return 0;
}

//프림 알고리즘 -- 우선순위 큐를 활용
//간선 구조체 정의
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define NODE_MAX 1001
#define EDGE_MAX 200001 // 양방향 간선이므로 각 방향당 100000개씩.

typedef struct {
	int cost;
	int node;
}Edge;

void swap(Edge *a, Edge *b) {
	Edge temp;
	temp.cost = a->cost;
	temp.node = a->node;
	a->cost = b->cost;
	a->node = b->node;
	b->cost = temp.cost;
	b->node = temp.node;
}

//프림 알고리즘 우선순위 큐 정의 및 삽입
typedef struct {
	Edge *heap[EDGE_MAX];
	int count;
}priorityQueue;

void push(priorityQueue *pq, Edge *edge) {
	if (pq->count >= EDGE_MAX) return;
	pq->heap[pq->count] = edge;
	int now = pq->count;
	int parent = (pq->count - 1) / 2;
	//새 원소를 삽입한 이후에 상향식으로 힙을 구성함.
	while (now > 0 && pq->heap[now]->cost < pq->heap[parent]->cost) {
		swap(pq->heap[now], pq->heap[parent]);
		now = parent;
		parent = (parent - 1) / 2;
	}
	pq->count++;
}

//프림 알고리즘 우선순위 큐 추출함수
Edge* pop(priorityQueue *pq) {
	if (pq->count <= 0) return NULL;
	Edge *res = pq->heap[0];
	pq->count--;
	pq->heap[0] = pq->heap[pq->count];
	int now = 0, leftChild = 1, rightChild = 2;
	int target = now;
	//새 원소를 추출한 이후에 하향식으로 힙 구성.
	while (leftChild < pq->count) {
		if (pq->heap[target]->cost > pq->heap[leftChild]->cost) target = leftChild;
		if (pq->heap[target]->cost > pq->heap[rightChild]->cost && rightChild < pq->count) target = rightChild;
		if (target == now) break;
		else {
			swap(pq->heap[now], pq->heap[target]);
			now = target;
			leftChild = now * 2 + 1;
			rightChild = now * 2 + 2;
		}
	}
	return res;
}

//프림 알고리즘 간선 연결리스트 구현
typedef struct Node {
	Edge *data;
	struct Node *next;
}Node;

Node** adj;
int d[NODE_MAX];

void addNode(Node** target, int index, Edge* edge) {
	if (target[index] == NULL) {
		target[index] = (Node*)malloc(sizeof(Node));
		target[index]->data = edge;
		target[index]->next = NULL;
	}
	else {
		Node* node = (Node*)malloc(sizeof(Node));
		node->data = edge;
		node->next = target[index];
		target[index] = node;
	}
}

//프림 알고리즘 사용
int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);
	adj = (Node**)malloc(sizeof(Node*)*(n + 1));
	for (int i = 1; i <= n; i++) {
		adj[i] = NULL;
	}
	priorityQueue *pq;
	pq = (priorityQueue*)malloc(sizeof(priorityQueue));
	pq->count = 0;
	for (int i = 0; i < m; i++) {
		int a, b, c; //a에서 b까지 가는 데에 c만큼 소비된다.
		scanf("%d %d %d", &a, &b, &c);
		Edge *edge1 = (Edge*)malloc(sizeof(Edge));
		edge1->node = b;
		edge1->cost = c;
		addNode(adj, a, edge1);
		Edge *edge2 = (Edge*)malloc(sizeof(Edge));
		edge2->node = a;
		edge2->cost = c;
		addNode(adj, b, edge2);
	}
	long long res = 0;
	Edge *start = (Edge*)malloc(sizeof(Edge));
	start->cost = 0; start->node = 1; push(pq, start);
	for (int i = 1; i < n; i++) {
		int nextNode = -1, nextCost = INT_MAX;
		while (1) {
			Edge* now = pop(pq);
			if (now == NULL) break;
			nextNode = now->node;
			if (!d[nextNode]) {
				nextCost = now->cost; break;//방문하지 않은 노드들 중 가장 비용이 적은 노드를 우선순위 큐에서 꺼내줄 것
				// 기본적으로 우선순위 큐는 비용이 적은 순으로 들어가 있기 때문에
				// 방문하지 않은 노드를 찾겠다는 의미가 되는 것.
			}
		}
		if (nextCost == INT_MAX) printf("연결 그래프가 아닙니다.\n");
		res += nextCost;
		d[nextNode] = 1;
		Node* cur = adj[nextNode];
		while (cur != NULL) { push(pq, cur->data); cur = cur->next; }
	}
	printf("%lld\n", res);
	system("pause");
}

//다익스트라 최단경로
//간선 구조체 정의
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define NODE_MAX 20001
#define EDGE_MAX 600001 // 양방향 간선이므로 300,000개

typedef struct {
	int cost;
	int node;
}Edge;

void swap(Edge *a, Edge *b) {
	Edge temp;
	temp.cost = a->cost;
	temp.node = a->node;
	a->cost = b->cost;
	a->node = b->node;
	b->cost = temp.cost;
	b->node = temp.node;
}

//우선순위 큐 정의 및 삽입

typedef struct {
	Edge *heap[EDGE_MAX];
	int count;
}priorityQueue;

void push(priorityQueue *pq, Edge *edge) {
	if (pq->count >= EDGE_MAX) return;
	pq->heap[pq->count] = edge;
	int now = pq->count;
	int parent = (pq->count - 1) / 2;
	// 새 원소를 삽입한 이후에 상향식으로 힙을 구성합니다.
	while (now > 0 && pq->heap[now]->cost < pq->heap[parent]->cost) {
		swap(pq->heap[now], pq->heap[parent]);
		now = parent;
		parent = (parent - 1) / 2;
	}
	pq->count++;
}

//추출함수
Edge* pop(priorityQueue *pq) {
	if (pq->count <= 0) return NULL;
	Edge *res = pq->heap[0];
	pq->count--;
	pq->heap[0] = pq->heap[pq->count];
	int now = 0; leftChild = 1; rightChild = 2;
	int target = now;
	//새 원소를 추출한 이후에 하향식으로 힙을 구성합니다.
	while (leftChild < pq->count) {
		if (pq->heap[target]->cost > pq->heap[leftChild]->cost) target = leftChild;
		if (pq->heap[target]->cost > pq->heap[rightChild]->cost && rightChild < pq->count) target = rightChild;
		if (target == now) break; //더 이상 내려가지 않아도 될 때 종료.
		else {
			swap(pq->heap[now], pq->heap[target]);
			now = target;
			leftChild = now * 2 + 1;
			rightChild = now * 2 + 2;
		}
		return res;
	}
}

//간선 연결리스트 구현
typedef struct Node {
	Edge *data;
	struct Node *next;
} Node;

Node** adj;
int ans[NODE_MAX];

void addNode(Node** target, int index, Edge* edge) {
	if (target[index] == NULL) {
		target[index] = (Node*)malloc(sizeof(Node));
		target[index]->data = edge;
		target[index]->next = NULL;
	}
	else {
		Node* node = (Node*)malloc(sizeof(Node));
		node->data = edge;
		node->next = target[index];
		target[index] = node;
	}
}

//다익스트라 알고리즘 사용
int main(void) {
	int n, m, k; //k는 출발하는 노드
	scanf("%d %d %d", &n, &m, &k);
	adj = (Node**)malloc(sizeof(Node*)*(n + 1)); //연결리스트 불러오기.
	for (int i = 1; i <= n; i++) {
		adj[i] = NULL;
		ans[i] = INT_MAX; //모든 노드로 갈 수 있는 값이 무한이라고 가정.
	}
	priorityQueue *pq;
	pq = (priorityQueue*)malloc(sizeof(priorityQueue));
	pq->count = 0;
	for (int i = 0; i < m; i++) {
		int a, b, c ;
		scanf("%d %d %d", &a, &b, &c);
		Edge *edge = (Edge*)malloc(sizeof(Edge));
		edge->node = b;
		edge->cost = c;
		addNode(adj, a, edge);
	}
	//다익스트라 알고리즘 시작
	ans[k] = 0; //특정 노드까지의 최단거리값.
	Edge *start = (Edge*)malloc(sizeof(Edge));
	start->cost = 0; start->node = k; push(pq, start); //자기 자신에게서 출발하는 것이니까 비용은 당연히 0
	while (1) {
		Edge* now = pop(pq);
		if (now == NULL) break;
		int curNode = now->node;
		int curCost = now->cost;
		if (ans[curNode] < curCost) continue; //현재 보고 있는 비용이 현재 테이블에 담겨있는 비용보다 크다면 계속
		Node* cur = adj[curNode];
		while (cur != NULL) {
			Edge* temp = cur->data;
			temp->cost += curCost;
			if (temp->cost < ans[temp->node]) {
				ans[temp->node] = temp->cost; push(pq, temp);
			}
			cur = cur->next;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (ans[i] == INT_MAX) printf("INF\n");
		else printf("%d\n", ans[i]);
	}
	system("pause");
}

//세그먼트 트리 -- 구간 합.
#include <stdio.h>
#define NUMBER 7

int a[] = { 7,1,9,5,6,4,1 };
int tree[4 * NUMBER];//4를 곱하면 모든 범위를 커버할 수 있습니다.
//start: 시작 인덱스, end: 끝 인덱스
int init(int start, int end, int node) {
	if (start == end) return tree[node] = a[start];
	int mid = (start + end) / 2;
	//재귀적으로 두 부분으로 나눈 뒤에 그 합을 자기 자신으로 한다.
	return tree[node] = init(start, mid, node * 2) + init(mid + 1, end, node * 2 + 1);
}

//구간 합 구하기.
// start:시작 인덱스, end: 끝 인덱스
//left, right: 구간 합을 구하고자 하는 범위
int sum(int start, int end, int node, int left, int right) {
	// 범위 밖에 있는 경우
	if (left > end || right < start) return 0;
	// 범위 안에 있는 경우
	if (left <= start && end <= right) return tree[node];
	// 그렇지 않다면 두 부분으로 나누어 합을 구하기.
	int mid = (start + end) / 2;
	return sum(start, mid, node * 2, left, right) + sum(mid + 1, end, node * 2 + 1, left, right);
}

// 구간합 수정하기.
// start: 시작 인덱스, end: 끝 인덱스
// index: 구간 합을 수정하고자 하는 노드
//dif: 수정할 값

void update(int start, int end, int node, int index, int dif) {
	// 범위 밖에 있는 경우
	if (index < start || index > end) return;
	// 범위 안에 있으면 내려가며 다른 원소도 갱신
	tree[node] += dif;
	if (start == end) return;
	int mid = (start + end) / 2;
	update(start, mid, node * 2, index, dif);
	update(mid + 1, end, node * 2 + 1, index, dif);
}

int main(void) {
	// 구간 합 트리의 인덱스를 제외하고는 모두 인덱스 0부터 시작합니다.
	// 구간 합 트리 생성하기
	init(0, NUMBER - 1, 1);
	//구간 합 구하기
	printf("0부터 6까지의 구간 합:%d\n", sum(0, NUMBER - 1, 1, 0, 6));
	//구간 합 갱신하기.
	printf("인덱스 5의 원소를 +3만큼 수정\n");
	update(0, NUMBER - 1, 1, 5, 3);
	//구간 합 다시 구하기
	printf("3부터 6까지의 구간 합: %d\n", sum(0, NUMBER - 1, 1, 3, 6));
	system("pause");
}

//인덱스 트리를 통한 합 구하기.
#include <stdio.h>
#define NUMBER 7

int tree[NUMBER];

int sum(int i) {
	int res = 0;
	while (i > 0) {
		res += tree[i];
		//마지막 비트만큼 빼면서 앞으로 이동
		i -= (i&-i)// 마지막 비트를 구하는 방법이죠.
	}
	return res;
}

//특정 인덱스 수정하기.
void update(int i, int dif) {
	while (i <= NUMBER) {
		tree[i] += dif;
		//마지막 비트만큼 더하면서 뒤로 이동
		i += (i&-i);
	}
}

// 구간 합 계산함수.
int getSection(int start, int end) {
	return sum(end) - sum(start - 1);
}

//인덱스 트리 사용
int main(void) {
	update(1, 7);
	update(2, 1);
	update(3, 9);
	update(4, 5);
	update(5, 6);
	update(6, 4);
	update(7, 1);
	printf("1부터 7까지의 구간 합: %d\n", getSection(1, 7));
	printf("인덱스 6의 원소를 +3만큼 수정");
	update(6, 3);
	printf("4부터 7까지의 구간 합: %d\n", getSection(4, 7));
	system("pause");
}

//단순 비교 문자열 매칭
#include <stdio.h>
#include <string>

char *parent = "ABCDEFG";
char *pattern = "EF";

int main(void) {
	int parentSize = strlen(parent);
	int patternSize = strlen(pattern);
	for (int i = 0; i <= parentSize - patternSize; i++) {
		int found = 1;
		for (int j = 0; j < patternSize; j++) {
			if (parent[i + j] != pattern[j]) { found = 0; break; }
		}
		if (found) {
			printf("%d번째에서 찾았습니다.\n", i + 1);
		}
	}
	system("pause");
}

//KMP 문자열 매칭
//테이블 만들기:문자열 정의
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *parent = "acabacdabac";
char *pattern = "abacdab";

//테이블 만들기: 테이블 생성 함수 구현
int* makeTable(char* pattern) {
	int patternSize = strlen(pattern);
	int* table = (int*)malloc(sizeof(int)*patternSize);
	for (int i = 0; i < patternSize; i++) {
		table[i] = 0;
	}
	int j = 0;
	for (int i = 1; i < patternSize; i++) {
		while (j > 0 && pattern[i] != pattern[j]) {
			j = table[j - 1];
		}
		if (pattern[i] == pattern[j]) {
			table[i] = ++j;
		}
	}
	return table;
}

//문자열 매칭 진행하기:KMP 함수 구현하기
void KMP(char* parent, char* pattern) {
	int* table = makeTable(pattern);
	int parentSize = strlen(parent);
	int patternSize = strlen(pattern);
	int j = 0;
	for (int i = 0; i < parentSize; i++) {
		while (j > 0 && parent[i] != pattern[j]) {
			j = table[j - 1];
		}
		if (parent[i] == pattern[j]) {
			if (j == patternSize - 1) {
				printf("[인덱스 %d]에서 매칭 성공\n", i - patternSize + 2);
				j = table[j];
			}
			else {
				j++;
			}
		}
	}
}

//KMP 문자열 매칭 알고리즘 사용
int main(void) {
	KMP(parent, pattern);
	system("pause");
}

//라빈 카프 문자열 매칭
#include <stdio.h>
#include <string.h>

char *parent = "acabacdabac";
char *pattern = "abacdab";

void check(char* parent, char*pattern, int start) {
	//start는 해시값이 일치하기 시작한 인덱스.
	int found = 1;
	int patternSize = strlen(pattern);
	for (int i = 0; i < patternSize; i++) {
		if (parent[start + i] != pattern[i]) {
			found = 0;
			break;
		}
	}
	if (found) {
		printf("[인덱스 %d에서 매칭발생]\n", start + 1);
	}
}

//라빈 카프 알고리즘 구현
void rabinKarp(char* parent, char *pattern) {
	int parentSize = strlen(parent);
	int patternSize = strlen(pattern);
	int parentHash = 0, patternHash = 0, power = 1;
	for (int i = 0; i <= parentSize - patternSize; i++) {
		if (i == 0) {
			for (int j = 0; j < patternSize; j++) {
				parentHash = parentHash + parent[patternSize - 1 - j] * power;
				patternHash = patternHash + pattern[patternSize - 1 - j] * power;
				if (j < patternSize - 1) * power = power * 2;
				//가장 뒤에 있는 것부터 power를 곱해가면서 해시값을 연산
			}
		}
		else {
			parentHash = 2 * (parentHash - parent[i - 1] * power) + parent[patternSize - 1 + i];
		}
		if (parentHash == patternHash) {
			check(parent, pattern, i);
		}		
	}
}

int main(void) {
	rabinKarp(parent, pattern);
	system("pause");
}