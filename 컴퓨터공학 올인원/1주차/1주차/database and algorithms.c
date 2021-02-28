#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define INF 10000 //�޸� ������ ���Ѵ뿡 ������ �����Ѵٰ� ����.

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

//���Ḯ��Ʈ
#include <stdlib.h>

typedef struct {
	int data;
	struct Node *next;
} Node;

Node *head; //���Ḯ��Ʈ�� ��� ���κ��� ���
// ���Ḯ��Ʈ�� ������ ������ ���� �Ҵ��� �� �� �ֵ��� �ϴ� �� �Ϲ�����.

void addFront(Node *root, int data) { //root�� ���� ��ġ ����
	Node *node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = root->next;
	root->next = node;
}

void removeFront(Node *root) {
	Node *front = root->next; //���� ����Ű�� ���� �� ���� ���� �ٲ������ ��.,
	root->next = front->next;
	free(front); // �޸� �Ҵ��� ���������ν� ����.
}

void freeAll(Node *root) {
	Node *cur = head->next;
	while (cur != NULL) {
		Node *next = cur->next;
		free(cur);
		cur = next; //�����͸� ���� ���� �̵�.
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
	head->next = NULL;//������ ���� ��������� NULL�̶� ����� ��.
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

//����� ���� ����Ʈ
typedef struct {
	int data;
	struct Node *prev;
	struct Node *next;
}Node;

Node *head, *tail;

void insert(int data) {
	Node* node = (Node*)malloc(sizeof(Node));// �ϳ��� ��尡 �� �� �ִ� �����Ҵ�.
	node->data = data;//�����Ͱ� �ʱ�ȭ
	Node* cur;//
	cur = head->next;//��尡 �� ��ġ ����
	while (cur->data < data && cur != tail) { //�츮�� �Է��ϰ��� �ϴ� �����ͺ��� ���� �����Ͱ� ����Ű�� �ִ� �����Ͱ� �� �۴ٸ�
		cur = cur->next; //�����ͷ� ���� ���Ҹ� �������ּ���,
	}
	Node* prev = cur->prev; //������ ����� ���� ��带 prev��� ����.
	prev->next = node; //�տ� �ִ� ����� next�� ���� ������ ����̰�,
	node->prev = prev; //����� prev�� ���ʿ� �ִ� prev�� �� ���̰�,
	cur->prev = node; //���ʿ� �ִ� ����� prev�� �����ϰ��� �ϴ� ����̰�,
	node->next = cur;//����� next�� ������ ����� �ٷ� �� ��尡 �ǵ���.
}

void removeFront() {
	Node* node = head->next;
	head->next = node->next;
	Node* next = node->next;
	next->prev = head; //�� ��° ����� prev�� head�� �ǵ��� ���ִ� ��.
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

//����
#define SIZE 10000
#define INF 9999999

int stack[SIZE]; //������ ������ ����
int top = -1; //������ �ֻ��.

void push(int data) {
	if (top == SIZE - 1) {
		printf("���� �����÷ο찡 �߻��߽��ϴ�.\n");
		return;
	}
	stack[++top] = data;
}

int pop() {
	if (top == -1) {
		printf("���� ����÷ο찡 �߻��߽��ϴ�.\n");
		return -INF;
	}
	return stack[top--];
 }
void show() {
	printf("---������ �ֻ��---\n");
	for (int i = top; i >= 0; i--) {
		printf("%d\n", stack[i]);
	}
	printf("---������ ���ϴ�---\n");
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

//���Ḯ��Ʈ�� Ȱ���� ���� ����
typedef struct {
	int data;
	struct Node *next;
}Node;

typedef struct {
	Node *top; //��� ������ ž�̶�� ��带 �ϳ� ������ �־�� ��.
}Stack;

void push(Stack *stack, int data) {
	Node *node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = stack->top; //���� ������ ž
	stack->top = node; //ž�� �������� ���� �����ͷ� �ִ� ��.
}

int pop(Stack *stack) {
	if (stack->top == NULL) {
		printf("���� ����÷ο찡 �߻��߽��ϴ�.\n");
		return -INF;
	}
	Node *node = stack->top; //������ �ֻ�� ��带 ��� node�� ��Ƶξ��ٰ�
	int data = node->data; //������ ����
	stack->top = node->next; //ž�� �� ���� ���� ����,
	free(node);
	return data;
}

void show(Stack *stack) {
	Node *cur = stack->top;
	printf("---������ �ֻ��---\n");
	while (cur != NULL) {
		printf("%d\n", cur->data);
		cur = cur->next;
	}
	printf("---������ ���ϴ�---\n");
}

int main(void) {
	Stack s;
	s.top = NULL; //�ݵ�� ó�� ž�� NULL���� �ž� ��.
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

//������ Ȱ���� ���� ����
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
		printf("���� ����÷ο찡 �߻��߽��ϴ�.\n");
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

// ���� ǥ��� ��ȯ �Լ�
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
			y = atoi(pop(stack)); //y�� ���� �� ������.
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
	printf("���� ǥ���: %s\n", b);
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

//ť�� ����(�迭)
#include <stdio.h>
#define SIZE 10000
#define INF 9999999

int queue[SIZE];
int front = 0;
int rear = 0;

void push(int data) {
	if (rear >= SIZE) {
		printf("ť �����÷ο찡 �߻��߽��ϴ�.\n");
		return;
	}
	queue[rear++] = data;
}

int pop() {
	if (front == rear) {
		printf("ť ����÷ο찡 �߻��߽��ϴ�.\n");
		return -INF;
	}
	return queue[front++];
}

void show() {
	printf("--- ť�� �� ---\n");
	for (int i = front; i < rear; i++) {
		printf("%d\n", queue[i]);
	}
	printf("--- ť�� �� ---\n");
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

//ť�� ����(���Ḯ��Ʈ)
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
		queue->front = node;//�ʱ� ����
	}
	else {
		queue->rear->next = node;
	}
	queue->rear = node;
	queue->count++;
}

int pop(Queue *queue) {
	if (queue->count == 0) {
		printf("ť ����÷ο찡 �߻��߽��ϴ�.\n");
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
	printf("---ť�� ��---\n");
	while (cur != NULL) {
		printf("%d\n", cur->data);
		cur = cur->next;
	}
	printf("---ť�� ��---\n");
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

//��������(���� ���� ���� �����ؼ� ������ ����������)
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

// ���� ����
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

//�� ����(�迭����)
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
	while (i <= j) {//������ ������ �ݺ�
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

//��� ����(�迭 ���� ���� ũ�⺰�� ������ ���� �״�� ����)
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

// ��� ���� : �� �ڸ������� ���ؼ� �ڿ������� ����
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 100000

void radixSort(int *a, int n) {
	int res[MAX], maxValue = 0;
	int exp = 1;
	for (int i = 0; i < n; i++) {
		if (a[i] > maxValue) maxValue = a[i];
	}
	while (maxValue / exp > 0) {//1�� �ڸ����� ���
		int bucket[10] = { 0 };
		for (int i = 0; i < n; i++) bucket[a[i] / exp % 10]++; //�ڸ��� �迭 ó��, ���� ���� �ִ� �ڸ����� ���� +1
		for (int i = 1; i < 10; i++) bucket[i] += bucket[i - 1]; //���� ���
		for (int i = n-1; i>=0;i--){//���� �ڸ��������� ������ ����
			res[--bucket[a[i] / exp % 10]] = a[i];//[--bucket[a[i]/exp%10] : ���� ���� �ش��ϴ� �ε���
		}
		for (int i = 0; i < n; i++) a[i] = res[i]; //�⺻ �迭 ����
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

//���� Ʈ��
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

//���� ��ȸ
void preorder(Node* root) {
	if (root) {
		printf("%d", root->data);
		preorder(root->leftChild);
		preorder(root->rightChild);
	}
}

//���� ��ȸ
void inorder(Node *root) {
	if (root) {
		inorder(root->leftChild);
		printf("%d", root->data);
		inorder(root->rightChild);
	}
}

//���� ��ȸ
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

//�켱 ���� ť(���� ����Ʈ�� �������� ���� �����Ѵ�)
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
	pq->heap[pq->count] = data; //���� ����Ʈ���� ������ ���ҷ� �����͸� �ְڴ�.
	int now = pq->count;
	int parent = (pq->count - 1) / 2;
	//�� ���Ҹ� ������ ���Ŀ� ��������� ���� �����մϴ�.
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
	// �� ���Ҹ� ������ ���Ŀ� ��������� ���� �����մϴ�.
	while (leftChild < pq->count) {
		if (pq->heap[target] < pq->heap[leftChild]) target = leftChild;
		if (pq->heap[target] < pq->heap[rightChild] && rightChild < pq->count) target = rightChild;
		if (target == now) break; // �� �̻� �������� �ʾƵ� �� �� ����
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

//����Ž��
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
			printf("%d��° �����Դϴ�.\n", i + 1);
			founded = 1;
		}
	}
	if (!founded) printf("���Ҹ� ã�� �� �����ϴ�.\n");
	system("pause");
	return 0;
}

// ���� Ž��
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
	if (result != -99999) printf("%d��° �����Դϴ�.\n", result + 1);
	else printf("���Ҹ� ã�� �� �����ϴ�. \n");
	system("pause");
	return 0;
}

//�׷���(������)
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
		//���� ������ �Ǿ��ٴ� ���� �˷��ִ� ��
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

//�׷���(���� ����ġ)
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
		printf("%d(�Ÿ� : %d"), cur->index, cur->distance);
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
		printf("���� [%d]: ", i);
		showAll(a[i]);
		printf("\n");
	}
	system("pause");
	return 0;
}

// ���� �켱 Ž��
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1001

typedef struct {
	int index;
	struct Node *next;
}Node;

Node** a;
int n, m, c[MAX_SIZE]; //c�� ���� �湮�� �ߴ� ������ üũ�ϴ� ����

void addFront(Node *root, int index) {
	Node *node = (Node*)malloc(sizeof(Node));
	node->index = index;
	node->next = root->next;
	root->next = node;
}

void dfs(int x) {
	if (c[x]) return;
	c[x] = 1; //�湮�� ���� �ִٸ� �ٷ� return�ϰ�, 1�� ���
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

//�ʺ� �켱 Ž��
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
		printf("ť ����÷ο찡 �߻��߽��ϴ�.\n");
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

//����Ž��Ʈ��
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
			//���� �ڽ��� �������� �ʴ´ٸ�, ������ �ڽ��� root�� �ְ� �ƴϸ� ���� �ڽ��� root�� �־��.
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

//AVL Ʈ��
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

//��� ���� ȸ���� ������ ���Ŀ� ���̸� �ٽ� ���
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

Node* rotateLR(Node *node) {//LR ȸ���� RR�� LR�� ��ģ ��.
	Node *leftChild = node->leftChild;
	node->leftChild = rotateRR(leftChild);
	setHeight(node->leftChild);
	return rotateLL(node);
}

Node* rotateRL(Node *node) {//LR ȸ���� LR�� RR�� ��ģ ��.
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
		printf("������ �ߺ��� �߻��߽��ϴ�. \n");
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

//�ؽ�
// ���������
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

//�ؽ� ���̺� �ʱ�ȭ
void init(Student** hashTable) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		hashTable[i] = NULL;
	}
}

//�ؽ� ���̺��� �޸𸮸� ��ȯ�մϴ�.
void destructor(Student** hashTable) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hashTable[i] != NULL) {
			free(hashTable[i]);
		}
	}
}

