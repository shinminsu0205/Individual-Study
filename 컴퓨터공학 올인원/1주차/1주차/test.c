#include <stdio.h> //ǥ�� ����� ��� ����(�׻� �־��ִ� �� ����.)
#define _CRT_SECURE_NO_WARNINGS

int main(void) {
	printf("Hello World!\n");
	int a = 7;
	printf("The number is %d.\n,a");
	scanf("%d", &a); //����� �Լ��� ���� �ǹ����� �������� ������ �������� ���� Ȱ��, & : �޸� �ּҿ� �����ؼ� �����͸� Ȱ���� �� �ֵ��� �ϴ� ������ ������ ����
	printf("�Է��� ���ڴ� %d�Դϴ�.\n", a);
	printf("%%");//%% : %�� �״�� ����ϱ� ���ؼ��� �տ� %�� �ٿ��־�߸� �Ѵ�.
	system("pause");//Ű���带 �Է��ϱ� ������ ���
	return 0; //main �Լ� ���������� �׻� return 0�� �־��־�� �Ѵ�.
}

int main(void) {
	double a; //double : �Ǽ��� ������ 
	scanf("%lf", &a); // scanf�� double�� �Է��� ���� %lf �����Է���, ����� ���� %f �����Է���
	printf("%.2f\n", a); //�Ҽ��� ��°�ڸ�����.
	system("pause");
	return 0;
}

int main(void) {
	int a, b;
	scanf("%d %d", &a, &b); //int�� �ڷ� �Է��� �� %d
	printf("%d %d\n", b, a);
	system("pause");
	return 0;
}

int main(void) {
	int a, b, c;
	scanf("%1d%1d%1d", &a, &b, &c); //�پ��ִ� �� �ڸ� ���� ����� ǥ���ϴ� ��(EX. 587�Է��̸� 5 8 7�� ��������)
	printf("%d %d %d\n", a, b, c);
	system("pause");
	return 0;
}

int main(void) {
	int a, b;
	scanf("%d %d", &a, &b);
	printf("%d + %d = %d\n", a, b, a + b);
	printf("%d - %d = %d\n", a, b, a - b);
	printf("%d / %d = %d\n", a, b, a / b);
	printf("%d % %d = %d\n", a, b, a % b);
	printf("%d * %d = %d\n", a, b, a * b);
	system("pause");
	return 0;
}

int main(void) {
	printf("\"A\tB\tC\tD\"\n");
	system("pause");
	return 0;
}

int main(void) {
	int a, b;
	scanf("%d %d", &a, &b);
	printf("%d\n", a>b); // a>b�̸� 1�� ����ϰ� �ƴϸ� 0�� ����ض�
	system("pause");
	return 0;
}

int main(void) {
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	printf("%d\n", !a);
	prinftf("%d\n", a && b); // a�� b ��� �� ���̴�?
	prinftf("%d\n", (a > b) && (b > c)); //a�� b���� ũ��, b�� c���� ũ��?(a>b>c �̷� ������ ���� a>b�� �ᱣ���� 0 �Ǵ� 1�� ���� ���� 1>c �̷� ������ ��ǻ�Ͱ� �ν��ؼ� �ٸ� ����� ����)
	system("pause");
	return 0;
}

int main(void) {
	int a = 7;
	printf("%d\n", ++a); //8 ���
	printf("%d\n", a++); //8 ��� �� 9 �Է�
	printf("%d\n", ++a); //10���
	system("pause");
	return 0;

}

int main(void) {
	int a = 7, b = 7;
	printf("%d\n", (a == b) ? 100 : -100); //a==b�̸�, 100�� ����ϰ� �ƴϸ� -100�� ����ض�
	system("pause");
	return 0
}

int main(void) {

}

int main(void) {
	printf("�մ��� �� �� �Գ���?");
	int a;
	scanf("%d", &a);
	if (a == 1 || a == 2) {
		printf("2�μ����� �ȳ��մϴ�.");
	}
	else if (a == 3 || a == 4) {
		printf("4�μ����� �ȳ��մϴ�.");
	}
	else {
		printf("���������� �ȳ��մϴ�.\n");
	}
	system("pause");
	return 0
}

