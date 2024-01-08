#include <iostream>
#include "Arr.h"
#include "CArr.h"


class CTest
{
private:
	int a;


public:
	CTest()
		: a(10) //�ʱ�ȭ
	{


	}
};

void whatisRef()
{
//�ڷ���* ������;	~�ڷ��� ������Ÿ�Ժ���
//*�����ͺ�����;	������Ÿ�Ժ����� ����Ǿ��ִ� �ּҸ� ������
//&����;			������ �ּҰ�
//�ڷ���& ������;	���۷������� ����(������ ���忡���� �����ͳ� ���۷����� ����)

int a = 10;

int* p = &a;
*p = 100; //������Ÿ���� �����ּҿ� a�� �ּҰ��� �ְ�, �ش��ּҸ� �������ؼ� 100�� ����

int& iRef = a; //���� ������ int* const p �� ����, ȣ������ �ٸ�(�ڵ�����������), �ּҰ������(���谨��)
iRef = 100; //���۷��������� '������ ����'�Ͽ� a�� ����

const int& iRefConst = a;
//���� ���ڸ� const int* const p2 = &a; �� ����
//iRefConst = 10; ����Ұ�

}

//����ü�� Ŭ������ Ŀ���� Ÿ��
struct tMy
{

};

class CMy
{
private:
	int m_i;
	float m_f;

public:
	void SetInt(int i) //SetInt : Private ���ڿ� ���ٰ����ϰ�����
	{
		m_i = i;
	}
	/*C��Ÿ�Ϸ� �ڵ���
	void SetInt(CMy* _this, int i)
	{
		_this->m_i = i;
	}
	*/

	//���Կ����� �� ��ü(C++������ �Ƚᵵ ���� ������)
	const CMy& operator =(const CMy& _Other)
	{
		m_i = _Other.m_i;
		m_f = _Other.m_f;

		return *this;
	}


public:
	CMy()
		: m_i(100)
		, m_f(0.f)
	{
	}

	~CMy()
	{

	}


};

template<typename T>
T Add(T a, T b)
{
	return a + b;
}


int main()
{
	/*C++Ŭ���� Ư¡
	* 	�������� ������ : private(���� �����), protected(���), public(���� ����ü�� ����)
	*  	�����Լ�(�ɹ��Լ�) : �ش� Ŭ������ ��ü�� �ʿ�, ȣ���ϸ� �ش� ��ü�� �ּҰ� this-> (������)�� ���޵�
	* 	//������,�Ҹ��� : �ȿ� �ʱ�ȭ ���� ����  (���ص� ����������Ҹ��, �ƹ���������� �������θ�)
	*/
	tArr arr = {  };
	InitArr(&arr);
	PushBack(&arr, 10);

	arr.iCount = 100;

	ReleaseArr(&arr);
	CMy c;
	c.SetInt(10);

	CMy c1;
	c1.SetInt(10);

	CMy c2;
	c2.SetInt(100);

	CMy c3;
	c3.SetInt(1000);

	c3 = c2; //Ŀ���� �ڷ����� ��� ó������ c++���� �������س��� [���Կ�����_�����ε�], this->�� c3, _Other�� c2
	//c3 + c2; : �ٸ� ������� ���� ����������




	int i1 = 0;
	int i2 = 5;
	int i3 = 10;

	i1 = i2 = i3; //==10

	//C++(�����ڼҸ��� �ڵ�����) �����Ҵ� �ڷ��� �˷���� new, delete VS C��Ÿ�� malloc, free (ũ��˷��ְ�, �����ͷ� ���ӻ��� ����)
	CTest* pTest = new CTest;
	delete pTest;

	//Arr VS Carr ����
	//tArr arr = {};
	InitArr(&arr); //�� ĭ Ȯ�� ��

	PushBack(&arr, 10);
	PushBack(&arr, 20);
	PushBack(&arr, 30);

	ReleaseArr(&arr);

	CArr<float> carr;
	carr.push_back(10.14f);
	carr.push_back(20.28f);
	carr.push_back(30.333f);
	//�������������� �Ҹ��� �ڵ� ����

	float fData = carr[1]; //20.28
	//carr[1] = 100; //C���� �⺻ �����Ǵ� �迭 �����ڴ� �ƴ����� Ŭ������ ����� ���׷��̵� ���� ���� Ȱ���Ϸ��� ����
	//*���۷���(&)��� ��� ������(*) �ּҷ� �����ϴ� *carr[1] = 100�� ������ ������ ����� ���⿡ ���������� ���� �ڵ�


	//�Լ� ���ø�
	int i = Add<int>(10, 20);
	

	return 0;

}