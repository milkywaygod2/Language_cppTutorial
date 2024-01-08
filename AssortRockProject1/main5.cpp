#include <iostream>
#include "CList.h"
#include "CArr.h"

#include <vector> //�����迭 ���ø�
#include <list> //����Ʈ ���ø�

namespace MYSPACE //�̸�����
{
	int g_int;
}

namespace OTHERSPACE
{
	int g_int;
}

using namespace std;
using std::cout;
using std::cin; // ���̻� �� :: �ּ� �Ƚᵵ��, �����ϸ� namespace������ ��� ���
using MYSPACE::g_int; // Ư����ɸ� ���־��ڴ�

void MyEndL()
{
	wprintf(L"\n");
}


class cMyOstream //cin + cout ����
{
public:
	cMyOstream& operator << (int _idata)
	{
		wprintf(L"%d", _idata);
		return *this;
	}

	cMyOstream& operator << (const wchar_t* _pString)
	{
		wprintf(L"%s", _pString); //������� == %s
		return *this;
	}
	
	cMyOstream& operator << (void(*_pFunc)(void))
	{
		_pFunc();
		return *this;
	}
	
	cMyOstream& operator >> (int& _idata)
	{
		scanf_s("%d", _idata);
		return *this;
	}

};

cMyOstream mycout;

class CTest
{
public:
	int m_i;

public:
	//���� ���������ָ� �ڵ����� �����Ǵ� "���Կ�����"
	CTest& operator = (const CTest& _other)
	{
		m_i = _other.m_i;
		return *this;
	}

public:
	CTest()
	: m_i(0)
	{

	}

	~CTest()
	{

	}
	
	//���� ���������ָ� �ڵ����� �����Ǵ� "���������"
	CTest(const CTest& _other)
		: m_i(_other.m_i)
	{

	}
};

