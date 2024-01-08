
#include <iostream>
#include <time.h>


#include "LinkedList.h"
#include "Arr.h"


void BubbleSort(int* _pData, int _iCount)
{
	//�����Ͱ� 1�����ϸ� ����x, ��� ������ �ƴ϶� ���� ���ʿ���� �ڵ�
	if (_iCount <= 1)
	{
		return;
	}

	//�������� ����

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

				bFinish = false; //for���ȿ��� ������ false����
				
			}
		}

		if (bFinish) //���������� ���� �Ǹ鼭 ����
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


//�����Ҵ� == ������, �޸��Ҵ��� �ǽð����� ����, �׷��� ������ �̸� ������ �ȵǰ� �����ͺ����� ����

int main()
{
	//int* pInt = (int*)malloc(100); //�޸��Ҵ��Լ�, ������ ����Ʈ, �Լ������ϸ� ������ �ּҰ� ������, voidŸ������ �ڷ��� �����ؾ���
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
		free(pInt);//����Ų �ּ��� ���޸𸮸� ������Ű�� �Լ�, �����Ƚ�Ű�� �޸� ��
	}


	//�����迭 -> ���������δ� �������� �ο��ϱ� ����� �ֳ��ϸ�, �޸�ũ���Ҵ綧��
	int arr[10] = {};
	int a = 100;

	//�Լ������� ������, �Լ��� �ּҸ� �޴� �����ͺ���
	void(*pFunc)(void) = nullptr; //���ڸ� �ƹ��͵� ���� �ʴ�(void), pFunc�Լ��� �ּ�(*)�� ��ȯŸ�� void�� ������
	pFunc = Test; // �ּҿ� ���ֱ�, Test�Լ� ���, �������� Ư¡�� Ȱ���ؼ� ���� �Լ��� ȣ���� �� �ִ� ���, Ư�� ����� ������ pFunc�� ��Ű¡�س��� ��Ĺ������ ������Ʈ�� ��Ȳ �߰�

	pFunc(); //ȣ��, ����, �ٲ� �ּ��� ������ �����ϰ� ������, ex����, ���־��� �������� ��� ��Ȳ ��

	int iArr1[10] = { 87,644,21,55,787,645,55,1231, };
	BubbleSort(iArr1, 10);

	tArr s1 = {};
	tArr s2 = {};
	tArr s3 = {};

	InitArr(&s1);
	InitArr(&s2);
	InitArr(&s3);

	//����(����)
	srand(time(nullptr));//�õ峭��ǥ + ����ð����� �־ �������� ��ȭ
	
	
	for (int i = 0; i < 10; ++i)
	{
		int iRand = rand() % 100 + 1;//�⺻����ǥ, �׳� �Լ����길 �ص������� ������Ҷ� ��Ȯ���غ����� �������� �ο�
		PushBack(&s1, iRand);

	}

	printf("���� ��\n");
	for (int i = 0; i < s1.iCount; ++i)
	{
		printf("%d\n", s1.pInt[i]);
	}

	Sort(&s1,&BubbleSort);

	printf("���� ��\n");
	for (int i = 0; i < s1.iCount; ++i)
	{
		printf("%d\n", s1.pInt[i]);
	}

	Reallocate(&s1); 
	//�����ǵ��� PushBack�Լ��� ���� ���Ҵ��Լ��ε� ����� �����ϱ� ���ο����� ȣ�Ⱑ���ϰ�, ���忡 ������x
	//�׷��� ���ʿ��ϰ� �����þ�� �޸� ���� ������ �ְ� ������ ���׸� �����ϱ⶧���� ������� arr1.cpp�� ������ �̵���Ű�� ��

	ReleaseArr(&s1);
	ReleaseArr(&s2);
	ReleaseArr(&s3);




	//������ ����Ʈ (�ڷᱸ��, �����迭�� �ڷᱸ���� ����)
	tLinkedList list = {}; //[3]����ü1�� ������ ����
	InitList(&list); //[3]����ü1�� ������ ����, ���״�� �ʱ�ȭ�� ����

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