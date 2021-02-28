#include <stdio.h> //표준 입출력 방식 도입(항상 넣어주는 게 좋음.)
#define _CRT_SECURE_NO_WARNINGS

int main(void) {
	printf("Hello World!\n");
	int a = 7;
	printf("The number is %d.\n,a");
	scanf("%d", &a); //취약한 함수라서 자주 실무에서 사용되지는 않지만 교육에서 자주 활용, & : 메모리 주소에 접근해서 데이터를 활용할 수 있도록 하는 일종의 포인터 역할
	printf("입력한 숫자는 %d입니다.\n", a);
	printf("%%");//%% : %를 그대로 출력하기 위해서는 앞에 %를 붙여주어야만 한다.
	system("pause");//키보드를 입력하기 전까지 대기
	return 0; //main 함수 마지막에는 항상 return 0를 넣어주어야 한다.
}

int main(void) {
	double a; //double : 실수형 데이터 
	scanf("%lf", &a); // scanf로 double을 입력할 때는 %lf 형식입력자, 출력할 때는 %f 형식입력자
	printf("%.2f\n", a); //소수점 둘째자리까지.
	system("pause");
	return 0;
}

int main(void) {
	int a, b;
	scanf("%d %d", &a, &b); //int형 자료 입력할 때 %d
	printf("%d %d\n", b, a);
	system("pause");
	return 0;
}

int main(void) {
	int a, b, c;
	scanf("%1d%1d%1d", &a, &b, &c); //붙어있는 세 자릿 수를 나누어서 표현하는 법(EX. 587입력이면 5 8 7로 나누어짐)
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
	printf("%d\n", a>b); // a>b이면 1을 출력하고 아니면 0을 출력해라
	system("pause");
	return 0;
}

int main(void) {
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	printf("%d\n", !a);
	prinftf("%d\n", a && b); // a와 b 모두 참 값이니?
	prinftf("%d\n", (a > b) && (b > c)); //a도 b보다 크고, b도 c보다 크니?(a>b>c 이런 식으로 쓰면 a>b의 결괏값인 0 또는 1이 먼저 들어가서 1>c 이런 식으로 컴퓨터가 인식해서 다른 결과가 나옴)
	system("pause");
	return 0;
}

int main(void) {
	int a = 7;
	printf("%d\n", ++a); //8 출력
	printf("%d\n", a++); //8 출력 후 9 입력
	printf("%d\n", ++a); //10출력
	system("pause");
	return 0;

}

int main(void) {
	int a = 7, b = 7;
	printf("%d\n", (a == b) ? 100 : -100); //a==b이면, 100을 출력하고 아니면 -100을 출력해라
	system("pause");
	return 0
}

int main(void) {

}

int main(void) {
	printf("손님이 몇 명 왔나요?");
	int a;
	scanf("%d", &a);
	if (a == 1 || a == 2) {
		printf("2인석으로 안내합니다.");
	}
	else if (a == 3 || a == 4) {
		printf("4인석으로 안내합니다.");
	}
	else {
		printf("대형석으로 안내합니다.\n");
	}
	system("pause");
	return 0
}

int main(void) {
	int size;
	printf("메인 메모리 크기를 입력하시오. (GB) ");
	scanf("%d", &size);
	if (size >= 16) {
		printf("메인 메모리 크기가 충분합니다.\n");
	}
	else {
		printf("메인 메모리를 증설하세요.\n");
	}
	system("pause");
	return 0
}

int main(void) {
	printf("학점을 입력하세요.");
	char a;
	scanf("%c", &a);
	switch (a) { //switch 구문의 경우 한 case가 만족되면 그 아래의 모든 케이스 해당값을 출력하기 때문에 각 케이스마다 끝에 break를 걸어주어야 올바른 결괏값을 얻을 수 있다.
	case 'A' :
		printf("A 학점입니다. \n"); break;
	case 'B' :
		printf("B 학점입니다. \n"); break;
	case 'C':
		printf("C 학점입니다. \n"); break;
	default:
		printf("학점을 바르게 입력하세요. \n");
	}
	system("pause");
	return 0
}