int main(void) {
	int size;
	printf("���� �޸� ũ�⸦ �Է��Ͻÿ�. (GB) ");
	scanf("%d", &size);
	if (size >= 16) {
		printf("���� �޸� ũ�Ⱑ ����մϴ�.\n");
	}
	else {
		printf("���� �޸𸮸� �����ϼ���.\n");
	}
	system("pause");
	return 0
}

int main(void) {
	printf("������ �Է��ϼ���.");
	char a;
	scanf("%c", &a);
	switch (a) { //switch ������ ��� �� case�� �����Ǹ� �� �Ʒ��� ��� ���̽� �ش簪�� ����ϱ� ������ �� ���̽����� ���� break�� �ɾ��־�� �ùٸ� �ᱣ���� ���� �� �ִ�.
	case 'A' :
		printf("A �����Դϴ�. \n"); break;
	case 'B' :
		printf("B �����Դϴ�. \n"); break;
	case 'C':
		printf("C �����Դϴ�. \n"); break;
	default:
		printf("������ �ٸ��� �Է��ϼ���. \n");
	}
	system("pause");
	return 0
}

int main(void) {
	printf("���� �Է��ϼ���.");
	int a;
	scanf("%d", &a);
	switch (a) {
	case 1: case 2: case 3:
		printf("��\n"); break;
	case 4: case 5: case 6:
		printf("����\n"); break;
	case 7: case 8: case 9:
		printf("����\n"); break;
	case 10: case 11: case 12:
		printf("�ܿ�\n"); break;
	}
	system("pause");
	return 0;
}

int main(void) {
	for (int i = 0; i <= 100; i++) {
		printf("%d\n", &i);
	}
	system("pause");
	return 0;
}

int main(void) {
	int N, sum = 0;
	printf("N�� �Է��ϼ��� : ");
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		sum = sum + i;
	}
	printf("%d\n", sum);
	system("pause");
	return 0
}

int main(void) {
	int sum = 0;
	for (; 1;) {
		int x;
		scanf("%d", &x);
		if (x == -1) break;
		sum += x;
	}
	printf("%d\n", sum);
	system("pause");
	return 0
}

int main(void) {
	int n;
	char a;
	scanf("%d %c", &n, &a);
	while (n--) { // �� ������ ���� ���� ���̴� �ܿ��θ� ������.
		printf("%c", a);
	}
	system("pause");
	return 0
}

int main(void) {
	int n;
	scanf("%d", &n);
	int i = 1;
	while (i <= 9) {
		printf("%d*%d=%d\n", n, i, n*i);
		i++;
	}
	system("pause");
	return 0;
}

int main(void) {
	int i = 1;
	while (i <= 9) {
		int j = 1;
		while (j <= 9) {
			printf("%d * %d = %d", i, j, i*j);
			j++
		}
		printf("\n");
		i++;
	}
	system("pause");
	return 0;
}

void dice(int input) {
	printf("�����̰� ���� �ֻ���: %d\n", input);
}

int main(void) {
	dice(3);
	dice(5);
	dice(1);
	system("pause");
	return 0;
}

int add(int a, int b) {
	return a + b;
}

int main(void) {
	printf("%d\n", add(10, 20));
	system("pause");
	return 0;
}

void calculator(int a, int b) {
	printf("%d + %d = %d\n", a, b, a + b);
	printf("%d - %d = %d\n", a, b, a - b);
	printf("%d * %d = %d\n", a, b, a * b);
	printf("%d / %d = %d\n", a, b, a / b);
	printf("\n");
}

int main(void) {
	calculator(10, 3);
	calculator(15, 2);
	calculator(18, 4);
	system("pause");
	return 0;
}

int factorial(int a) {
	if (a == 1) return 1;
	else return a * factorial(a - 1);
}

int main(void) {
	int n;
	printf("n ���丮���� ����մϴ�.");
	scanf("%d", &n);
	printf("%d\n", facotrial(n));
	system("pause");
	return 0;
}

int main(void) {
	int a[10] = { 6,5,4,3,9,8,0,1,2,7 };
	int i;
	for (i = 0; i < 10; i++) {
		printf("%d", a[i]);
	}
	system("pause");
	return 0;
}

