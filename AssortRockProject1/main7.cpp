#include <iostream>
#include <map>
#include <set>
#include <string>

using std::wcout;//�ѱ��� 2����Ʈ ���ڿ�
using std::endl;



// ��ü���� ��� Ư¡
// 1.ĸ��ȭ (���м�)
// 2.��� (�������̵�)
// 3.������ (��Ӱ��迡�� �������� Ư���� Ȱ���(Vutual+dynamic_cast))
// 4.�߻�ȭ
// 
// 
// #���
// - a�ڽ��̶�� �ص� �θ� private�� ���� �Ұ�, �θ� protected �з��� �ڽı����� ���� ����
// - b�ڽ�, �θ� ���� �Ҹ� �ʱ�ȭ�� ���� ������� ���� ����
// - c������? �θ�� ���� ���� ���߿� ���� (���)
//		((������)) �ڽ� ȣ�� => �θ�ȣ�� ====> �θ� ������/���� => �ڽ� ������/����
//		((�Ҹ���)) �ڽ� ȣ�� => �θ�ȣ�� ====> �ڽ� �Ҹ���/���� => �θ� �Ҹ���/����
// - d�θ� ������ �������϶��� �⺻�����ڰ� �⺻, Ư���ϰ� ������ �����ε� �Լ��� �°� �ڳ� �����ڿ� �θ���� �Լ��� ����ؾ���
// 
// #�������̵�
// - e�θ��� �Լ��� ����ϴٰ� �����ǳ� ����ó���� �ʿ��� ��� (�����ε� : �Լ����� ������ ���ڰ� �޶� �����ϴ� ���)
// 
// #������ (�������̵�����)
// - �θ������ͷδ� �Ʒ��� ����ų �� ������, �� ���� �������� ����
// - �������̵��� �Լ��� �θ������ͷ� ����Ű�� ���� �θ��Լ��� �����Լ�(Virtual)�� ����(�ڽ� Ŭ�������� �ڵ������������� but ���������� �ڽ�Ŭ�������� ��⸦ ����)
//		���θ��Լ��� �����Լ� ó���صθ�, �θ������ͷ� ��� �Լ� ȣ�Ⱑ��, �� ���θ𿡰Դ� ������� ����
// 
// #�ٿ�ĳ���� (���������� ������ ������ ���� �����ϰ� �ϴ� ���)
// - dynamic_cast : ��� �θ�Ÿ�Ծȿ� ���������� Ȯ���� �ڽİ�ü �Լ���� �����ɶ�, �ڽ������ͷ� �θ�Ÿ���� ĳ�����ؼ� �޴� ��� (������ Ʋ�ȴٸ� nullptr�� ��ȯ���ִ� ���ž��)
//		��������ġ�� nullptr ��ȯ�ϴ� Ư���� �̿��ؼ�, RTTI (Run Time Type Identification or Inforamtion) ������� Ȱ���� ���� ����
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

	void Output() // �����Լ� (#������)
	{
		wcout << "f(x), belong to Parent" << endl;
	}

	virtual void OutputV() // �����Լ� (#������)
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


class CChild : public CParent //��ӹ���
{
private:
	float m_f;


public:
	void SetFloat(int _f)
	{
		m_f = _f;
	}

	void OutputV() // �����Լ� (#������)
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

	void OutputV() // �����Լ� (#������)
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
	childchild.Output(); //�������̵�
	childchild.CParent::Output(); //�������̵� ����, �Լ�����



	//-------3.������--------
	CParent* pParent = &child; //���� ��ü�� �ڽ�, �θ������� ������� �ڽ� �ּ� �޸𸮸� �޴��� ������ ������ ���� (�� ���� ����)
	//CChild* pChild = &parent; //�ڽ������� ����� �� ū�� �θ� �ּ� �޸� �о������ �ϸ�, �׵ڿ� �̻��� �޸𸮱��� �о���Ե� (����)


	wcout << endl << endl << endl << "------ - 3.������--------"<< endl;
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


	//�ٿ�ĳ����(dynamic_cast)
	pParent = &parent;

	//((CChild*)pParent)->NewFunc(); //����ĳ���� �ǵ�ġ���� �޸� ���� �̽����� �ɰ��� ������ ���輺����

	CChild* pChild = dynamic_cast<CChild*>(pParent); //�ϴ� �õ��غ��� �ǵ�ġ���� ������ null��ȯ����

	if (nullptr == pChild)
	{
		pChild->NewFunc();
	}


	return 0;
}