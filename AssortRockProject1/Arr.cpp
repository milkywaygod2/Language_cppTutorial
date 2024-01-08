
#include <iostream>

#include "Arr.h"


//���� �ʱ��Ҵ� �� �ʱ�ȭ�Լ�
void InitArr(tArr* _pArr)
{
	_pArr->pInt = (int*)malloc(sizeof(int) * 2);
	_pArr->iCount = 0; //������ �ִ� ���� ����
	_pArr->iMaxCount = 2; //malloc���� �Ҵ�� �ִ����
	 
}
//���� ���Ҵ��Լ�
void Reallocate(tArr* _pArr)
{
	//�޸𸮰��� 2��� �÷��ֱ�
	int* pNew =	(int*)malloc(_pArr->iMaxCount * sizeof(int) * 2);

	//���� �����͸� ���ο� �������� �̵�
	for (int i = 0; i < _pArr->iCount; ++i)
	{
		pNew[i] = _pArr->pInt[i];
	}

	//���� ������ �޸� ����
	free(_pArr->pInt);

	//���� Ȯ��� �迭�� pInt�� ������Ʈ
	_pArr->pInt = pNew;

	//MaxCount������ ����


}

//�������Ҵ� �Լ�
void PushBack(tArr* _pArr, int _iData)
{
	//������ ���� �����ִ°�?
	if(_pArr->iMaxCount <= _pArr->iCount);
	{
		//������ ���Ҵ�
		Reallocate(_pArr);
	}

	//�������߰�
	_pArr->pInt[_pArr->iCount++] = _iData; //���޸� �ּҰ������� pInt�� ���κп� �����϶�� �ֹ�
	

}

//���� ���� �� �ʱ�ȭ�Լ�
void ReleaseArr(tArr* _pArr)
{
	free(_pArr->pInt);
	_pArr->iCount = 0;
	_pArr->iMaxCount = 0;

}