//�ؽ� ���̺� �� �� ������ ���� Ž������ ã���ϴ�.
int findEmpty(Student** hashTable, int id) {
	int i = id % TABLE_SIZE;
	while (1) {
		if (hashTable[i % TABLE_SIZE] == NULL) {
			return i % TABLE_SIZE;
		}
		i++;
	}
}

//Ư���� ID ���� ��Ī�Ǵ� �����͸� �ؽ� ���̺� ������ ã���ϴ�.
int search(Student** hashTable, int id) {
	int i = id % TABLE_SIZE;
	while (1) {
		if (hashTable[i % TABLE_SIZE] == NULL) return -1;
		else if (hashTable[i % TABLE_SIZE]->id == id) return 1;
		i++;
	}
}

// Ư���� Ű �ε����� �����͸� �����մϴ�.
void add(Student** hashTable, Student* input, int key) {
	hashTable[key] = input;
}

//�ؽ� ���̺��� Ư���� Ű�� �����͸� ��ȯ�մϴ�.
Student* getValue(Student** hashTable, int key) {
	return hashTable[key];
}

//�ؽ� ���̺� �����ϴ� ��� �����͸� ����մϴ�.
void show(Student** hashTable) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hashTable[i] != NULL) {
			printf("Ű:[%d] �̸�:[%s]\n", i, hashTable[i]->name);
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
		sprintf(student->name, "���%d", student->id);
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

//�ؽ� - ü�̴� ���
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

// �ؽ� ���̺� �ʱ�ȭ
void init(Bucket** hashTable) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		hashTable[i] = NULL;
	}
}