#include <limits.h>//�� ���� �ּ�, �ִ񰪰� ���� �Ѱ谪���� �����ϴ� ���̺귯��
int main(void) {
	int a[10] = { 0, };
	int i, maxValue = INT_MIN; // �ִ��� ���� �� ���� ���� ����.
	for (i = 0; i < 10; i++) {
		if (maxValue<a[i]) maxValue = a[i]
	}
	printf("%d\n",maxValue)
	system("pause")
	return 0;
}
int main(void) {
	char a[20]; //���ڿ��� ���� + �迭�̱� ������ ��� ������ ũ�⳪ �Ǵ� �迭���� �̸� �������־�� ��.(C++������ string���� ������ �ż� �̷� �ʿ� X)
	scanf("%s", &a);
	printf("%s\n", a);
	system("pause");
	return 0;
}

int main(void) {
	char a[20] = "Hello World";
	a[4] = ',';//���ڿ� ����
	printf("%s\n", a); 
	system("pause");
	return 0;
}

int main(void) {
	char a[] = "Hello World";
	int count = 0;
	for (int i = 0; i <= 10; i++) {
		if (a[i] == 'l') count++;
	}
	printf("%d\n", count);
	system("pause");
	return 0;
}

int main(void) {
	int a = 5;
	int *b = &a;
	printf("%d\n", *b);
	system("pause");
	return 0;
}

int main(void) {
	int a[] = { 1,2,3,4,5,6,7,8,9 };
	int i;
	for (i = 0; i < 10; i++) {
		printf("%d\n", &a[i]);
	}
	system("pause");
	return 0;
}

int main(void) {
	int a = 5;
	int *b = &a;
	int **c = &b;
	printf("%d\n", **c);
	system("pause");
	return 0;
}

int main(void) {
	int a[] = { 1,2,3,4,5,6,7,8,9,10 };
	int *b = a; //a��� �迭 ��ü�� �ּڰ����� Ȱ���ϰڴ�.
	printf("%d\n", b[2]);
	system("pause");
	return 0;
}

int main(void) {
	char a = 65; // ascii code number�� �ٷ� ���ڸ� �Է�
	//0~9 �� 48 ~ 57, A�� 65, a�� 97
	printf("%c\n", a);
	system("pause");
	return 0;
}

int main(void) {
	char a = getchar(); //����ڷκ��� ���ڸ� �Է¹޴� ��.
	printf("%c\n", a);
	system("pause");
	return 0;
}

int main() {
	int a; char c;
	scanf("%d", &a);
	printf("%d\n", a);
	int temp;
	//�� �ھ� �޾Ƽ� ������ ��(End Of File)�̰ų� ���๮��('\n')�� ������ �Է��� ���߹Ƿ� �׻� �Է� ���۸� ����ϴ�.
	//�̰� ������ �� ���� �� �� �̻��� �Է��� �ް� ���α׷��� ������ ���ʷ� ���� �ϳ��� �Է°��� ����ϰ� ���α׷��� ����˴ϴ�.
	while ((temp = getchar() != EOF && temp != '\n')) { }
	scanf("%c", &c);
	printf("%c\n", c);
	system("pause");
	return 0;
}

int main(void) {
	char*a = "Hello World";
	//������ ��ü�� ���ڿ��� ����. �̰��� ���ڿ� ��Ʈ���̶�� �մϴ�.
	//�����͸� �ٲ� ���� ������ ���ڿ� ��Ʈ���� �ٲ� ���� ����.
	printf("%s\n", a);
	system("pause");
	return 0;
}
int main(void) {
	char*a = "Hello World";
	printf("%c\n", a[1]);
	printf("%c\n", a[4]);
	printf("%c\n", a[8]);
	system("pause");
	return 0;
}

int main(void) {
	char a[100];
	gets(a); //scanf�ʹ� �ٸ� �Է� �Լ�(������� ���ڷ� �ν���.)
	printf("%s\n", a);
	system("pause");
	return 0;
}

int main(void) {
	char a[100];
	gets_s(a, sizeof(a));
	//gets �Լ��� ����� �迭�� ũ�⺸�� ũ�� �迭�� �Է��ص� �Է��� �����ؼ� ���Ȼ����� �����.
	//gets_s �Լ��� ����� �迭�� ũ�⸸ŭ�� �Է��� �����ϵ��� ������.
	printf("%s\n", a);
	system("pause");
	return 0;
}

