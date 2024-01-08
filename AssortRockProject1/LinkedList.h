#pragma once

/*������ ����Ʈ�� �����ڡ�
* ����ü1 : iCount�� ������ �������� �� pHeadNode ù��° �������� �ּ�����
* ����ü2 : iData�� ���� ���������� �� ����ü2�� ��������� �����Ͽ� ���� ����� �ּҸ� ���� �� pNextNode�� ����
*/

typedef struct _tagNode //[2]����� ����ü : ���峻�� iDate & ���������� ����� �ּ�
{
	int					iData; //struct _tagNode�� �������ϰ�
	struct _tagNode*	pNextNode; //���� struct _tagNode�� �ּҸ� ���� // tNode* pNextNode; ����ϸ� ���� �ֳ�, tNode���� ���� ����ϸ� �ȵǼ�

}tNode;//typedef struct _tagNode �Ź����� �������� ���Ӹ� ��� ����
 

typedef struct _tagList //[1]������ ����Ʈ ����ü : �������� ù��° ��� �ּҸ� �����ϴ� ����ü(���� �ּҴ� �����ο��� ���������� Ž��)
{
	tNode*	pHeadNode; //�ּ�
	int		iCount;//������ ���� ����

}tLinkedList;//typedef struct _tagList �Ź����� �������� ���Ӹ� ��� ����

//{���� ���� ���� �պ�(����) ���(��) ��(���� ����Ʈ��)}���� ����


//������ ����Ʈ �ʱ�ȭ
void InitList(tLinkedList* _pList);

//������ ����Ʈ ������ �߰�
void PushBackL(tLinkedList* _pList, int _iData);
void PushFrontL(tLinkedList* _pList, int _iData);


//�� ������ �� ���޸� ����
void ReleaseList(tLinkedList* _pList);