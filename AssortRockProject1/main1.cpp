//단축키
// Ctrl + k,c : 광범위 주석설정
// Ctrl + k,u : 광범위 주식해제
// Alt + Drag
// 디버깅 : F5(n번 누르면 n번 중단점까지 실행), F9(중단점설정,직전까지수행), F10(디버깅중, 구문수행), F11(디버깅중, 구문수행), shift + F5(디버깅종료)


#include <stdio.h>

#define HUNGRY  0x1 
#define THIRSTY 0x2
#define TIRED   0x4
#define FIRE	0x8

#define COLD	0x10
#define POISON	0x20
#define POISON1	0x30
#define POISON2	0x40

#define POISON3	0x100 
#define POISON4	0x200
#define POISON5	0x300
#define POISON6	0x800
//전처리기능을 통해서 가독성+유지보수에 이점을 얻을 수 있다.비트는 칸이기 때문에 2의 배수로 설정
//0x 16진수표현의미

//변수
//지역변수(함수안), 전역변수, 정적변수(3가지), 외부변수(컴파일 시)

int global = 0;//전역변수(함수밖의 변수)

int Add1(int left, int right)
{
	return left + right;
}

int Factorial(int _oNum)
{
	int oValue = 1;

	for (int j = 0; j < _oNum - 1; ++j)
	{
		oValue *= (j + 2);
	}

	return oValue;
}

//재귀함수(Recursion) : 가독성 좋고 구현이 용이, 반드시 탈출구가 있어야함, 스택 큐 활용해서 반복문으로도 구현가능
//재귀함수 버전 팩토리얼
int Factorial_Re(int _oNum)
{
	if (1 == _oNum)
	{
		return 1;
	}

	return _oNum * Factorial_Re(_oNum - 1);

}

//피보나치수열 1 1 2 3 5 8 13 21 34 55...
int Fibonacci(int _iNum)
{
	if (1 == _iNum || 2 == _iNum)
	{
		return 1;
	}

	int oPrev1 = 1;
	int oPrev2 = 1;
	int oValue = 0;

	for (int i = 0; i < _iNum - 2; ++i)
	{
		oValue = oPrev1 + oPrev2;
		oPrev1 = oPrev2;
		oPrev2 = oValue;

	}

	return oValue;
}

//재귀함수 버전 피보나치 수열 >> 느려지는문제 꼬리 재귀 등 기술 활용
int Fibonacci_Re(int _iNum)
{
	if (1 == _iNum || 2 == _iNum)
	{
		return 1;
	}

	return Fibonacci_Re(_iNum - 1) + Fibonacci_Re(_iNum - 2);
}


//사용자정의자료형 (c스타일로)
typedef struct _tagMyST
{
	int a;
	float f;
}MYST;

typedef struct _tagBig
{
	MYST k;
	int i;
	float c;
}BIG;

typedef int INT;

typedef struct NewStruct
{
	int a;
	short s;
}NEWST;