int main()
{
	CList<float> List;

	for (int i = 0; i < 4; ++i)
	{
		List.push_back(i);
	}


	setlocale(LC_ALL, "korean");//�ƽ�Ű�ڵ� �ѱ۷� ����
	_wsetlocale(LC_ALL, L"korean");//2����Ʈ �ƽ�Ű�ڵ� �ѱ۷� ����

	cout << "�ȳ�" << 10 << endl; //std::
	wcout << L"�ȳ�" << 10; //2����Ʈ���ڿ� 
	mycout << 10 << 20 << 30;
	mycout << L"�ȳ�" << 10; 
	mycout << L"�ȳ�" << 10 << L" " << L"���ڿ�" << MyEndL;


	int iInput = 0;
	//cin >> iInput; //std::

	MYSPACE::g_int = 0;
	OTHERSPACE::g_int = 0;




	//---------------------------------------------------------------------------------------------------
	//iterator (����Ŭ���� ����Ŭ���� inner class), ����Ű�� ����
	//���� �ڷᱸ�� ������ �ݺ��ڸ� �̿��ؼ� ������ �����Ϳ� ���ٶǴ� �ݺ��� �� �ְ� ���ִ� �������̽�
	//�ڷᱸ������ �۵������ �ٸ�����, ����ڰ� �װ� �� �� �ʿ���� ������ �����ϰ� �������ִ� ��

	//--------------vector
	vector<int> vecInt;
	vecInt.push_back(10);
	vecInt.push_back(20); //push_back�ι������ �ε���1���� �����迭 ������, �� �׷��� �Ʒ� vecInt[1] �����ϸ� �޸� ������
	//vecInt.push_front(100); ���Ϳ��� push_front ���� �ֳ�, �ڷᰡ ���ʺ��� �� �ſ��� list�� �����ؾ�
	
	vecInt.at(1) = 100;
	vecInt[1] = 100;

	vecInt.data(); //�迭�� ���ʽ����ּҸ� ��ȯ
	vecInt.size();
	vecInt.capacity();

	for (size_t i = 0; i < vecInt.size(); ++i)
	{
		cout << vecInt[i] << endl;
	}

	vector<int>::iterator veciter = vecInt.begin();
	*veciter = 100;
	++veciter; //���������ͷ� �̵�

	vecInt[0] = 100;
	
	for (int i = 0; i < 10; ++i)
	{
		vecInt.push_back(i);
	}

	//---------------iterator �������ø��������� ������
	CArr<int> myvector;

	myvector.push_back(1);
	myvector.push_back(2);
	myvector.push_back(3);

	CArr<int>::iterator myiter = myvector.begin();
	myiter = myvector.erase(myiter);
	int k = *myiter;
	


	//*myiter ++�������� --�������� != == ���� �Լ� ���� �ʿ�
	for ( ; myiter != myvector.end(); ++myiter)
	{
		cout << *myiter << endl;
	}

	myiter = myvector.begin();
	int iData_vector = (*myiter++);

	CTest t1, t2;
	t1 = t2;

	t1.m_i = 100;
	t2 = t1;

	//����������� ��� ����� ������ ���ÿ�
	CTest t3(t1);

	//vecInc.erase();
	vector<int> vecInt1;

	vecInt1.push_back(100);
	vecInt1.push_back(200);
	vecInt1.push_back(300);
	vecInt1.push_back(400);

	vector<int>::iterator veciter1 = vecInt1.begin();
	veciter1 = vecInt1.erase(veciter1); //�����ϰ� iterator�� ������==�ּҿ���, �ѹ��� �޾���� �����ȳ�
	int i = *veciter1;


	vecInt1.clear(); //������ ������, ������ �״�������� ���⼭�� ����

	//1~10�� ���Ϳ� �Է�
	for (int i = 0; i < 11; ++i) //10���� �ϸ� ������ �ֳ�!?
	{
		vecInt1.push_back(i + 1);
	}

	//¦���� ����
	veciter1 = vecInt1.begin();
	for (; veciter1 != vecInt1.end(); )
	{
		if (0 == *veciter1 % 2)
		{
			//����
			veciter1 = vecInt1.erase(veciter1);
		}
		else
		{
			++veciter1;
		}
	}

	for (int i = 0; i < vecInt1.size(); ++i)
	{
		cout << vecInt1[i] << endl;
	}


	

	//--------------list
	list<int> listInt;
	listInt.push_back(10);
	listInt.push_front(100);

	//listInt[1] ���ӵ� ������ �ƴ� �ڷᱸ���μ� ������ ������ �ֱ⶧���� ����x
	//listInt.capacity(); list�� �����迭�� �ƴ����� capacity���� ����
	listInt.size();

	list<int>::iterator iter = listInt.begin();
	int iData = *iter; //�����Ͱ� �ƴ� �������ϴ� ������ �����ε�, Ŭ������ ��ü�ϻ���
	++iter; //���������ͷ� �̵�
	iData = *iter;
	//listInt.erase();

	for (iter = listInt.begin(); iter != listInt.end(); ++iter) //.end ���İɱ�������� ������ ���� �������� ���õǾ�����
	{
		cout << *iter << endl;
	}

	//���� list�� �̿��� insert���Ȯ��
	list<int> intlist;
	intlist.push_back(100);
	intlist.push_back(300);

	list<int>::iterator it = intlist.begin();
	it = intlist.insert(++it, 200); //insert ��Ī�� �� �տ� ��



	//list iterator
	CList<int> mylist;

	mylist.push_back(100);
	mylist.push_back(300);
	mylist.push_back(400);

	CList<int>::iterator listiter = mylist.begin();
	*listiter = 150;

	++listiter; //300����Ű��
	--listiter; //100����Ű��
	++listiter; //300����Ű��

	listiter = mylist.insert(listiter, 200);

	cout << "==================" << endl;
	cout << "list iterator test" << endl;
	cout << "==================" << endl;
	for (listiter = mylist.begin(); listiter != mylist.end(); ++listiter )
	{
		cout << *listiter << endl;
	}







 	return 0;


}