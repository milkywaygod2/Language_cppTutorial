#pragma once

/*연결형 리스트의 구조★★
* 구조체1 : iCount로 데이터 개수관리 및 pHeadNode 첫번째 데이터의 주소저장
* 구조체2 : iData로 실제 데이터저장 및 구조체2를 재귀적으로 선언하여 다음 노드의 주소를 생성 및 pNextNode에 저장
*/

typedef struct _tagNode //[2]저장용 구조체 : 저장내용 iDate & 다음저장할 노드의 주소
{
	int					iData; //struct _tagNode에 값저장하고
	struct _tagNode*	pNextNode; //다음 struct _tagNode의 주소를 지목 // tNode* pNextNode; 라고하면 오류 왜냐, tNode선언 전에 사용하면 안되서

}tNode;//typedef struct _tagNode 매번쓰기 귀찮으니 줄임말 용어 정의
 

typedef struct _tagList //[1]연결형 리스트 구조체 : 데이터의 첫번째 노드 주소를 저장하는 구조체(뒤의 주소는 구현부에서 순차적으로 탐색)
{
	tNode*	pHeadNode; //주소
	int		iCount;//데이터 개수 관리

}tLinkedList;//typedef struct _tagList 매번쓰기 귀찮으니 줄임말 용어 정의

//{버블 삽입 선택 합병(머지) 쾌속(퀵) 힙(완전 이진트리)}정렬 종류


//연결형 리스트 초기화
void InitList(tLinkedList* _pList);

//연결형 리스트 데이터 추가
void PushBackL(tLinkedList* _pList, int _iData);
void PushFrontL(tLinkedList* _pList, int _iData);


//각 데이터 및 힙메모리 해제
void ReleaseList(tLinkedList* _pList);