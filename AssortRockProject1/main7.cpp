#include <iostream>
#include <map>
#include <set>
#include <string>

using std::wcout;//한글은 2바이트 문자열
using std::endl;



// 객체지향 언어 특징
// 1.캡슐화 (은닉성)
// 2.상속 (오버라이딩)
// 3.다형성 (상속관계에서 포인터의 특성과 활용법(Vutual+dynamic_cast))
// 4.추상화
// 
// 
// #상속
// - a자식이라고 해도 부모 private에 접근 불가, 부모가 protected 분류시 자식까지는 접근 가능
// - b자식, 부모 생성 소멸 초기화는 각자 계산으로 각자 실행
// - c순서는? 부모는 먼저 들어가서 나중에 나옴 (모범)
//		((생성자)) 자식 호출 => 부모호출 ====> 부모 생성자/실행 => 자식 생성자/실행
//		((소멸자)) 자식 호출 => 부모호출 ====> 자식 소멸자/실행 => 부모 소멸자/실행
// - d부모 생성자 여러개일때는 기본생성자가 기본, 특정하고 싶으면 오버로딩 함수에 맞게 자녀 생성자에 부모생성 함수를 명시해야함
// 
// #오버라이딩
// - e부모의 함수를 사용하다가 재정의나 예외처리가 필요한 경우 (오버로딩 : 함수명이 같은데 인자가 달라서 구별하는 경우)
// 
// #다형성 (오버라이딩관련)
// - 부모포인터로는 아래를 가리킬 수 있으나, 그 역은 성립하지 않음
// - 오버라이딩된 함수를 부모포인터로 가리키기 위해 부모함수에 가상함수(Virtual)를 적용(자식 클래스에는 자동적용생략적용됨 but 가독성위해 자식클래스에도 명기를 권장)
//		ㄴ부모함수를 가상함수 처리해두면, 부모포인터로 모든 함수 호출가능, 단 조부모에게는 적용되지 않음
// 
// #다운캐스팅 (다형성에서 금지된 행위를 비교적 안전하게 하는 방법)
// - dynamic_cast : 비록 부모타입안에 속해있지만 확실히 자식객체 함수라고 생각될때, 자식포인터로 부모타입을 캐스팅해서 받는 경우 (추측이 틀렸다면 nullptr을 반환해주는 기능탑재)
//		ㄴ안전장치로 nullptr 반환하는 특성을 이용해서, RTTI (Run Time Type Identification or Inforamtion) 기능으로 활용할 수도 있음
// 
//





class CParent
{
protected:
	int m_i;


public:
	void SetInt(int _a)
	{
		m_i = _a;
	}

	void Output() // 가상함수 (#다형성)
	{
		wcout << "f(x), belong to Parent" << endl;
	}

	virtual void OutputV() // 가상함수 (#다형성)
	{
		wcout << "f(x), belong to Parent" << endl;
	}

public:
	CParent()
		: m_i(0)
	{}
	CParent(int _a)
		: m_i (_a)
	{}
	~CParent()
	{}
};


class CChild : public CParent //상속문법
{
private:
	float m_f;


public:
	void SetFloat(int _f)
	{
		m_f = _f;
	}

	void OutputV() // 가상함수 (#다형성)
	{
		wcout << "f(y), belong to Child" << endl;
	}

	void NewFunc()
	{
		;
	}

public:
	CChild()
		: m_f(0.f)
		,CParent(1000) // d
	{}

};


class CChildchild : public CChild
{
private:
	long long m_ll;

public:

	void Output()
	{
		wcout << "f(z), belong to Childchild" << endl;
	}

	void OutputV() // 가상함수 (#다형성)
	{
		wcout << "f(z), belong to Childchild" << endl;
	}


};


int main()
{
	CParent parent;
	CChild child;
	CChildchild childchild;

	parent.SetInt(10);
	child.SetInt(10);
	childchild.SetInt(10);
	childchild.SetFloat(10.f);

	parent.Output();
	child.Output(); 
	childchild.Output(); //오버라이딩
	childchild.CParent::Output(); //오버라이딩 예외, 함수지정



	//-------3.다형성--------
	CParent* pParent = &child; //실제 객체는 자식, 부모포인터 사이즈로 자식 주소 메모리를 받더라도 문법상 문제는 없음 (단 정보 제한)
	//CChild* pChild = &parent; //자식포인터 사이즈가 더 큰데 부모 주소 메모리 읽어오려고 하면, 그뒤에 이상한 메모리까지 읽어오게됨 (오류)


	wcout << endl << endl << endl << "------ - 3.다형성--------"<< endl;
	pParent = nullptr;

	wcout << endl << "pParent(&parent)->Output" << endl;
	parent.Output();
	pParent = &parent;
	pParent->Output();

	wcout << endl << "pParent(&child)->Output" << endl;
	child.Output();
	pParent = &child;
	pParent->Output();

	wcout << endl << endl << "---------------" << endl << "pParent(&parent)->OutputV" << endl;
	parent.OutputV();
	pParent = &parent;
	pParent->OutputV();

	wcout << endl << "pParent(&child)->OutputV" << endl;
	child.OutputV();
	pParent = &child;
	pParent->OutputV();

	wcout << endl << "pParent(&Childchild)->OutputV" << endl;
	childchild.OutputV();
	pParent = &childchild;
	pParent->OutputV();


	//다운캐스팅(dynamic_cast)
	pParent = &parent;

	//((CChild*)pParent)->NewFunc(); //강제캐스팅 의도치않은 메모리 참조 미싱으로 심각한 에러의 위험성있음

	CChild* pChild = dynamic_cast<CChild*>(pParent); //일단 시도해보고 의도치않은 참조시 null반환해줌

	if (nullptr == pChild)
	{
		pChild->NewFunc();
	}


	return 0;
}