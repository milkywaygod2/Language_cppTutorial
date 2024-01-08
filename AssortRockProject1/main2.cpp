#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <assert.h>
#include <iostream>
#include "func.h"
#include "common.h"


//ctrl+shift+spacebar >> 함수선언문 확인기능

//변수의 종류 : 지역(스택) 전역(Data영역) 정적(static,Data영역) 외부(extern)
//메모리 영역의 종류 : 스택 데이터(프로그램시작시 생성 종료시까지 유지) 읽기전용(코드,ROM_read only memory) 힙
//함수 오버로딩, 동일이름의 구성요건이 다른 여러가지 함수를 만들고 코딩시 선택할 수 있는 기능
//함수 오버라이딩 > class쪽 개념

int g_i = 0; //Data영역, 전역변수

typedef struct _tagMyST //구조체 선언
{
	int a; //구조체 맴버
	int f;
}MYST;


unsigned int GetLenth(const wchar_t* _pStr) //문자개수체크용 함수
{
	int i = 0;

	while (true)
	{
		wchar_t c = *(_pStr + i); //== _pStr[i]
		if ('\0' == c) //논리식 짤때 상수(Rvalue)를 왼쪽으로 가는게 좋음 
		{
			break;
		}
		++i;
	}

	return i;
}
/* 위랑 같은 코딩입니다 간소하게
unsigned int GetLenth(const wchar_t* _pStr)
{
	int i = 0;
	
	while ('\0' != _pStr[i])
	{
			++i
	}
		return i;
}



*/



void StrCat(wchar_t* _pDest, unsigned int _iBufferSize, const wchar_t* _pSrc)
{
	int iDestLen = GetLenth(_pDest);
	int iSrcLen = GetLenth(_pSrc);
	if (_iBufferSize < iDestLen + iSrcLen + 1) //문자열공간까지 포함
	{
		assert(nullptr);

		//작업순서세우기
		//목표: 문자열 이어붙이기
		//1.Dest문자열의 끝을 확인
		iDestLen;

		//2.반복적으로 Src문자열을 Dest 끝 위치에 복사
		for (int i = 0; i < iSrcLen; ++i)
		{
			_pDest[iDestLen + i] = _pSrc[i]; //★
		}

		//3.Src 문자열의 끝을 만나면 반복 종료

	}

}

int StrCmp(const wchar_t* _left, const wchar_t* _right) //문자열비교함수(오름차순내림차순 정렬기능구현용) 오른쪽이 크면 -1 왼쪽이크면 1
{
	int leftLen = GetLenth(_left);
	int rightLen = GetLenth(_right);

	int iLoop = leftLen;
	int iReturn = 0;

	//1단계 : 둘중에 길이가 짧은 쪽을 기준으로 iLoop에 넣어 비교, 같다면 초기값 leftLen~
	if (leftLen < rightLen)
	{
		iLoop = leftLen;
		iReturn = -1; //for구문까지 갔는데 값이 같았을때, 좀 더 긴놈이 최종판정승!
	}
	else if (leftLen > rightLen)
	{
		iLoop = rightLen;
		iReturn = 1;
	}

	//2단계 : 둘의 길이가 같은 부분까지를 앞에서부터 비교해서, 같으면 패스 다르면 점수부여
	for (int i = 0; i < iLoop; ++i)
	{
		if (_left[i] < _right[i])
		{
			return -1;
		}
		else if (_left[i] > _right[i])
		{
			return 1;
		}
	}
	//3단계 : 오른쪽이큼(1) 왼쪽이큼(-1) 길이는 같음(0) 
	return iReturn;
}

void Test1(int* a)
{
	*a = 500;

}


int Test()
{
	static int i = 0; //Test함수안에서만 작동, Data영역 >> 해당함수의 호출과 종료와 별개로 유지되는 메모리
	++g_i;
	++i;

	return i;

}

void Output(const int* pI)
{
	int i = *pI; //값확인이나 접근만 할게요!
	//*pI = 100; 이렇게 포인터기능으로는 수정안됨 > 포인터로 값 수정할 의도는 없습니다!
	int* pInt = (int*)pI; //일반포인터로 치환해서 > 강제의도
	*pInt = 100; //const무시하고 수정, const_cast 라는 취소 기능도 있음
}