//함수(기능,Function)
int main()
{
	//자료형DataType : 정수형 >> unsigned(양수의) + char(1),short(2),int(4),long(4),long long(8)/ 실수형 >> float(4),double(8)
	//1Byte == 8bit == 2^8 == 256경우, ∴int == 4Byte == 32Bit == 1024경우 == 2^10 == 1KB
	//KB < MB < GB < TB 각1024배씩 증가
	// = 는 대입의 의미, == 같다의 의미
	int i = 0; 	//int : 자료형, i : 임의변수

	//음수의 표기와 저장 >> 뺄셈의 계산시, 음수의 덧셈으로 계산하여 양수로 나오는 값으로 음수를 저장함 
	//메모리를 0으로 만들어주는 양수값+음수부호(MSB,Most Significant Bit)로 표기, [2의 보수법]
	unsigned char c = 0;
	c = 0;
	c = 255;
	c = -1; //메모리상태는 같으나 unsigned char임으로 255로 읽음

	signed char c1 = 0;
	c1 = -128;
	c1 = 127;
	c1 = 255; //메모리상태는 같으나 signed char임으로 -1로 읽음,  
	
	//실수형 데이터는 [부동소수점] 방식으로 표현, MSB+지수파트+가수파트, 정밀도에 의존 근사값으로 표현
	//실수표현뒤에 f를 붙이면 float타입, 안붙이면 double타입 간주

	//데이터는 같은 형끼리 연산이 원칙, 섞일 경우는 변환자 사용
	float f = 10.2415f + float(20);

	//연산자 : {산술연산자 + - * / %(모듈러스,나머지)} {증감연산자 ++ -- } {대입연산자 = }
	//우선순위 : x++ x--, ++x --x, * /, + -, << >>, < <= > >=, == !=, 비트AND연산 &, 비트XOR연산 ^, 비트OR연산 |, && , ||, ?:, 대입연산
	int data = 10 + 10;
	data + 20; //연산만하고 대입x
	data += 20; //data = data + 20;

	//실수형 데이터는 %모듈러스 연산이 불가
	
	//증감연산자는 '한단계 증가/감소'를 수행, 앞/뒤에 위치하여 전위(전치)/후위(후치) 연산순서를 최우선 혹은 최후순위로 정해줄수 있음
	data = 0;
	int a;
	a = 10;
	data=++a;
	data=a++;

	//논리 연산자(true/false) : !(역), &&(곱), ||(합)
	//True == 0이 아닌 값
	//bool 참 거짓만을 위한 1byte 자료형
	bool turefalse = false; //==0
	bool IsTrue = 100; //==1

	IsTrue = true;
	IsTrue = !IsTrue;

	int iTrue = 0;
	iTrue = !iTrue;

	iTrue = 0 && 200;
	iTrue = 0 || 300;
	iTrue = 0 || 0;

	//비교 연산자 : ==. !=, <, >, <=, >=, 


	//구문 if_else if_else, switch case
	data = 0;

	if (100 && 200)
	{
		data = 100;
	}
	else if (300)
	{
		
	}
	else if (400)
	{
	
	}
	else //마지노선(다안되면 실행개념), 없어도됨
	{
	
	}

	int iTest = 20;
	switch (iTest) //코드가 좀 더 간결, 경우의 수를 누적적으로 적용하고 싶을때(if구문은 논리연산자써야함)
	{
	case 10:
	case 20:
	case 30:
		break; //의도된 것이 아니라면 짝 잘 맞춰야함
	case 40:
			break;
	default: //else개념
		break;
	}

	//same-ex
	if (iTest == 10 || iTest == 20 || iTest == 30)
	{

	}
	else if (true)
	{

	}
	else
	{

	}

	//삼항 연산자 :?
	// ~~~? 참실행 : 거짓실행
	iTest == 20 ? iTest = 100 : iTest == 200; // == 넣으므로써 문법오류는 아니나 참거짓으로 결과나오게됨

	if (iTest==20)
	{
		iTest = 100;
	}
	else
	{
		iTest == 200;
	}

	//비트 연산자, 비트단위로 연산시 << >>(쉬프트:비트를 한칸씩 밀기), &(곱) |(합) ^(XOR:같으면0,다르면1) ~(역)
	unsigned char byte = 1;
	byte << 1; //1승증가, 계산만하고 대입은 안함
	byte <<= 3; //3승증가 1이 8이됨
	byte >>= 1; //1승감소 8이 4가됨

	unsigned int iStatus = 0; 
	
	//상태 추가
	iStatus |= HUNGRY; 	//전처리 참고, 배고픔을 추가
	iStatus |= THIRSTY; //이미 배고픔에서 목마름을 비트단위에서 합쳐서 대입


	//상태 확인
	if (iStatus & THIRSTY) //둘다 1일때만 참
	{

	}

	//상태 제거
	iStatus &= ~THIRSTY; //무조건0 나옴, 특정 자리 비트 제거

	data = Add1(10, 20);


	//반복문 : for(), while(), 프로그램 계속실행/종료를 컨트롤


	int iData = Add1(100, 200);

	//for (/*반복자 초기화*/; /*반복자 조건체크*/; /*반복자 변경(탈출여지)*/)
	for (int i = 0; i < 4; ++i)
	{
		if (i % 2 == 1)
		{
			continue; //뒤 기능없이 처음으로 다시, break는 중단후 다음단계로
		}
		printf("Output Test\n");

	}

	int j = 0;
	while (j < 2)
	{
		printf("Output Test\n");
		++j;
	}


	//콘솔 : 입출력창 이라는 뜻
	printf("abcdef %d \n", 10);		//정수는 %d
	printf("abcdef %f \n", 3.14f);	//실수는 %f, 데이터타입은 float만 가능

	for (int i = 0; i < 10; ++i)
	{
		printf("Output i : %d \n", i);
	}

	//scanf 변수 입력받기
	int iInput = 0;
	scanf_s("%d", &iInput);

	//자료구조, 데이터관리
	//스택 : 선입후출, 후입선출 >> 함수가 사용하는 메모리공간, 스택 메모리
	//큐Queue : 선입선출, 후입후출

	//Factorial : ex 8! = 8*7*6*5*4*3*2*1
	//매번 짜기 귀찮으니 전역에 함수 설정 해놓기
	int oValue = Factorial(4);
	oValue = Factorial(8); //반복문구현
	oValue = Factorial_Re(8); //재귀함수구현
	
	oValue = Fibonacci(10);
	oValue = Fibonacci_Re(10);

	//배열 : 메모리가 연속적인 구조!
	int iArray[10] = { }; //10개짜리 배열을 생성,{ } 내용은 전부 0 으로 
	iArray[4] = 10; //5번째 인덱스에 접근, 10으로 저장, 배열 초과해서 접근하면 다른 데이터에 이상한 값들어감

	//구조체
	MYST t;
	t.a = 10;
	t.f = 10.2312f;

	int iSize = sizeof(MYST);

	return 0;


}
