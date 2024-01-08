#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <assert.h>
#include <iostream>
#include "func.h"
#include "common.h"


//ctrl+shift+spacebar >> �Լ����� Ȯ�α��

//������ ���� : ����(����) ����(Data����) ����(static,Data����) �ܺ�(extern)
//�޸� ������ ���� : ���� ������(���α׷����۽� ���� ����ñ��� ����) �б�����(�ڵ�,ROM_read only memory) ��
//�Լ� �����ε�, �����̸��� ��������� �ٸ� �������� �Լ��� ����� �ڵ��� ������ �� �ִ� ���
//�Լ� �������̵� > class�� ����

int g_i = 0; //Data����, ��������

typedef struct _tagMyST //����ü ����
{
	int a; //����ü �ɹ�
	int f;
}MYST;


unsigned int GetLenth(const wchar_t* _pStr) //���ڰ���üũ�� �Լ�
{
	int i = 0;

	while (true)
	{
		wchar_t c = *(_pStr + i); //== _pStr[i]
		if ('\0' == c) //���� ©�� ���(Rvalue)�� �������� ���°� ���� 
		{
			break;
		}
		++i;
	}

	return i;
}
/* ���� ���� �ڵ��Դϴ� �����ϰ�
unsigned int GetLenth(const wchar_t* _pStr)
{
	int i = 0;
	
	while ('\0' != _pStr[i])
	{
			++i
	}
		return i;
}



*/



void StrCat(wchar_t* _pDest, unsigned int _iBufferSize, const wchar_t* _pSrc)
{
	int iDestLen = GetLenth(_pDest);
	int iSrcLen = GetLenth(_pSrc);
	if (_iBufferSize < iDestLen + iSrcLen + 1) //���ڿ��������� ����
	{
		assert(nullptr);

		//�۾����������
		//��ǥ: ���ڿ� �̾���̱�
		//1.Dest���ڿ��� ���� Ȯ��
		iDestLen;

		//2.�ݺ������� Src���ڿ��� Dest �� ��ġ�� ����
		for (int i = 0; i < iSrcLen; ++i)
		{
			_pDest[iDestLen + i] = _pSrc[i]; //��
		}

		//3.Src ���ڿ��� ���� ������ �ݺ� ����

	}

}

int StrCmp(const wchar_t* _left, const wchar_t* _right) //���ڿ����Լ�(���������������� ���ı�ɱ�����) �������� ũ�� -1 ������ũ�� 1
{
	int leftLen = GetLenth(_left);
	int rightLen = GetLenth(_right);

	int iLoop = leftLen;
	int iReturn = 0;

	//1�ܰ� : ���߿� ���̰� ª�� ���� �������� iLoop�� �־� ��, ���ٸ� �ʱⰪ leftLen~
	if (leftLen < rightLen)
	{
		iLoop = leftLen;
		iReturn = -1; //for�������� ���µ� ���� ��������, �� �� ����� ����������!
	}
	else if (leftLen > rightLen)
	{
		iLoop = rightLen;
		iReturn = 1;
	}

	//2�ܰ� : ���� ���̰� ���� �κб����� �տ������� ���ؼ�, ������ �н� �ٸ��� �����ο�
	for (int i = 0; i < iLoop; ++i)
	{
		if (_left[i] < _right[i])
		{
			return -1;
		}
		else if (_left[i] > _right[i])
		{
			return 1;
		}
	}
	//3�ܰ� : ��������ŭ(1) ������ŭ(-1) ���̴� ����(0) 
	return iReturn;
}

void Test1(int* a)
{
	*a = 500;

}


int Test()
{
	static int i = 0; //Test�Լ��ȿ����� �۵�, Data���� >> �ش��Լ��� ȣ��� ����� ������ �����Ǵ� �޸�
	++g_i;
	++i;

	return i;

}

void Output(const int* pI)
{
	int i = *pI; //��Ȯ���̳� ���ٸ� �ҰԿ�!
	//*pI = 100; �̷��� �����ͱ�����δ� �����ȵ� > �����ͷ� �� ������ �ǵ��� �����ϴ�!
	int* pInt = (int*)pI; //�Ϲ������ͷ� ġȯ�ؼ� > �����ǵ�
	*pInt = 100; //const�����ϰ� ����, const_cast ��� ��� ��ɵ� ����
}