//�ؽ� ���̺� �޸� ��ȯ
void destructor(Bucket** hashTable) {
	for (int i = 0; i < TABLE_SIZE, I++) {
		if (hashTable[i] != NULL) {
			free(hashTable[i]);
		}
	}
}

//ü�̴� ������ Ž��
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

//ü�̴� ������ ����
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

//ü�̴� ������ ��� �Լ�
void show(Bucket** hashTable) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hashTable[i] != NULL) {
			Bucket *cur = hashTable[i];
			while (cur != NULL) {
				printf("Ű: [%d] �̸�: [%s]", i, cur->data->name);
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
		sprintf(student->name, "���%d", student->id);
		if (!isExist(hashTable, student->id)) {
			add(hashTable, student);
		}
	}

	show(hashTable);
	destructor(hashTable);
	system("pause");
	return 0;
}

//���� �˰��� -- �켱���� ť�� Ȱ��
//���� ����ü ����
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define NODE_MAX 1001
#define EDGE_MAX 200001 // ����� �����̹Ƿ� �� ����� 100000����.

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

//���� �˰��� �켱���� ť ���� �� ����
typedef struct {
	Edge *heap[EDGE_MAX];
	int count;
}priorityQueue;

void push(priorityQueue *pq, Edge *edge) {
	if (pq->count >= EDGE_MAX) return;
	pq->heap[pq->count] = edge;
	int now = pq->count;
	int parent = (pq->count - 1) / 2;
	//�� ���Ҹ� ������ ���Ŀ� ��������� ���� ������.
	while (now > 0 && pq->heap[now]->cost < pq->heap[parent]->cost) {
		swap(pq->heap[now], pq->heap[parent]);
		now = parent;
		parent = (parent - 1) / 2;
	}
	pq->count++;
}

