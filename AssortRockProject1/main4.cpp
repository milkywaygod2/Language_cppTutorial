#include <iostream>
#include "Arr.h"
#include "CArr.h"


class CTest
{
private:
	int a;


public:
	CTest()
		: a(10) //초기화
	{


	}
};

void whatisRef()
{
//자료형* 변수명;	~자료형 포인터타입변수
//*포인터변수명;	포인터타입변수에 저장되어있는 주소를 역참조
//&변수;			변수의 주소값
//자료형& 변수명;	레퍼런스변수 선언(컴파일 입장에서는 포인터나 레퍼런스나 동일)

int a = 10;

int* p = &a;
*p = 100; //포인터타입의 변수주소에 a의 주소값을 넣고, 해당주소를 역참조해서 100를 수정

int& iRef = a; //굳이 따지면 int* const p 와 동일, 호출방식이 다름(코딩자유도증가), 주소개념없음(위험감소)
iRef = 100; //레퍼런스변수로 '원본을 참조'하여 a를 수정

const int& iRefConst = a;
//굳이 하자면 const int* const p2 = &a; 와 동일
//iRefConst = 10; 수행불가

}

//구조체나 클래스나 커스텀 타입
struct tMy
{

};

class CMy
{
private:
	int m_i;
	float m_f;

public:
	void SetInt(int i) //SetInt : Private 인자에 접근가능하게해줌
	{
		m_i = i;
	}
	/*C스타일로 코딩시
	void SetInt(CMy* _this, int i)
	{
		_this->m_i = i;
	}
	*/

	//대입연산자 의 실체(C++에서는 안써도 내장 컴파일)
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
	/*C++클래스 특징
	* 	접근제한 지정자 : private(변수 숨기기), protected(상속), public(공개 구조체랑 동일)
	*  	전용함수(맴버함수) : 해당 클래스의 객체가 필요, 호출하면 해당 객체의 주소가 this-> (포인터)로 전달됨
	* 	//생성자,소멸자 : 안에 초기화 보통 넣음  (안해도 디폴드생성소멸됨, 아무기능은없이 명목상으로만)
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

	c3 = c2; //커스텀 자료형도 어떻게 처리할지 c++에서 컴파일해놓음 [대입연산자_오버로딩], this->가 c3, _Other가 c2
	//c3 + c2; : 다른 연산들은 직접 만들어줘야함




	int i1 = 0;
	int i2 = 5;
	int i3 = 10;

	i1 = i2 = i3; //==10

	//C++(생성자소멸자 자동지원) 동적할당 자료형 알려줘야 new, delete VS C스타일 malloc, free (크기알려주고, 포인터로 쓰임새를 지정)
	CTest* pTest = new CTest;
	delete pTest;

	//Arr VS Carr 예시
	//tArr arr = {};
	InitArr(&arr); //두 칸 확보 ㅎ

	PushBack(&arr, 10);
	PushBack(&arr, 20);
	PushBack(&arr, 30);

	ReleaseArr(&arr);

	CArr<float> carr;
	carr.push_back(10.14f);
	carr.push_back(20.28f);
	carr.push_back(30.333f);
	//지역변수임으로 소멸자 자동 적용

	float fData = carr[1]; //20.28
	//carr[1] = 100; //C에서 기본 제공되는 배열 연산자는 아니지만 클래스로 비슷한 업그레이드 버전 만들어서 활용하려는 취지
	//*레퍼런스(&)방식 대신 포인터(*) 주소로 수정하는 *carr[1] = 100도 동작은 하지만 사람이 보기에 직관적이지 않은 코딩


	//함수 탬플릿
	int i = Add<int>(10, 20);
	

	return 0;

}