int main(void) {
	printf("월을 입력하세요.");
	int a;
	scanf("%d", &a);
	switch (a) {
	case 1: case 2: case 3:
		printf("봄\n"); break;
	case 4: case 5: case 6:
		printf("여름\n"); break;
	case 7: case 8: case 9:
		printf("가을\n"); break;
	case 10: case 11: case 12:
		printf("겨울\n"); break;
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
	printf("N을 입력하세요 : ");
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
	while (n--) { // 이 구문은 정말 자주 쓰이니 외워두면 유용함.
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
	printf("동빈이가 던진 주사위: %d\n", input);
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
	printf("n 팩토리얼을 계산합니다.");
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

#include <limits.h>//각 값의 최소, 최댓값과 같은 한계값들을 포함하는 라이브러리
int main(void) {
	int a[10] = { 0, };
	int i, maxValue = INT_MIN; // 최댓값을 구할 때 가장 많이 쓰임.
	for (i = 0; i < 10; i++) {
		if (maxValue<a[i]) maxValue = a[i]
	}
	printf("%d\n",maxValue)
	system("pause")
	return 0;
}
int main(void) {
	char a[20]; //문자열은 문자 + 배열이기 때문에 어느 정도의 크기나 되는 배열인지 미리 선언해주어야 함.(C++에서는 string으로 제공이 돼서 이럴 필요 X)
	scanf("%s", &a);
	printf("%s\n", a);
	system("pause");
	return 0;
}

int main(void) {
	char a[20] = "Hello World";
	a[4] = ',';//문자열 변경
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
	int *b = a; //a라는 배열 자체를 주솟값으로 활용하겠다.
	printf("%d\n", b[2]);
	system("pause");
	return 0;
}

int main(void) {
	char a = 65; // ascii code number로 바로 문자를 입력
	//0~9 는 48 ~ 57, A는 65, a는 97
	printf("%c\n", a);
	system("pause");
	return 0;
}

int main(void) {
	char a = getchar(); //사용자로부터 문자를 입력받는 것.
	printf("%c\n", a);
	system("pause");
	return 0;
}

int main() {
	int a; char c;
	scanf("%d", &a);
	printf("%d\n", a);
	int temp;
	//한 자씩 받아서 파일의 끝(End Of File)이거나 개행문자('\n')를 만나면 입력을 멈추므로 항상 입력 버퍼를 지웁니다.
	//이거 없으면 한 번에 두 개 이상의 입력을 받고 프로그램을 돌리면 최초로 받은 하나의 입력값만 출력하고 프로그램이 종료됩니다.
	while ((temp = getchar() != EOF && temp != '\n')) { }
	scanf("%c", &c);
	printf("%c\n", c);
	system("pause");
	return 0;
}

int main(void) {
	char*a = "Hello World";
	//포인터 자체를 문자열에 넣음. 이것을 문자열 리트럴이라고 합니다.
	//포인터를 바꿀 수는 있지만 문자열 리트럴을 바꿀 수는 없음.
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
	gets(a); //scanf와는 다른 입력 함수(공백까지 문자로 인식함.)
	printf("%s\n", a);
	system("pause");
	return 0;
}

int main(void) {
	char a[100];
	gets_s(a, sizeof(a));
	//gets 함수는 선언된 배열의 크기보다 크게 배열을 입력해도 입력이 가능해서 보안상으로 취약함.
	//gets_s 함수는 선언된 배열의 크기만큼만 입력이 가능하도록 강제함.
	printf("%s\n", a);
	system("pause");
	return 0;
}

int main(void) {
	char a[20] = "Dongbin Na";
	printf("문자열의 길이:%d\n", strlen(a));
	system("pause");
	return 0;
}

int main(void) {
	char a[20] = "Dongbin Na";
	char b[20] = "Seokjoon Hong";
	printf("두 배열의 사전 순 비교:%d\n", strcmp(a, b));
	system("pause");
	return 0;
}

int main(void) {
	char a[30] = "My name is";
	char b[20] = "Dongbin Na";
	strcat(a, b);
	//a에 b를 붙이는 것이기 때문에 a의 배열 크기를 늘려주어야 함.
	printf("%s\n", a);
	system("pause");
	return 0;
}
int main(void) {
	char a[20] = "I like you";
	char b[20] = "like";
	printf("찾은 문자열: %s\n", strstr(a, b));
	// a에서 b 이하의 것들을 모두 찾아라,라는 함수
	//결괏값은 like you
	system("pause");
	return 0;
}

int a = 5;//전역변수
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
		int a = 5; // 지역변수라서 이 블록에서 함수가 시행되지 않으면 앞에 선언된 a인 7로 나옴
		// a=5를 적용시키려면 int a = 5가 아니라 그냥 a=5를 하면 됨.
	}
	printf("%d", a);
	system("pause");
	return 0;
}

void process() {
	static int a = 5; //프로그램이 실행됨과 동시에 a=5가 메모리상에 적재.
	a = a + 1; //process 함수를 실행할 때마다 +1씩, 앞에 선택된 static int는 처음 이후로는 무시.
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
	register int a = 10, i; //레지스터 변수를 활용하면 조금 더 빠름.
	//단, 레지스터 변수는 CPU의 레지스터를 직접 활용하는 것이라서
	//컴파일러가 어떻게 작동하느냐에 따라 성공적으로 진행이 안 될 수도 있음.
	for (i = 0; i < a; i++) {
		printf("%d", i);
	}
	system("pause");
	return 0;
}

void add(int a, int b) {
	a = a + b;
	printf("%d\n", a); //a=17이 나옴
}
int main(void) {
	int a = 7;
	add(a, 10);
	printf("%d\n", a); //a = 7이 나옴. 값에 의한 전달 방식이기 때문에
	//add 함수의 결괏값인 a를 출력하는 게 아니라, 선언된 a인 7을 그대로 출력함.
	system("pause");
	return 0;
}

//참조에 의한 전달방식
void add(int*a) {
	*a = (*a) + 10; //포인터로 직접 접근해서 데이터를 바꿔버리는 것.
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
	int a[5] = { 1,2,3,4,5 };//배열을 포인터처럼 쓰는 것보다는 포인터를
							// 배열처럼 쓰는 경우가 더 많다.
	// 배열의 이름은 배열의 첫번째 값의 주소값과 똑같음.
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
	int(*p)[5] = a[1]; //6을 가리키고 있는 주솟값을 담는다.
	int i;
	for (i = 0; i < 5; i++) {
		printf("%d", p[0][i]);//p는 {6,7,8,9,10}을 가리키고 있음.
	}
	system("pause");
	return 0;
}

#include <stdlib.h> //동적 메모리 할당 함수인 malloc 함수가 포함된 패키지
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
	free(a); //메모리 할당 해제
			// 동적 메모리 할당은 힙 영역에 저장되기 때문에, 따로 메모리 해제를 해주어야함.
	a = malloc(sizeof(int));
	printf("%d\n", a);
	free(a);
	system("pause");
	return 0;
}