int main(void) {
	char a[20] = "Dongbin Na";
	printf("���ڿ��� ����:%d\n", strlen(a));
	system("pause");
	return 0;
}

int main(void) {
	char a[20] = "Dongbin Na";
	char b[20] = "Seokjoon Hong";
	printf("�� �迭�� ���� �� ��:%d\n", strcmp(a, b));
	system("pause");
	return 0;
}

int main(void) {
	char a[30] = "My name is";
	char b[20] = "Dongbin Na";
	strcat(a, b);
	//a�� b�� ���̴� ���̱� ������ a�� �迭 ũ�⸦ �÷��־�� ��.
	printf("%s\n", a);
	system("pause");
	return 0;
}
int main(void) {
	char a[20] = "I like you";
	char b[20] = "like";
	printf("ã�� ���ڿ�: %s\n", strstr(a, b));
	// a���� b ������ �͵��� ��� ã�ƶ�,��� �Լ�
	//�ᱣ���� like you
	system("pause");
	return 0;
}

int a = 5;//��������
void changeValue() {
	a = 10;
}
int main(void) {
	printf("%d\n", a);
	changeValue();
	printf("%d\n", a);
	system("pause");
	return 0;
}

int main(void) {
	int a = 7;
	if (1) {
		int a = 5; // ���������� �� ��Ͽ��� �Լ��� ������� ������ �տ� ����� a�� 7�� ����
		// a=5�� �����Ű���� int a = 5�� �ƴ϶� �׳� a=5�� �ϸ� ��.
	}
	printf("%d", a);
	system("pause");
	return 0;
}

void process() {
	static int a = 5; //���α׷��� ����ʰ� ���ÿ� a=5�� �޸𸮻� ����.
	a = a + 1; //process �Լ��� ������ ������ +1��, �տ� ���õ� static int�� ó�� ���ķδ� ����.
	printf("%d\n", a);
}
int main(void) {
	process();
	process();
	process();
	system("pause");
	return 0;

}
int main(void) {
	register int a = 10, i; //�������� ������ Ȱ���ϸ� ���� �� ����.
	//��, �������� ������ CPU�� �������͸� ���� Ȱ���ϴ� ���̶�
	//�����Ϸ��� ��� �۵��ϴ��Ŀ� ���� ���������� ������ �� �� ���� ����.
	for (i = 0; i < a; i++) {
		printf("%d", i);
	}
	system("pause");
	return 0;
}

void add(int a, int b) {
	a = a + b;
	printf("%d\n", a); //a=17�� ����
}
int main(void) {
	int a = 7;
	add(a, 10);
	printf("%d\n", a); //a = 7�� ����. ���� ���� ���� ����̱� ������
	//add �Լ��� �ᱣ���� a�� ����ϴ� �� �ƴ϶�, ����� a�� 7�� �״�� �����.
	system("pause");
	return 0;
}

//������ ���� ���޹��
void add(int*a) {
	*a = (*a) + 10; //�����ͷ� ���� �����ؼ� �����͸� �ٲ������ ��.
}
int main(void) {
	int a = 7;
	add(&a);
	printf("%d\n", a);
	system("pause");
	return 0;
}

int a[3][3] = { {1,2,3},{4,5,6},{7,8,9} };
int main(void) {
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			printf("%d", a[i][j]);
		}
		printf("\n");
	}
	system("pause");
	return 0;
}

int a[2][3][3] = { {{1,2,3},{4,5,6},{7,8,9}},{{1,2,3},{4,5,6},{7,8,9}} }
int main(void) {
	int i, j, k;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 3; j++) {
			for (k = 0; k < 3; k++) {
				printf("%d", a[i][j][k]);
			}
			printf("\n")
		}
		printf("\n")
	}
	system("pause");
	return 0;
}

int main(void) {
	int a[5] = { 1,2,3,4,5 };//�迭�� ������ó�� ���� �ͺ��ٴ� �����͸�
							// �迭ó�� ���� ��찡 �� ����.
	// �迭�� �̸��� �迭�� ù��° ���� �ּҰ��� �Ȱ���.
	int *b = a;
	printf("%d\n", b[2]);
	system("pause");
	return 0;
}