//���� �˰��� �켱���� ť �����Լ�
Edge* pop(priorityQueue *pq) {
	if (pq->count <= 0) return NULL;
	Edge *res = pq->heap[0];
	pq->count--;
	pq->heap[0] = pq->heap[pq->count];
	int now = 0, leftChild = 1, rightChild = 2;
	int target = now;
	//�� ���Ҹ� ������ ���Ŀ� ��������� �� ����.
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

//���� �˰��� ���� ���Ḯ��Ʈ ����
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

//���� �˰��� ���
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
		int a, b, c; //a���� b���� ���� ���� c��ŭ �Һ�ȴ�.
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
				nextCost = now->cost; break;//�湮���� ���� ���� �� ���� ����� ���� ��带 �켱���� ť���� ������ ��
				// �⺻������ �켱���� ť�� ����� ���� ������ �� �ֱ� ������
				// �湮���� ���� ��带 ã�ڴٴ� �ǹ̰� �Ǵ� ��.
			}
		}
		if (nextCost == INT_MAX) printf("���� �׷����� �ƴմϴ�.\n");
		res += nextCost;
		d[nextNode] = 1;
		Node* cur = adj[nextNode];
		while (cur != NULL) { push(pq, cur->data); cur = cur->next; }
	}
	printf("%lld\n", res);
	system("pause");
}

//���ͽ�Ʈ�� �ִܰ��
//���� ����ü ����
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define NODE_MAX 20001
#define EDGE_MAX 600001 // ����� �����̹Ƿ� 300,000��

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

//�켱���� ť ���� �� ����

typedef struct {
	Edge *heap[EDGE_MAX];
	int count;
}priorityQueue;