int main()
{
	//int i = Mul(10, 20);
	g_iStatic = 100;
	g_iExtern = 500;

	//F12 함수 추적기능
	Add(0, 0);

	Test();
	Test();
	Test();
	Test();
	Test();

	int iCall = Test();


	g_i = 0;
	printf("Test함수 호출 횟수 : %d\n", iCall);


	//포인터(주소를 저장하는 역할) 변수, ★자료형을 같이 부여해줘야함 == 자료형* 변수명
	//포인터를 쓰는 이유, 스택기반으로 함수 호출를 사용하게되면 무조건 공간을 두배로 쓰게 되서 비효율적, 포인터로 필요한 것만 확인 또는 수정
	int* pInt1 = nullptr; //실제데이터는 0, *붙여서 포인터 변수

	int i = 100;
	float f = 3.f;
	 
	int* pInt2 = &i; //주소값 받아오는 선언
	(*pInt2) = 100; //포인터형 변수, 주소의 단위는 8BYTE(8바이트==64비트) 정수타입, ★포인터 변수의 크기는 모두 같음(운영체제 32/64bit동일플랫폼내에서) +다만 ~자료형으로 해석을 하겠다만 다름
	//주소를 한번에 32비트 처리한다? 4바이트 공간 == 2^32 == 42억가지, 주소를 담을 수 있는 최소 단위는 1BYTE, 즉 42억BYTE를 한번에 호출 할 수 있다는 의미 == 420만KB == 4천MB == 4GB


	int* pInt3 = (int*)&f; //자료형 다르지만, 강제로 f주소 가져오기
	i = *pInt3; // 그주소를 i에 넣으셈, 실수형 데이터를 정수형으로 읽어보기 ㅋㅋ

	char* pChar = nullptr;
	short* pShort = nullptr;

	int iSize = sizeof(pInt1); //int 자료형은 4BYTE크기이다

	i = 0;
	pInt2 = &i;
	pInt2 += 1; //★주소의 연산이기때문에 자료형인 int크기 4BYTE를 증가시킴 sizeof(int)단위로 증가, 4 → 8

	//배열의 특징 1.메모리가 연속적 2.배열의 이름이 시작 주소를 의미
	int iArr[10] = {};
	*(iArr + 1) = 10; //[0,10,0,0,0,0,0,0,0,0] 두번째칸 주소에 10을 대입 축약형 iArr[1] = 7
	*(iArr + 0) = 7; //[7,10,0,0,0,0,0,0,0,0] 두번째칸 주소에 10을 대입, 축약형 iArr[0] = 7, 배열 인덱스 접근이 0부터 시작하는 이유 ==포인터주소접근

	//문제1
	short sArr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int* pI = (int*)sArr;
	int iData = *((short*)(pI + 2)); //short는 2BYTE 자료형, int는 4BYTE 자료형
	printf("1번 문제 정답 : %d\n", iData); //5


	//문제2
	char cArr[2] = { 1,1 }; //char 자료형은 1BYTE
	short* pS = (short*)cArr; //2BYTE로 읽음
	iData = *pS;
	printf("2번 문제 정답 : %d\n", iData); //{256+1}


	int a = 100;
	Test1(&a);

	printf("출력 : %d\n", a);

	//scanf_s("%d", &a); //a 주소에 있는 값을 키보드 입력 값으로 반환

	//콘스트 const 변수앞에 붙이는  / 상수 r-value, 변수 l-value
	volatile const int cint = 100; //상수화 (값이 바뀔 수 없는 상태) 문법상 상수 그러나 실체는 변수, 포인터로 주소접근해서 바꾸면 바뀜
	//volatile(레지스터사용금지) 안붙이면 const 값이 CPU내의 레지스터에 들어가서 아래 포인터 접근으로 변경에도 불구, 계산은 최초 const 값으로 수행됨
	printf("cint출력 : %d\n", cint);

	pInt3 = (int*)&cint;
	*pInt3 = 300;
	printf("cint출력 : %d\n", cint);

	const int j = 100;

	int b = 0;
	int* pInt = &b;

 	*pInt = 1;
	pInt = nullptr;

	//==============
	//★const 포인터 : 포인터가 가리키고 있는 원본을 상수화, 변수를 상수화한다
	//==============
	const int* pConstInt = &b; //== int const* pConstInt 거의 안쓰는 표현
	*pConstInt; //접근 가능

	int c = 0;
	pConstInt = &c; //포인터 변수자체도 변경가능
	//*pConstInt = 100; //수정은 불가능, 즉 &b 또는 &c 원본을 수정할 수는 없음
	
	c = 10; //????? 가능하다, 왜냐하면 const int* 는 포인터의 기능을 제한한 것으로 변수 자체에 직접 명령하는 것과 별개
	int* p = &a;
	*p = 100; //기능을 제한하지 않은 다른 포인터로는 변경가능

	//==============
	//★포인터 const : 포인터 그 자체를 상수화
	//==============
	int* const pIntConst = &b;
	*pIntConst = 400; //가리키고 있는 원본 수정가능
	*pIntConst;
	//pIntConst = &b; //가리키는 방향 등, 포인터 자체는 수정불가


	//포인터와 원본 모두 상수화
	const int* const pConstIntConst = nullptr;


	a = 100;
	Output(&a); //ctrl shift space로 함수의 의도 확인


	//void 반환값이 필요없는 함수
	
	//void 포인터
	void* pVoid = nullptr; //자료형 제한없는 포인터 + 자료형 미정으로 역참조/주소연산 안됨
	float* pFloat = nullptr; //일반적 > 포인터에 자료형을 정해줌

	{
	int a = 0;
	float f = 0.f;
	double d = 0.;
	long long ll = 0;
	
	pVoid = &a;
	pVoid = &f;
	pVoid = &d;
	pVoid = &ll;

	//*pVoid; 역참조는 불가능함, 자료형을 모르기때문
	//pVoid +1; 주소연산도 안됨, 자료형 특정x
	}


	//데이터 영역중 읽기전용 ROM, 아스키 코드표
	{
		char c = 'a'; //문자, 1바이트 기반 가변 문자 자료형(2바이트는 자동으로 2바이트처리)
		wchar_t wc = L'a'; //소문자 a, 2바이트 문자 자료형(L)
		
		bool b = 1; //true
		c = '1'; //문자로써의 1을 넣으라

		wchar_t wc1 = 97; //소문자 a, 2바이트 문자 자료형
		short s = 97; //숫자 97

		char szChar[10] = "abcdef";
		wchar_t szWChar[7] = L"abcd"; //문자열을 나타내는 마지막 1BYTE여유있어야, [4]으로 하면 공간부족으로 에러
		short arrShort[7] = { 97,98,99,100, }; //"abcd"
		
		szWChar[1] = 'z'; //주소연산 Lvalue대입
		const wchar_t* pChar = L"abcd"; //포인터로 Rvalue바꾸면 알고리즘 붕괴될 위험(ROM을 수정하려고 하기때문)
		// pChar[1] = 'z';	/==/	*(pChar +1) = 'z'; Rvalue대입, 연산중인 혹은 연산해야할 데이터를 중간에 끼여들어서 바꿈(치명적 문제임)
		
		unsigned char szTest[10] = "abc한글"; //char 1바이트 자료형, unsigned >> 167넘어가면 음수로 보여서 양수로 보려고 추가ㅋㅋ
		wchar_t szTestW[10] = L"abc한글"; //wchar_t 2바이트 자료형
	}

	{
		wchar_t szName[10] = L"Raimond";
		int iLen = wcslen(szName);//문자열의 길이를 알려주는 함수
		iLen = GetLenth(szName); //커스텀 함수

		//문자열 이어붙이기

		{
			wchar_t szString[100] = L"abc";
			wcscat_s(szString, 100, L"def");
			wcscat_s(szString, 100, L"ghi");

		}

		{
			wchar_t szString[100] = L"abc";
			StrCat(szString, 10, L"def");

			//wcscmp 두문자열을 비교해서 완전히 같으면 참 아니면 거짓
			int iRet = wcscmp(L"ca",L"ca");
			iRet = StrCmp(L"abcdef", L"abc");

		}
	}

	{
		//구조체와 포인터
		MYST s = {};

		s.a;
		int a;

		MYST s2;
		MYST s3;

		MYST* pST = &s;
		pST + 1;

		(*pST).a = 100;
		(*pST).f = 3.14f;

		pST->a = 100;
		pST->f = 3.14f;
	}

	return 0;

}