// 동적으로 문자열 처리하기
#include <string.h> //동적문자열 처리를 위한 Memset 함수가 들어있는 패키지
int main(void) {
	char *a = malloc(100); //100바이트를 할당하겠다.
	memset(a, 'A', 100); //100바이트를 전부 A로만 채우겠다.
	for (int i = 0; i < 100; i++) {
		printf("%c", a[i]);
	}
	system("pause");
	return 0;
}

int main(void) {
	int **p = (int**)malloc(sizeof(int*) * 3);
	//sizeof(int*)는 한 개의 행을 받는 포인터이고
	// 우리는 세 개의 행을 받고 싶으니 *3을 해서 세 개를 받도록 해주는 것.
	//그게 **p라는 이중 포인터로 선언이 된 겁니다.
	for (int i = 0; i < 3; i++) {
		*(p + i) = (int*)malloc(sizeof(int) * 3);
		//*p는 첫행을 받는 것이니까 거기다 +1.+2를 해서 3개의 행을 모두 받도록 하고,
		//그럼 각 행마다 sizeof(int)*3으로 열을 하나씩 받도록 해주는 것.
		// 총 3*3 행렬이다.
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			*(*(p + i) + j) = i * 3 + j;
			//*(p+i)가 행을 나타내고 거기에 +j를 붙여서 열을 알려준다.
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
	//그냥 함수의 이름을 넣어서 출력하도록 만들면 주솟값을 반환한다.
	system("pause");
	return 0;
}

//매개변수 및 반환 자료형이 없는 함수 포인터
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

//매개변수 및 변환자료형이 있는 함수 포인터
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

//함수포인터를 반환하여 사용하기
int add(int a, int b) {
	return a + b;
}
int(*process(char* a))(int, int) {
	printf("%s\n", a);
	return add;
}
int main(void) {
	printf("%d\n", process("10과 20을 더해보겠습니다.")(10, 20)); 
	//오류 나는 거 위에서 process라는 함수를 이미 썼어서 그래요.
	system("pause");
	return 0;
}

struct Student {//구조체!
	char studnetID[10];
	char name[10];
	int grade;
	char major[100];
};

int main(void) {
	struct Student s; //구조체변수선언
	strcpy(s.studnetID, "2016312147");
	strcpy(s.name, "신민수");
	s.grade = 4;
	strcpy(s.major, "글로벌경영학과");
	printf("학번: %s\n", s.studentID);
	printf("이름: %s\n", s.name);
	printf("학년: %d\n", s.grade);
	printf("학과: %s\n", s.major);
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
	//메모리 주소에 구조체가 할당 됐기 때문에
	strcpy(s->studentID, "2016312147");
	strcpy(s->name, "신민수");
	s->grade = 4;
	strcpy(s->major, "글로벌경영학과");
	printf("학번:%s\n", s->studentID);
	printf("이름:%s\n", s->name);
	printf("학년:%d\n", s->grade);
	printf("학과:%s\n", s->major);
	//.이 아니라->로 표시.
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
		printf("이름:%s, 성적: %d\n", (students + i)->name, (students + i)->score);
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
	printf("점수 평균: %.2f\n", (double)sum / n);
	system("pause");
	return 0;
}

#include "test.h" //내가 만들어놓은 헤더 파일
//의도치 않게 여러번 불러오게 되면 프로그램 오류가 뜰 수 있음.
int main(void) {
	printf("%d\n", add(3,7));
	system("pause");
	return 0;
}

#define PI 3.1415926535 //define을 통해서 매크로로 필요한 것들을 미리 설정하는 것.
int main(void) {
	int r = 10;
	printf("원의 둘레: %.2f", 2 * PI*r);
	system("pause");
	return 0;
}

#define POW(x) (x*x)
int main(void) {
	int x = 10;
	printf("10의 제곱은 : %d", POW(x));
	system("pause");
	return 0;
}

#define ll long long
#define ld long double // 위 두개는 프로그래머들이 정말 많이 쓰는 매크로 전처리기
// 걍 다 치기는 귀찮아서 이렇게 쓴대요
int main(void) {
	ll a = 987654321000;
	ld b = 100.5054;
	printf("%.1f\n", a*b);
	system("pause");
	return 0;
}

#include "test.h"
#include "test.h"
