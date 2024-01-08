#pragma once



typedef struct _tagArr //타입재정의 구조체 의_이름
{
	int* pInt; //주소
	int iCount;//관리변수
	int iMaxCount; //관리변수

}tArr;


//ctrl = . 같이누르면 해당함수 정의cpp파일생성

//배열 초기화함수
void InitArr(tArr* _pArr);

//데이터 추가함수
void PushBack(tArr* _pArr, int _iData);

//공간 추가 함수
void Reallocate(tArr* _pArr);

//배열 메모리 해제 함수
void ReleaseArr(tArr* _pArr);


//데이터 정렬 함수
void Sort(tArr* _pArr, void(*SortFunc)(int*, int));
