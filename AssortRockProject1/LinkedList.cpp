#include "LinkedList.h"
#include <iostream>


void InitList(tLinkedList* _pList) //[3]구조체1을 생성한 직후, 말그대로 초기화를 해줌
{
	_pList->pHeadNode = nullptr;
	_pList->iCount = 0;
}

void PushBackL(tLinkedList* _pList, int _iData) //[4]리스트에 입력 데이터를 넣어주세요 (푸쉬백 : 데이터를 뒤이어 넣겠다), ★★본 함수자체는 반복문이 아님에 주의, 따라서 비록 독립적으로 수행됨
{
	tNode* pNode = (tNode*)malloc(sizeof(tNode));//[4-1]tNode(구조체2)타입의 노드를 를 실행하고 메모리에 할당하고, 그 주소를 pNode에 저장 
	//malloc 함수로 할당된 메모리 영역은 실제 물리적인 메모리 주소이나, 사용자가 값을 할당하기전에는 물리적인 트랜지스터의 공간에 전기적으로 기록되지않음 따라서 기록된 특정한 주소값도 없음(쓰레기값)

	pNode->iData = _iData; //[4-2]tNode, 즉 구조체2는 인자를 2개 가짐, 입력데이터를 입력 .h 참조
	pNode->pNextNode = nullptr;//[4-2]tNode구조체 실행으로(pNode선언) 다음 주소의 존재는 선언된 후임, 해당주소에 값을 할당해줌으로써 물리적인 트랜지스터의 공간에 전기적으로 기록, 주소확정(할당없으면 주소쓰레기값)


	//[4-3]링크드 리스트가 비어있다면, 헤드 노드를 새로운 노드로 설정합니다. 헤드 노드는 링크드 리스트의 첫 번째 노드를 가리키는 멤버임
	if (0 == _pList->iCount) 
	{
		_pList->pHeadNode = pNode; //[4-3]pHeadNode주소에 "이번 함수"의 pNode 주소를 넣음(매치시킴)
		
	}

	//[4-5] 최초 주소(_pList->pHeadNode)를 pCurFinalNode로 한번 받아서(헤드노드안바뀌게) 받은 노드의 다음 노드 주소가 null이 아닐 때까지 반복하는 while 문을 작성. null이라면 마지막 노드에 도달했다는 의미
	else
	{
		tNode* pCurFinalNode = _pList->pHeadNode; 
		while (pCurFinalNode->pNextNode) //[4-5]Null(False)나오면 break;
		{
			pCurFinalNode = pCurFinalNode->pNextNode;
		}
		pCurFinalNode->pNextNode = pNode; //[4-5]마지막노드에 도달하면, 그 노드 다음 위치에

	}
	
	++_pList->iCount;//[4-4] 이후 if-else반복때마다 iCount올려줌


}

//연결형리스트 PushFront로 구현
void PushFrontL(tLinkedList* _pList, int _iData)
{
	//새로 생성시킨 노드의 다음을 기존의 헤드로 지정(넥스트==시작점 으로 설정)
	tNode* pFNode = (tNode*)malloc(sizeof(tNode));
	pFNode->iData = _iData;
	pFNode->pNextNode = _pList->pHeadNode;
		
	//리스트의 헤드노드 포인터를 함수의 입력값으로 갱신
	_pList->pHeadNode = pFNode;
		
	//데이터카운트증가
	++_pList->iCount;
}


//재귀함수로 메모리해제 > 4000스택 넘어가면 터짐 비효율
void Release(tNode* _pNode)
{
	if (nullptr == _pNode)
		return;
	Release(_pNode->pNextNode);
	free(_pNode);
}

//반복문방식 메모리해제
void ReleaseList(tLinkedList* _pList)
{
	//Release(_pList->pHeadNode);
	tNode* pDeletNode = _pList->pHeadNode;

	while (pDeletNode)
	{
		tNode* pNext = pDeletNode->pNextNode;
		free(pDeletNode);
		pDeletNode = pNext;
	}
}