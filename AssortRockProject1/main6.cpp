#include <iostream>
#include <map>
#include <set>
#include <string>

#include "C_BST.h"

using std::wcout;//한글은 2바이트 문자열
using std::endl;

using std::map;
using std::make_pair;

using std::set;

using std::wstring;

//열거형
enum class MY_TYPE //나열하면 연속된 숫자로 인식됨, 지정도 가능 / class스타일로 쓸경우 :: 자료형 둘다 필요해짐
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

#define MAN		1 //전처리기, 컴파일이전에 작업됨(디버깅할때 안나옴 그냥 1로 나옴), 일괄적으로 대입해줄 수 있는 정의
#define WOMAN	2

struct tStdInfo
{
	wchar_t szName[20];		//학생이름20글자이내
	unsigned char age;		//부호없는+8비트정수형데이터 (256개)
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
		wcscpy_s(szName, _pName);//저장할 목적지, 저장할 원본
	}
};

int main()
{
	int a = (int)MY_TYPE::TYPE_1; //class로 구현하면 자료형, :: 둘다 필요
	MY_TYPE1::TYPE_10;


	//이진탐색
	//1.정렬이 되어있는 데이터 필요

	//이진탐색트리
	//1.이진탐색을 사용할 수 있게 고안된 이진트리
	//2.입력 효율은 0(logN)
	//3.탐색 효율은 0(logN)
	//4.트리모양 밸런스가 유지되어야 탐색효율이 유지됨 > 자가균형기능필요 (AVL, Red/Black)


	set<int> setInt;

	setInt.insert(100);
	setInt.insert(50);
	setInt.insert(150);


	const wchar_t* pStr = L"문자열";
	
	map<const wchar_t*, tStdInfo> mapData; //타입두개 필요로함, 처음꺼 키값, 두번째가 데이터
	//ㄴ사실은 문자열의 주소값으로 찾고 있는중, 키값 그자체로 비교하려면 문자열 다루는 클래스 필요

	tStdInfo info1(L"진형두",32,MAN);
	tStdInfo info2(L"배유리",29,WOMAN);

	mapData.insert(make_pair(L"진형두", info1));
	mapData.insert(make_pair(L"배유리", info2));

	map<const wchar_t*, tStdInfo>::iterator mapiter;
	mapiter = mapData.find(L"진형두"); //find함수는 가리키는 iterator를 반환해줌


	_wsetlocale(LC_ALL, L"korean");//한국어 패키지

	if (mapiter == mapData.end())
	{
		wcout << L"데이터를 찾을 수 없습니다." << endl;
	}
	else
	{
		wcout << L"이름 : " << mapiter->second.szName << endl;
		wcout << L"나이 : " << mapiter->second.age << endl;
		wcout << L"성별 : ";					//1,2로 저장되어있음 텍스트 출력경우의 수로 나눠줘야함
		if (MAN == mapiter -> second.gender)	//MAN대신 1넣어도 무관
		{
			wcout << L"남자" << endl;
		}
		else if (WOMAN == mapiter->second.gender)
		{
			wcout << L"여자" << endl;
		}
		else
		{
			wcout << L"알 수 없습니다." << endl;
		}
	}

	//반환하는 iterator중 pair데이터를 반환, pair라는 구조체의 인자 first(const wchar_t*), second(우리가 만든 구조체)로 구성됨
	(*mapiter).first;
	(*mapiter).second;
	mapiter->first;
	mapiter->second;

	map<wstring, tStdInfo> manStdInfo;
	//ㄴwstring대신 내가 만든 클래스에 비교연산 구현해놓으면 그걸로도 ok

	wstring str; //가변배열구조 vector<wchar_t>와 거의 유사
	str = L"abcdef"; //원래는 L""는 주소지만, wstring클래스의 경우 데이터 자체를 복사하는 대입연산 구현되어있음
	str += L"ghijkl";
	str += L"mnopqrs";
	str[6] = L'x'; //g가 x로 바뀜
	str = L"wlsgudendlqslek"; //덮어씌우기

	wstring str1; //비교연산 대입연산 등등 다 구현되어있음
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

	Iter = bstint.erase(Iter); //250반환, 위로 올라옴
	//				100
	//		50				250
	//	25		75		125			-
	//
	
	Iter = bstint.find(100); //100
	Iter = bstint.erase(Iter); //125반환, 위로 올라옴
	//				125
	//		50				250
	//	25		75		-			-
	//












	//map make_pair사용 예시
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

	//기본문법
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
	++(++Iter); //ㅋㅋ end-1 은 없냐 ㅠㅜㅠㅜ

	for (; Iter != bstint.begin(); --Iter)
	{
		wcout << Iter->first << L"," << Iter->second << endl;
	}
	wcout << Iter->first << L"," << Iter->second << endl;

	return 0;

}