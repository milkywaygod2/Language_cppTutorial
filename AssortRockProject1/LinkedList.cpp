#include "LinkedList.h"
#include <iostream>


void InitList(tLinkedList* _pList) //[3]����ü1�� ������ ����, ���״�� �ʱ�ȭ�� ����
{
	_pList->pHeadNode = nullptr;
	_pList->iCount = 0;
}

void PushBackL(tLinkedList* _pList, int _iData) //[4]����Ʈ�� �Է� �����͸� �־��ּ��� (Ǫ���� : �����͸� ���̾� �ְڴ�), �ڡں� �Լ���ü�� �ݺ����� �ƴԿ� ����, ���� ��� ���������� �����
{
	tNode* pNode = (tNode*)malloc(sizeof(tNode));//[4-1]tNode(����ü2)Ÿ���� ��带 �� �����ϰ� �޸𸮿� �Ҵ��ϰ�, �� �ּҸ� pNode�� ���� 
	//malloc �Լ��� �Ҵ�� �޸� ������ ���� �������� �޸� �ּ��̳�, ����ڰ� ���� �Ҵ��ϱ������� �������� Ʈ���������� ������ ���������� ��ϵ������� ���� ��ϵ� Ư���� �ּҰ��� ����(�����Ⱚ)

	pNode->iData = _iData; //[4-2]tNode, �� ����ü2�� ���ڸ� 2�� ����, �Էµ����͸� �Է� .h ����
	pNode->pNextNode = nullptr;//[4-2]tNode����ü ��������(pNode����) ���� �ּ��� ����� ����� ����, �ش��ּҿ� ���� �Ҵ��������ν� �������� Ʈ���������� ������ ���������� ���, �ּ�Ȯ��(�Ҵ������ �ּҾ����Ⱚ)


	//[4-3]��ũ�� ����Ʈ�� ����ִٸ�, ��� ��带 ���ο� ���� �����մϴ�. ��� ���� ��ũ�� ����Ʈ�� ù ��° ��带 ����Ű�� �����
	if (0 == _pList->iCount) 
	{
		_pList->pHeadNode = pNode; //[4-3]pHeadNode�ּҿ� "�̹� �Լ�"�� pNode �ּҸ� ����(��ġ��Ŵ)
		
	}

	//[4-5] ���� �ּ�(_pList->pHeadNode)�� pCurFinalNode�� �ѹ� �޾Ƽ�(�����ȹٲ��) ���� ����� ���� ��� �ּҰ� null�� �ƴ� ������ �ݺ��ϴ� while ���� �ۼ�. null�̶�� ������ ��忡 �����ߴٴ� �ǹ�
	else
	{
		tNode* pCurFinalNode = _pList->pHeadNode; 
		while (pCurFinalNode->pNextNode) //[4-5]Null(False)������ break;
		{
			pCurFinalNode = pCurFinalNode->pNextNode;
		}
		pCurFinalNode->pNextNode = pNode; //[4-5]��������忡 �����ϸ�, �� ��� ���� ��ġ��

	}
	
	++_pList->iCount;//[4-4] ���� if-else�ݺ������� iCount�÷���


}

//����������Ʈ PushFront�� ����
void PushFrontL(tLinkedList* _pList, int _iData)
{
	//���� ������Ų ����� ������ ������ ���� ����(�ؽ�Ʈ==������ ���� ����)
	tNode* pFNode = (tNode*)malloc(sizeof(tNode));
	pFNode->iData = _iData;
	pFNode->pNextNode = _pList->pHeadNode;
		
	//����Ʈ�� ����� �����͸� �Լ��� �Է°����� ����
	_pList->pHeadNode = pFNode;
		
	//������ī��Ʈ����
	++_pList->iCount;
}


//����Լ��� �޸����� > 4000���� �Ѿ�� ���� ��ȿ��
void Release(tNode* _pNode)
{
	if (nullptr == _pNode)
		return;
	Release(_pNode->pNextNode);
	free(_pNode);
}

//�ݺ������ �޸�����
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