#pragma once



typedef struct _tagArr //Ÿ�������� ����ü ��_�̸�
{
	int* pInt; //�ּ�
	int iCount;//��������
	int iMaxCount; //��������

}tArr;


//ctrl = . ���̴����� �ش��Լ� ����cpp���ϻ���

//�迭 �ʱ�ȭ�Լ�
void InitArr(tArr* _pArr);

//������ �߰��Լ�
void PushBack(tArr* _pArr, int _iData);

//���� �߰� �Լ�
void Reallocate(tArr* _pArr);

//�迭 �޸� ���� �Լ�
void ReleaseArr(tArr* _pArr);


//������ ���� �Լ�
void Sort(tArr* _pArr, void(*SortFunc)(int*, int));
