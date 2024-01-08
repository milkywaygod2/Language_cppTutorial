#include <iostream>
#include <map>
#include <set>
#include <string>

#include "C_BST.h"

using std::wcout;//�ѱ��� 2����Ʈ ���ڿ�
using std::endl;

using std::map;
using std::make_pair;

using std::set;

using std::wstring;

//������
enum class MY_TYPE //�����ϸ� ���ӵ� ���ڷ� �νĵ�, ������ ���� / class��Ÿ�Ϸ� ����� :: �ڷ��� �Ѵ� �ʿ�����
{
	TYPE_1, //0
	TYPE_2, //1
	TYPE_3, //2
	TYPE_5 = 100,
	TYPE_6, //101
};

enum class MY_TYPE1
{
	TYPE_10,
};

#define MAN		1 //��ó����, ������������ �۾���(������Ҷ� �ȳ��� �׳� 1�� ����), �ϰ������� �������� �� �ִ� ����
#define WOMAN	2

struct tStdInfo
{
	wchar_t szName[20];		//�л��̸�20�����̳�
	unsigned char age;		//��ȣ����+8��Ʈ������������ (256��)
	unsigned char gender;

	tStdInfo()
		: szName{}
		, age(0)
		, gender(0)
	{}

	tStdInfo(const wchar_t* _pName, unsigned char _age, unsigned char _gender)
		: szName{}
		, age(_age)
		, gender(_gender)
	{
		wcscpy_s(szName, _pName);//������ ������, ������ ����
	}
};

int main()
{
	int a = (int)MY_TYPE::TYPE_1; //class�� �����ϸ� �ڷ���, :: �Ѵ� �ʿ�
	MY_TYPE1::TYPE_10;


	//����Ž��
	//1.������ �Ǿ��ִ� ������ �ʿ�

	//����Ž��Ʈ��
	//1.����Ž���� ����� �� �ְ� ��ȵ� ����Ʈ��
	//2.�Է� ȿ���� 0(logN)
	//3.Ž�� ȿ���� 0(logN)
	//4.Ʈ����� �뷱���� �����Ǿ�� Ž��ȿ���� ������ > �ڰ���������ʿ� (AVL, Red/Black)


	set<int> setInt;

	setInt.insert(100);
	setInt.insert(50);
	setInt.insert(150);


	const wchar_t* pStr = L"���ڿ�";
	
	map<const wchar_t*, tStdInfo> mapData; //Ÿ�Եΰ� �ʿ����, ó���� Ű��, �ι�°�� ������
	//������� ���ڿ��� �ּҰ����� ã�� �ִ���, Ű�� ����ü�� ���Ϸ��� ���ڿ� �ٷ�� Ŭ���� �ʿ�

	tStdInfo info1(L"������",32,MAN);
	tStdInfo info2(L"������",29,WOMAN);

	mapData.insert(make_pair(L"������", info1));
	mapData.insert(make_pair(L"������", info2));

	map<const wchar_t*, tStdInfo>::iterator mapiter;
	mapiter = mapData.find(L"������"); //find�Լ��� ����Ű�� iterator�� ��ȯ����


	_wsetlocale(LC_ALL, L"korean");//�ѱ��� ��Ű��

	if (mapiter == mapData.end())
	{
		wcout << L"�����͸� ã�� �� �����ϴ�." << endl;
	}
	else
	{
		wcout << L"�̸� : " << mapiter->second.szName << endl;
		wcout << L"���� : " << mapiter->second.age << endl;
		wcout << L"���� : ";					//1,2�� ����Ǿ����� �ؽ�Ʈ ��°���� ���� ���������
		if (MAN == mapiter -> second.gender)	//MAN��� 1�־ ����
		{
			wcout << L"����" << endl;
		}
		else if (WOMAN == mapiter->second.gender)
		{
			wcout << L"����" << endl;
		}
		else
		{
			wcout << L"�� �� �����ϴ�." << endl;
		}
	}

	//��ȯ�ϴ� iterator�� pair�����͸� ��ȯ, pair��� ����ü�� ���� first(const wchar_t*), second(�츮�� ���� ����ü)�� ������
	(*mapiter).first;
	(*mapiter).second;
	mapiter->first;
	mapiter->second;

	map<wstring, tStdInfo> manStdInfo;
	//��wstring��� ���� ���� Ŭ������ �񱳿��� �����س����� �װɷε� ok

	wstring str; //�����迭���� vector<wchar_t>�� ���� ����
	str = L"abcdef"; //������ L""�� �ּ�����, wstringŬ������ ��� ������ ��ü�� �����ϴ� ���Կ��� �����Ǿ�����
	str += L"ghijkl";
	str += L"mnopqrs";
	str[6] = L'x'; //g�� x�� �ٲ�
	str = L"wlsgudendlqslek"; //������

	wstring str1; //�񱳿��� ���Կ��� ��� �� �����Ǿ�����
	if (str < str1)
	{

	}

	C_BST<int, int> bstint;
	
	bstint.insert(make_bstpair(100, 0));
	bstint.insert(make_bstpair(150, 0));
	bstint.insert(make_bstpair(50, 0));
	bstint.insert(make_bstpair(250, 0));
	bstint.insert(make_bstpair(75, 0));
	bstint.insert(make_bstpair(125, 0));
	bstint.insert(make_bstpair(25, 0));
	//				100
	//		50				150
	//	25		75		125		250
	//

	C_BST<int, int>::iterator Iter = bstint.begin(); //25
	Iter = bstint.find(150); //150

	Iter = bstint.erase(Iter); //250��ȯ, ���� �ö��
	//				100
	//		50				250
	//	25		75		125			-
	//
	
	Iter = bstint.find(100); //100
	Iter = bstint.erase(Iter); //125��ȯ, ���� �ö��
	//				125
	//		50				250
	//	25		75		-			-
	//












	//map make_pair��� ����
	map<int, int> mapInt;
	mapInt.insert(make_pair(100, 100));
	
	map<int, int>::iterator iter = mapInt.find(100);
	if (iter == mapInt.end())
	{

	}
	//---------------------
	(*Iter).first;
	Iter->first;

	(*Iter).second;
	Iter->second;

	//�⺻����
	tPair<int, int> pair;
	tPair<int, int>* pPair = &pair;
	pPair->first;
	pPair->second;

	Iter = bstint.begin();
	for (; Iter != bstint.end();++Iter)
	{
		wcout << Iter->first << L"," << Iter->second << endl;
	}

	Iter = bstint.begin();
	++(++Iter); //���� end-1 �� ���� �Ф̤Ф�

	for (; Iter != bstint.begin(); --Iter)
	{
		wcout << Iter->first << L"," << Iter->second << endl;
	}
	wcout << Iter->first << L"," << Iter->second << endl;

	return 0;

}