void push(priorityQueue *pq, Edge *edge) {
	if (pq->count >= EDGE_MAX) return;
	pq->heap[pq->count] = edge;
	int now = pq->count;
	int parent = (pq->count - 1) / 2;
	// �� ���Ҹ� ������ ���Ŀ� ��������� ���� �����մϴ�.
	while (now > 0 && pq->heap[now]->cost < pq->heap[parent]->cost) {
		swap(pq->heap[now], pq->heap[parent]);
		now = parent;
		parent = (parent - 1) / 2;
	}
	pq->count++;
}

//�����Լ�
Edge* pop(priorityQueue *pq) {
	if (pq->count <= 0) return NULL;
	Edge *res = pq->heap[0];
	pq->count--;
	pq->heap[0] = pq->heap[pq->count];
	int now = 0; leftChild = 1; rightChild = 2;
	int target = now;
	//�� ���Ҹ� ������ ���Ŀ� ��������� ���� �����մϴ�.
	while (leftChild < pq->count) {
		if (pq->heap[target]->cost > pq->heap[leftChild]->cost) target = leftChild;
		if (pq->heap[target]->cost > pq->heap[rightChild]->cost && rightChild < pq->count) target = rightChild;
		if (target == now) break; //�� �̻� �������� �ʾƵ� �� �� ����.
		else {
			swap(pq->heap[now], pq->heap[target]);
			now = target;
			leftChild = now * 2 + 1;
			rightChild = now * 2 + 2;
		}
		return res;
	}
}

//���� ���Ḯ��Ʈ ����
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

