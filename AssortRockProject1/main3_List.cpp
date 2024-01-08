
#include <iostream>
#include <time.h>


#include "LinkedList.h"
#include "Arr.h"


void BubbleSort(int* _pData, int _iCount)
{
	//데이터가 1개이하면 정렬x, 없어도 오류는 아니라 굳이 쓸필요없는 코드
	if (_iCount <= 1)
	{
		return;
	}

	//오름차순 정렬

	while (true)
	{
		bool bFinish = true;

		int iLoop = _iCount - 1;
		for (int i = 0; i < iLoop; ++i)
		{
			if (_pData[i] > _pData[i + 1])
			{
				int iTemp = _pData[i];
				_pData[i] = _pData[i + 1];
				_pData[i + 1] = iTemp;

				bFinish = false; //for문안에서 돌때는 false유지
				
			}
		}

		if (bFinish) //빠져나오면 참이 되면서 종료
		{
			break;
		}

	}


}

void Test2(int a)
{
	printf("%d\n", a);
}

void Test()
{
	
}


//동적할당 == 힙영역, 메모리할당을 실시간으로 변경, 그래서 변수가 미리 설정이 안되고 포인터변수로 제어

int main()
{
	//int* pInt = (int*)malloc(100); //메모리할당함수, 단위는 바이트, 함수실행하면 공간과 주소가 생성됨, void타입으로 자료형 강제해야함
	Test2(10);


	int iInput = 0;
	scanf_s("%d", &iInput);

	int* pInt = nullptr;

	if (100 == iInput)
	{
		pInt = (int*)malloc(100);
	}

	if (nullptr != pInt)
	{
		free(pInt);//가리킨 주소의 힙메모리를 해지시키는 함수, 해제안시키면 메모리 샘
	}


	//가변배열 -> 지역변수로는 가변성을 부여하기 어려움 왜냐하면, 메모리크기할당때문
	int arr[10] = {};
	int a = 100;

	//함수포인터 선언방법, 함수의 주소를 받는 포인터변수
	void(*pFunc)(void) = nullptr; //인자를 아무것도 갖지 않는(void), pFunc함수의 주소(*)를 반환타입 void로 가져옴
	pFunc = Test; // 주소에 값넣기, Test함수 대신, 포인터의 특징을 활용해서 각종 함수를 호출할 수 있는 기능, 특정 모션을 통제를 pFunc로 패키징해놓고 소캣식으로 업데이트나 상황 추가

	pFunc(); //호출, 실행, 바뀐 주소의 내용을 실행하고 싶을때, ex무기, 자주쓰는 마법등의 사용 상황 등

	int iArr1[10] = { 87,644,21,55,787,645,55,1231, };
	BubbleSort(iArr1, 10);

	tArr s1 = {};
	tArr s2 = {};
	tArr s3 = {};

	InitArr(&s1);
	InitArr(&s2);
	InitArr(&s3);

	//난수(랜덤)
	srand(time(nullptr));//시드난수표 + 현재시간값을 넣어서 무작위성 강화
	
	
	for (int i = 0; i < 10; ++i)
	{
		int iRand = rand() % 100 + 1;//기본난수표, 그냥 함수연산만 해도되지만 디버깅할때 값확인해보려고 지역변수 부여
		PushBack(&s1, iRand);

	}

	printf("정렬 전\n");
	for (int i = 0; i < s1.iCount; ++i)
	{
		printf("%d\n", s1.pInt[i]);
	}

	Sort(&s1,&BubbleSort);

	printf("정렬 후\n");
	for (int i = 0; i < s1.iCount; ++i)
	{
		printf("%d\n", s1.pInt[i]);
	}

	Reallocate(&s1); 
	//원래의도는 PushBack함수용 공간 재할당함수인데 헤더에 있으니까 메인에서도 호출가능하고, 당장에 문제는x
	//그러나 불필요하게 공간늘어나면 메모리 새는 문제도 있고 잠재적 버그를 내포하기때문에 헤더에서 arr1.cpp로 선언을 이동시키면 됨

	ReleaseArr(&s1);
	ReleaseArr(&s2);
	ReleaseArr(&s3);




	//연결형 리스트 (자료구조, 가변배열도 자료구조의 일종)
	tLinkedList list = {}; //[3]구조체1을 생성한 직후
	InitList(&list); //[3]구조체1을 생성한 직후, 말그대로 초기화를 해줌

	PushBackL(&list, 100);
	PushBackL(&list, 200);
	PushBackL(&list, 300);

	ReleaseList(&list);

	InitList(&list);
	PushFrontL(&list, 100);
	PushFrontL(&list, 200);
	PushFrontL(&list, 300);
	
	tNode* pNode = list.pHeadNode;
	for (int i = 0; i < list.iCount; ++i)
	{
		printf("%d\n", pNode->iData);
		pNode = pNode->pNextNode;
	}

	ReleaseList(&list);




	return 0;

}