#include <iostream>
#include "CList.h"
#include "CArr.h"

#include <vector> //가변배열 탬플릿
#include <list> //리스트 탬플릿

namespace MYSPACE //이름공간
{
	int g_int;
}

namespace OTHERSPACE
{
	int g_int;
}

using namespace std;
using std::cout;
using std::cin; // 더이상 이 :: 주소 안써도됨, 남발하면 namespace본연의 기능 상실
using MYSPACE::g_int; // 특정기능만 자주쓰겠다

void MyEndL()
{
	wprintf(L"\n");
}


class cMyOstream //cin + cout ㅋㅋ
{
public:
	cMyOstream& operator << (int _idata)
	{
		wprintf(L"%d", _idata);
		return *this;
	}

	cMyOstream& operator << (const wchar_t* _pString)
	{
		wprintf(L"%s", _pString); //문자출력 == %s
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
	//따로 설정안해주면 자동으로 생성되는 "대입연산자"
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
	
	//따로 설정안해주면 자동으로 생성되는 "복사생성자"
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


	setlocale(LC_ALL, "korean");//아스키코드 한글로 변경
	_wsetlocale(LC_ALL, L"korean");//2바이트 아스키코드 한글로 변경

	cout << "안녕" << 10 << endl; //std::
	wcout << L"안녕" << 10; //2바이트문자열 
	mycout << 10 << 20 << 30;
	mycout << L"안녕" << 10; 
	mycout << L"안녕" << 10 << L" " << L"문자열" << MyEndL;


	int iInput = 0;
	//cin >> iInput; //std::

	MYSPACE::g_int = 0;
	OTHERSPACE::g_int = 0;




	//---------------------------------------------------------------------------------------------------
	//iterator (포함클래스 내부클래스 inner class), 가리키는 수단
	//각종 자료구조 내에서 반복자를 이용해서 내부의 데이터에 접근또는 반복할 수 있게 해주는 인터페이스
	//자료구조마다 작동방식은 다르지만, 사용자가 그걸 다 알 필요없이 사용법을 동일하게 셋팅해주는 툴

	//--------------vector
	vector<int> vecInt;
	vecInt.push_back(10);
	vecInt.push_back(20); //push_back두번해줘야 인덱스1까지 가변배열 생성됨, 안 그러고 아래 vecInt[1] 실행하면 메모리 오류남
	//vecInt.push_front(100); 백터에는 push_front 없음 왜냐, 자료가 앞쪽부터 들어갈 거였음 list로 정리해야
	
	vecInt.at(1) = 100;
	vecInt[1] = 100;

	vecInt.data(); //배열의 최초시작주소를 반환
	vecInt.size();
	vecInt.capacity();

	for (size_t i = 0; i < vecInt.size(); ++i)
	{
		cout << vecInt[i] << endl;
	}

	vector<int>::iterator veciter = vecInt.begin();
	*veciter = 100;
	++veciter; //다음데이터로 이동

	vecInt[0] = 100;
	
	for (int i = 0; i < 10; ++i)
	{
		vecInt.push_back(i);
	}

	//---------------iterator 셀프템플릿버전에도 만들어보기
	CArr<int> myvector;

	myvector.push_back(1);
	myvector.push_back(2);
	myvector.push_back(3);

	CArr<int>::iterator myiter = myvector.begin();
	myiter = myvector.erase(myiter);
	int k = *myiter;
	


	//*myiter ++전위후위 --전위후위 != == 각종 함수 구현 필요
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

	//복사생성자의 기능 선언과 대입을 동시에
	CTest t3(t1);

	//vecInc.erase();
	vector<int> vecInt1;

	vecInt1.push_back(100);
	vecInt1.push_back(200);
	vecInt1.push_back(300);
	vecInt1.push_back(400);

	vector<int>::iterator veciter1 = vecInt1.begin();
	veciter1 = vecInt1.erase(veciter1); //삭제하고난 iterator는 무쓸모==주소오류, 한번더 받아줘야 오류안남
	int i = *veciter1;


	vecInt1.clear(); //데이터 날리기, 공간은 그대로있으나 여기서는 무시

	//1~10을 벡터에 입력
	for (int i = 0; i < 11; ++i) //10으로 하면 에러남 왜냐!?
	{
		vecInt1.push_back(i + 1);
	}

	//짝수만 제거
	veciter1 = vecInt1.begin();
	for (; veciter1 != vecInt1.end(); )
	{
		if (0 == *veciter1 % 2)
		{
			//제거
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

	//listInt[1] 연속된 구조가 아닌 자료구조로서 오해의 소지가 있기때문에 지원x
	//listInt.capacity(); list는 가변배열이 아님으로 capacity개념 없음
	listInt.size();

	list<int>::iterator iter = listInt.begin();
	int iData = *iter; //포인터가 아님 역참조하는 느낌의 오버로딩, 클래스의 객체일뿐임
	++iter; //다음데이터로 이동
	iData = *iter;
	//listInt.erase();

	for (iter = listInt.begin(); iter != listInt.end(); ++iter) //.end 수식걸기좋으라고 마지막 것의 다음으로 세팅되어있음
	{
		cout << *iter << endl;
	}

	//원래 list를 이용한 insert기능확인
	list<int> intlist;
	intlist.push_back(100);
	intlist.push_back(300);

	list<int>::iterator it = intlist.begin();
	it = intlist.insert(++it, 200); //insert 지칭한 곳 앞에 들어감



	//list iterator
	CList<int> mylist;

	mylist.push_back(100);
	mylist.push_back(300);
	mylist.push_back(400);

	CList<int>::iterator listiter = mylist.begin();
	*listiter = 150;

	++listiter; //300가리키고
	--listiter; //100가리키고
	++listiter; //300가리키고

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