//���ͽ�Ʈ�� �˰��� ���
int main(void) {
	int n, m, k; //k�� ����ϴ� ���
	scanf("%d %d %d", &n, &m, &k);
	adj = (Node**)malloc(sizeof(Node*)*(n + 1)); //���Ḯ��Ʈ �ҷ�����.
	for (int i = 1; i <= n; i++) {
		adj[i] = NULL;
		ans[i] = INT_MAX; //��� ���� �� �� �ִ� ���� �����̶�� ����.
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
	//���ͽ�Ʈ�� �˰��� ����
	ans[k] = 0; //Ư�� �������� �ִܰŸ���.
	Edge *start = (Edge*)malloc(sizeof(Edge));
	start->cost = 0; start->node = k; push(pq, start); //�ڱ� �ڽſ��Լ� ����ϴ� ���̴ϱ� ����� �翬�� 0
	while (1) {
		Edge* now = pop(pq);
		if (now == NULL) break;
		int curNode = now->node;
		int curCost = now->cost;
		if (ans[curNode] < curCost) continue; //���� ���� �ִ� ����� ���� ���̺� ����ִ� ��뺸�� ũ�ٸ� ���
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

//���׸�Ʈ Ʈ�� -- ���� ��.
#include <stdio.h>
#define NUMBER 7

int a[] = { 7,1,9,5,6,4,1 };
int tree[4 * NUMBER];//4�� ���ϸ� ��� ������ Ŀ���� �� �ֽ��ϴ�.
//start: ���� �ε���, end: �� �ε���
int init(int start, int end, int node) {
	if (start == end) return tree[node] = a[start];
	int mid = (start + end) / 2;
	//��������� �� �κ����� ���� �ڿ� �� ���� �ڱ� �ڽ����� �Ѵ�.
	return tree[node] = init(start, mid, node * 2) + init(mid + 1, end, node * 2 + 1);
}

//���� �� ���ϱ�.
// start:���� �ε���, end: �� �ε���
//left, right: ���� ���� ���ϰ��� �ϴ� ����
int sum(int start, int end, int node, int left, int right) {
	// ���� �ۿ� �ִ� ���
	if (left > end || right < start) return 0;
	// ���� �ȿ� �ִ� ���
	if (left <= start && end <= right) return tree[node];
	// �׷��� �ʴٸ� �� �κ����� ������ ���� ���ϱ�.
	int mid = (start + end) / 2;
	return sum(start, mid, node * 2, left, right) + sum(mid + 1, end, node * 2 + 1, left, right);
}

// ������ �����ϱ�.
// start: ���� �ε���, end: �� �ε���
// index: ���� ���� �����ϰ��� �ϴ� ���
//dif: ������ ��

void update(int start, int end, int node, int index, int dif) {
	// ���� �ۿ� �ִ� ���
	if (index < start || index > end) return;
	// ���� �ȿ� ������ �������� �ٸ� ���ҵ� ����
	tree[node] += dif;
	if (start == end) return;
	int mid = (start + end) / 2;
	update(start, mid, node * 2, index, dif);
	update(mid + 1, end, node * 2 + 1, index, dif);
}

int main(void) {
	// ���� �� Ʈ���� �ε����� �����ϰ�� ��� �ε��� 0���� �����մϴ�.
	// ���� �� Ʈ�� �����ϱ�
	init(0, NUMBER - 1, 1);
	//���� �� ���ϱ�
	printf("0���� 6������ ���� ��:%d\n", sum(0, NUMBER - 1, 1, 0, 6));
	//���� �� �����ϱ�.
	printf("�ε��� 5�� ���Ҹ� +3��ŭ ����\n");
	update(0, NUMBER - 1, 1, 5, 3);
	//���� �� �ٽ� ���ϱ�
	printf("3���� 6������ ���� ��: %d\n", sum(0, NUMBER - 1, 1, 3, 6));
	system("pause");
}

//�ε��� Ʈ���� ���� �� ���ϱ�.
#include <stdio.h>
#define NUMBER 7

int tree[NUMBER];

int sum(int i) {
	int res = 0;
	while (i > 0) {
		res += tree[i];
		//������ ��Ʈ��ŭ ���鼭 ������ �̵�
		i -= (i&-i)// ������ ��Ʈ�� ���ϴ� �������.
	}
	return res;
}

//Ư�� �ε��� �����ϱ�.
void update(int i, int dif) {
	while (i <= NUMBER) {
		tree[i] += dif;
		//������ ��Ʈ��ŭ ���ϸ鼭 �ڷ� �̵�
		i += (i&-i);
	}
}

// ���� �� ����Լ�.
int getSection(int start, int end) {
	return sum(end) - sum(start - 1);
}

//�ε��� Ʈ�� ���
int main(void) {
	update(1, 7);
	update(2, 1);
	update(3, 9);
	update(4, 5);
	update(5, 6);
	update(6, 4);
	update(7, 1);
	printf("1���� 7������ ���� ��: %d\n", getSection(1, 7));
	printf("�ε��� 6�� ���Ҹ� +3��ŭ ����");
	update(6, 3);
	printf("4���� 7������ ���� ��: %d\n", getSection(4, 7));
	system("pause");
}

//�ܼ� �� ���ڿ� ��Ī
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
			printf("%d��°���� ã�ҽ��ϴ�.\n", i + 1);
		}
	}
	system("pause");
}

//KMP ���ڿ� ��Ī
//���̺� �����:���ڿ� ����
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *parent = "acabacdabac";
char *pattern = "abacdab";

//���̺� �����: ���̺� ���� �Լ� ����
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

//���ڿ� ��Ī �����ϱ�:KMP �Լ� �����ϱ�
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
				printf("[�ε��� %d]���� ��Ī ����\n", i - patternSize + 2);
				j = table[j];
			}
			else {
				j++;
			}
		}
	}
}

//KMP ���ڿ� ��Ī �˰��� ���
int main(void) {
	KMP(parent, pattern);
	system("pause");
}

//��� ī�� ���ڿ� ��Ī
#include <stdio.h>
#include <string.h>

char *parent = "acabacdabac";
char *pattern = "abacdab";

void check(char* parent, char*pattern, int start) {
	//start�� �ؽð��� ��ġ�ϱ� ������ �ε���.
	int found = 1;
	int patternSize = strlen(pattern);
	for (int i = 0; i < patternSize; i++) {
		if (parent[start + i] != pattern[i]) {
			found = 0;
			break;
		}
	}
	if (found) {
		printf("[�ε��� %d���� ��Ī�߻�]\n", start + 1);
	}
}

//��� ī�� �˰��� ����
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
				//���� �ڿ� �ִ� �ͺ��� power�� ���ذ��鼭 �ؽð��� ����
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