int main()
{
	//int i = Mul(10, 20);
	g_iStatic = 100;
	g_iExtern = 500;

	//F12 �Լ� �������
	Add(0, 0);

	Test();
	Test();
	Test();
	Test();
	Test();

	int iCall = Test();


	g_i = 0;
	printf("Test�Լ� ȣ�� Ƚ�� : %d\n", iCall);


	//������(�ּҸ� �����ϴ� ����) ����, ���ڷ����� ���� �ο�������� == �ڷ���* ������
	//�����͸� ���� ����, ���ñ������ �Լ� ȣ�⸦ ����ϰԵǸ� ������ ������ �ι�� ���� �Ǽ� ��ȿ����, �����ͷ� �ʿ��� �͸� Ȯ�� �Ǵ� ����
	int* pInt1 = nullptr; //���������ʹ� 0, *�ٿ��� ������ ����

	int i = 100;
	float f = 3.f;
	 
	int* pInt2 = &i; //�ּҰ� �޾ƿ��� ����
	(*pInt2) = 100; //�������� ����, �ּ��� ������ 8BYTE(8����Ʈ==64��Ʈ) ����Ÿ��, �������� ������ ũ��� ��� ����(�ü�� 32/64bit�����÷���������) +�ٸ� ~�ڷ������� �ؼ��� �ϰڴٸ� �ٸ�
	//�ּҸ� �ѹ��� 32��Ʈ ó���Ѵ�? 4����Ʈ ���� == 2^32 == 42�ﰡ��, �ּҸ� ���� �� �ִ� �ּ� ������ 1BYTE, �� 42��BYTE�� �ѹ��� ȣ�� �� �� �ִٴ� �ǹ� == 420��KB == 4õMB == 4GB


	int* pInt3 = (int*)&f; //�ڷ��� �ٸ�����, ������ f�ּ� ��������
	i = *pInt3; // ���ּҸ� i�� ������, �Ǽ��� �����͸� ���������� �о�� ����

	char* pChar = nullptr;
	short* pShort = nullptr;

	int iSize = sizeof(pInt1); //int �ڷ����� 4BYTEũ���̴�

	i = 0;
	pInt2 = &i;
	pInt2 += 1; //���ּ��� �����̱⶧���� �ڷ����� intũ�� 4BYTE�� ������Ŵ sizeof(int)������ ����, 4 �� 8

	//�迭�� Ư¡ 1.�޸𸮰� ������ 2.�迭�� �̸��� ���� �ּҸ� �ǹ�
	int iArr[10] = {};
	*(iArr + 1) = 10; //[0,10,0,0,0,0,0,0,0,0] �ι�°ĭ �ּҿ� 10�� ���� ����� iArr[1] = 7
	*(iArr + 0) = 7; //[7,10,0,0,0,0,0,0,0,0] �ι�°ĭ �ּҿ� 10�� ����, ����� iArr[0] = 7, �迭 �ε��� ������ 0���� �����ϴ� ���� ==�������ּ�����

	//����1
	short sArr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int* pI = (int*)sArr;
	int iData = *((short*)(pI + 2)); //short�� 2BYTE �ڷ���, int�� 4BYTE �ڷ���
	printf("1�� ���� ���� : %d\n", iData); //5


	//����2
	char cArr[2] = { 1,1 }; //char �ڷ����� 1BYTE
	short* pS = (short*)cArr; //2BYTE�� ����
	iData = *pS;
	printf("2�� ���� ���� : %d\n", iData); //{256+1}


	int a = 100;
	Test1(&a);

	printf("��� : %d\n", a);

	//scanf_s("%d", &a); //a �ּҿ� �ִ� ���� Ű���� �Է� ������ ��ȯ

	//�ܽ�Ʈ const �����տ� ���̴�  / ��� r-value, ���� l-value
	volatile const int cint = 100; //���ȭ (���� �ٲ� �� ���� ����) ������ ��� �׷��� ��ü�� ����, �����ͷ� �ּ������ؼ� �ٲٸ� �ٲ�
	//volatile(�������ͻ�����) �Ⱥ��̸� const ���� CPU���� �������Ϳ� ���� �Ʒ� ������ �������� ���濡�� �ұ�, ����� ���� const ������ �����
	printf("cint��� : %d\n", cint);

	pInt3 = (int*)&cint;
	*pInt3 = 300;
	printf("cint��� : %d\n", cint);

	const int j = 100;

	int b = 0;
	int* pInt = &b;

 	*pInt = 1;
	pInt = nullptr;

	//==============
	//��const ������ : �����Ͱ� ����Ű�� �ִ� ������ ���ȭ, ������ ���ȭ�Ѵ�
	//==============
	const int* pConstInt = &b; //== int const* pConstInt ���� �Ⱦ��� ǥ��
	*pConstInt; //���� ����

	int c = 0;
	pConstInt = &c; //������ ������ü�� ���氡��
	//*pConstInt = 100; //������ �Ұ���, �� &b �Ǵ� &c ������ ������ ���� ����
	
	c = 10; //????? �����ϴ�, �ֳ��ϸ� const int* �� �������� ����� ������ ������ ���� ��ü�� ���� ����ϴ� �Ͱ� ����
	int* p = &a;
	*p = 100; //����� �������� ���� �ٸ� �����ͷδ� ���氡��

	//==============
	//�������� const : ������ �� ��ü�� ���ȭ
	//==============
	int* const pIntConst = &b;
	*pIntConst = 400; //����Ű�� �ִ� ���� ��������
	*pIntConst;
	//pIntConst = &b; //����Ű�� ���� ��, ������ ��ü�� �����Ұ�


	//�����Ϳ� ���� ��� ���ȭ
	const int* const pConstIntConst = nullptr;


	a = 100;
	Output(&a); //ctrl shift space�� �Լ��� �ǵ� Ȯ��


	//void ��ȯ���� �ʿ���� �Լ�
	
	//void ������
	void* pVoid = nullptr; //�ڷ��� ���Ѿ��� ������ + �ڷ��� �������� ������/�ּҿ��� �ȵ�
	float* pFloat = nullptr; //�Ϲ��� > �����Ϳ� �ڷ����� ������

	{
	int a = 0;
	float f = 0.f;
	double d = 0.;
	long long ll = 0;
	
	pVoid = &a;
	pVoid = &f;
	pVoid = &d;
	pVoid = &ll;

	//*pVoid; �������� �Ұ�����, �ڷ����� �𸣱⶧��
	//pVoid +1; �ּҿ��굵 �ȵ�, �ڷ��� Ư��x
	}


	//������ ������ �б����� ROM, �ƽ�Ű �ڵ�ǥ
	{
		char c = 'a'; //����, 1����Ʈ ��� ���� ���� �ڷ���(2����Ʈ�� �ڵ����� 2����Ʈó��)
		wchar_t wc = L'a'; //�ҹ��� a, 2����Ʈ ���� �ڷ���(L)
		
		bool b = 1; //true
		c = '1'; //���ڷν��� 1�� ������

		wchar_t wc1 = 97; //�ҹ��� a, 2����Ʈ ���� �ڷ���
		short s = 97; //���� 97

		char szChar[10] = "abcdef";
		wchar_t szWChar[7] = L"abcd"; //���ڿ��� ��Ÿ���� ������ 1BYTE�����־��, [4]���� �ϸ� ������������ ����
		short arrShort[7] = { 97,98,99,100, }; //"abcd"
		
		szWChar[1] = 'z'; //�ּҿ��� Lvalue����
		const wchar_t* pChar = L"abcd"; //�����ͷ� Rvalue�ٲٸ� �˰��� �ر��� ����(ROM�� �����Ϸ��� �ϱ⶧��)
		// pChar[1] = 'z';	/==/	*(pChar +1) = 'z'; Rvalue����, �������� Ȥ�� �����ؾ��� �����͸� �߰��� ������ �ٲ�(ġ���� ������)
		
		unsigned char szTest[10] = "abc�ѱ�"; //char 1����Ʈ �ڷ���, unsigned >> 167�Ѿ�� ������ ������ ����� ������ �߰�����
		wchar_t szTestW[10] = L"abc�ѱ�"; //wchar_t 2����Ʈ �ڷ���
	}

	{
		wchar_t szName[10] = L"Raimond";
		int iLen = wcslen(szName);//���ڿ��� ���̸� �˷��ִ� �Լ�
		iLen = GetLenth(szName); //Ŀ���� �Լ�

		//���ڿ� �̾���̱�

		{
			wchar_t szString[100] = L"abc";
			wcscat_s(szString, 100, L"def");
			wcscat_s(szString, 100, L"ghi");

		}

		{
			wchar_t szString[100] = L"abc";
			StrCat(szString, 10, L"def");

			//wcscmp �ι��ڿ��� ���ؼ� ������ ������ �� �ƴϸ� ����
			int iRet = wcscmp(L"ca",L"ca");
			iRet = StrCmp(L"abcdef", L"abc");

		}
	}

	{
		//����ü�� ������
		MYST s = {};

		s.a;
		int a;

		MYST s2;
		MYST s3;

		MYST* pST = &s;
		pST + 1;

		(*pST).a = 100;
		(*pST).f = 3.14f;

		pST->a = 100;
		pST->f = 3.14f;
	}

	return 0;

}