int main(void) {
	double b[10];
	printf("%d %d\n", b, b + 9);
	system("pause");
	return 0;
}

int main(void) {
	int a[5] = { 1,2,3,4,5 };
	int *p = a;
	printf("%d\n", *(p++)); //1
	printf("%d\n", *(++p)); //3
	printf("%d\n", *(p+2)); //5
	system("pause");
	return 0;
}

int main(void) {
	int a[2][5] = { {1,2,3,4,5} {6,7,8,9,10} };
	int(*p)[5] = a[1]; //6�� ����Ű�� �ִ� �ּڰ��� ��´�.
	int i;
	for (i = 0; i < 5; i++) {
		printf("%d", p[0][i]);//p�� {6,7,8,9,10}�� ����Ű�� ����.
	}
	system("pause");
	return 0;
}

#include <stdlib.h> //���� �޸� �Ҵ� �Լ��� malloc �Լ��� ���Ե� ��Ű��
int main (void){
	int *a = malloc(sizeof(int));
	printf("%d\n", a);
	a = malloc(sizeof(int));
	printf("%d\n", a);
	system("pause");
	return 0;
}

int main(void) {
	int *a = malloc(sizeof(int));
	printf("%d\n", a);
	free(a); //�޸� �Ҵ� ����
			// ���� �޸� �Ҵ��� �� ������ ����Ǳ� ������, ���� �޸� ������ ���־����.
	a = malloc(sizeof(int));
	printf("%d\n", a);
	free(a);
	system("pause");
	return 0;
}

// �������� ���ڿ� ó���ϱ�
#include <string.h> //�������ڿ� ó���� ���� Memset �Լ��� ����ִ� ��Ű��
int main(void) {
	char *a = malloc(100); //100����Ʈ�� �Ҵ��ϰڴ�.
	memset(a, 'A', 100); //100����Ʈ�� ���� A�θ� ä��ڴ�.
	for (int i = 0; i < 100; i++) {
		printf("%c", a[i]);
	}
	system("pause");
	return 0;
}

int main(void) {
	int **p = (int**)malloc(sizeof(int*) * 3);
	//sizeof(int*)�� �� ���� ���� �޴� �������̰�
	// �츮�� �� ���� ���� �ް� ������ *3�� �ؼ� �� ���� �޵��� ���ִ� ��.
	//�װ� **p��� ���� �����ͷ� ������ �� �̴ϴ�.
	for (int i = 0; i < 3; i++) {
		*(p + i) = (int*)malloc(sizeof(int) * 3);
		//*p�� ù���� �޴� ���̴ϱ� �ű�� +1.+2�� �ؼ� 3���� ���� ��� �޵��� �ϰ�,
		//�׷� �� �ึ�� sizeof(int)*3���� ���� �ϳ��� �޵��� ���ִ� ��.
		// �� 3*3 ����̴�.
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			*(*(p + i) + j) = i * 3 + j;
			//*(p+i)�� ���� ��Ÿ���� �ű⿡ +j�� �ٿ��� ���� �˷��ش�.
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%d", *(*(p + i) + j));
		}
		printf("\n");
	}
	system("pause");
	return 0;
}

void function() {
	printf("It's my function.");
}
int main(void) {
	printf("%d\n", function);
	//�׳� �Լ��� �̸��� �־ ����ϵ��� ����� �ּڰ��� ��ȯ�Ѵ�.
	system("pause");
	return 0;
}

//�Ű����� �� ��ȯ �ڷ����� ���� �Լ� ������
void myFunction() {
	printf("It's my function.\n");
}
void yourFunction() {
	printf("It's your function.\n");
}
int main(void) {
	void(*fp)() = myFunction;
	fp();
	fp = yourFunction;
	fp();
	system("pause");
	return 0;
}

//�Ű����� �� ��ȯ�ڷ����� �ִ� �Լ� ������
int add(int a, int b) {
	return a + b;
}
int sub(int a, int b) {
	return a - b;
}
int main(void) {
	int(*fp)(int, int) = add;
	printf("%d\n", fp(10, 3));
	fp = sub;
	printf("%d\n", fp(10, 3));
	system("pause");
	return 0;
}

