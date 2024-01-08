
#include <iostream>

#include "Arr.h"


//공간 초기할당 및 초기화함수
void InitArr(tArr* _pArr)
{
	_pArr->pInt = (int*)malloc(sizeof(int) * 2);
	_pArr->iCount = 0; //데이터 넣는 순서 관리
	_pArr->iMaxCount = 2; //malloc으로 할당된 최대공간
	 
}
//공간 재할당함수
void Reallocate(tArr* _pArr)
{
	//메모리공간 2배로 늘려주기
	int* pNew =	(int*)malloc(_pArr->iMaxCount * sizeof(int) * 2);

	//기존 데이터를 새로운 공간으로 이동
	for (int i = 0; i < _pArr->iCount; ++i)
	{
		pNew[i] = _pArr->pInt[i];
	}

	//기존 공간은 메모리 해제
	free(_pArr->pInt);

	//새로 확장된 배열로 pInt를 업데이트
	_pArr->pInt = pNew;

	//MaxCount변경점 적용


}

//데이터할당 함수
void PushBack(tArr* _pArr, int _iData)
{
	//힙영역 공간 여유있는가?
	if(_pArr->iMaxCount <= _pArr->iCount);
	{
		//없으면 재할당
		Reallocate(_pArr);
	}

	//데이터추가
	_pArr->pInt[_pArr->iCount++] = _iData; //힙메모리 주소관리자인 pInt의 끝부분에 저장하라는 주문
	

}

//공간 해제 및 초기화함수
void ReleaseArr(tArr* _pArr)
{
	free(_pArr->pInt);
	_pArr->iCount = 0;
	_pArr->iMaxCount = 0;

}