//�Լ������͸� ��ȯ�Ͽ� ����ϱ�
int add(int a, int b) {
	return a + b;
}
int(*process(char* a))(int, int) {
	printf("%s\n", a);
	return add;
}
int main(void) {
	printf("%d\n", process("10�� 20�� ���غ��ڽ��ϴ�.")(10, 20)); 
	//���� ���� �� ������ process��� �Լ��� �̹� �� �׷���.
	system("pause");
	return 0;
}

struct Student {//����ü!
	char studnetID[10];
	char name[10];
	int grade;
	char major[100];
};

int main(void) {
	struct Student s; //����ü��������
	strcpy(s.studnetID, "2016312147");
	strcpy(s.name, "�Źμ�");
	s.grade = 4;
	strcpy(s.major, "�۷ι��濵�а�");
	printf("�й�: %s\n", s.studentID);
	printf("�̸�: %s\n", s.name);
	printf("�г�: %d\n", s.grade);
	printf("�а�: %s\n", s.major);
	system("pause");
	return 0;
}

typedef struct {
	char studentID[10];
	char name[10];
	int grade;
	char major[100];
} Student;

int main(void) {
	Student *s = malloc(sizeof(Student));
	//�޸� �ּҿ� ����ü�� �Ҵ� �Ʊ� ������
	strcpy(s->studentID, "2016312147");
	strcpy(s->name, "�Źμ�");
	s->grade = 4;
	strcpy(s->major, "�۷ι��濵�а�");
	printf("�й�:%s\n", s->studentID);
	printf("�̸�:%s\n", s->name);
	printf("�г�:%d\n", s->grade);
	printf("�а�:%s\n", s->major);
	//.�� �ƴ϶�->�� ǥ��.
	system("pause");
	return 0;
}

int main(void) {
	char s[20] = "Hello World";
	FILE *fp;
	fp = open("temp.txt", "w");
	fprintf(fp, "%s\n", s);
	fclose(fp);
	return 0;
}

typedef struct {
	char name[20];
	int score;
}Student;
int main(void) {
	int n, sum = 0;
	FILE *fp;
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &n);
	Student *students = (Student*)malloc(sizeof(Student)*n);
	for (int i = 0; i < n; i++) {
		fscanf(fp, "%s%d", &((students + i)->name), &((students + i)->score));
		printf("�̸�:%s, ����: %d\n", (students + i)->name, (students + i)->score);
	}
	system("pause");
	return 0;
}

int main(void) {
	int n, sum = 0;
	FILE *fp;
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &n);
	Student *students = (Student*)malloc(sizeof(Student)*n);
	for (int i = 0; i < n; i++) {
		fscanf(fp, "%s %d", &((students + i)->name), &((students + i)->score));
	}
	for (int i = 0; i < n;  i++) {
		sum += (students + i)->score;
	}
	free(students);
	flcose(fp);
	printf("���� ���: %.2f\n", (double)sum / n);
	system("pause");
	return 0;
}

#include "test.h" //���� �������� ��� ����
//�ǵ�ġ �ʰ� ������ �ҷ����� �Ǹ� ���α׷� ������ �� �� ����.
int main(void) {
	printf("%d\n", add(3,7));
	system("pause");
	return 0;
}

#define PI 3.1415926535 //define�� ���ؼ� ��ũ�η� �ʿ��� �͵��� �̸� �����ϴ� ��.
int main(void) {
	int r = 10;
	printf("���� �ѷ�: %.2f", 2 * PI*r);
	system("pause");
	return 0;
}

#define POW(x) (x*x)
int main(void) {
	int x = 10;
	printf("10�� ������ : %d", POW(x));
	system("pause");
	return 0;
}

#define ll long long
#define ld long double // �� �ΰ��� ���α׷��ӵ��� ���� ���� ���� ��ũ�� ��ó����
// �� �� ġ��� �����Ƽ� �̷��� �����
int main(void) {
	ll a = 987654321000;
	ld b = 100.5054;
	printf("%.1f\n", a*b);
	system("pause");
	return 0;
}

#include "test.h"
#include "test.h"
