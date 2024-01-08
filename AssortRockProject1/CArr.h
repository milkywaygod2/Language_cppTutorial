#pragma once

#include <Assert.h>


template<typename T>
class CArr 
{
private: //아무것도 적지 않으면 private이 디폴트

	T*		m_pData;	//8바이트
	int		m_iCount;	//4바이트
	int		m_iMaxCount;//4바이트
	

public:
	void push_back(const T& _iData);
	void resize(int _iResizeCount);
	T* data() { return m_pData; }
	int size() { return m_iCount; }
	int capacity() { return m_iMaxCount; }

	T& operator[] (int idx);

	//클래스안에 선언되어있을뿐 별개, 상위 클래스의 데이터를 가리킬 수 있게끔 구현 목적(시작주소+인덱스 필요)
	class iterator; //이너클래스 사용을 위한 전방선언
	iterator begin();
	iterator end();
	iterator erase(iterator& _iter);

public: //★생성자는 자동호출를 지원하기위해 퍼블릭에, 안만들어도 생성은 되지만 내용적어줄 것
	CArr();
	~CArr(); //실제구현은 구현부에
	//참고) 클래스 같은 경우는 헤더파일상에서 내부에 함수를 포함하더라도 중복문제 발생x

	//소속 클래스 안의 private에 이너클래스는 접근이 가능 	
	class iterator
	{
	private:
		CArr*	m_pArr;		//가변배열 자체의 주소
		T*		m_pData;	//메모리공간변경 이슈로 인해 크로스체크할거 아니면 따로 관리할 필요없음, 데이터들의 시작 주소
		int		m_iIdx;		//데이터의 인덱스
		bool	m_bValid;	//iterator의 유효성체크

	public:
		T& operator * ()	//주소를 가리키는 기능을 가진 오퍼레이터 연산자만들기
		{
			if (m_pArr->m_pData != m_pData || -1 == m_iIdx || false == m_bValid)
			{
				assert(nullptr); //메모리주소달라진경우 또는 배열에 아무 데이터가 없을때 오퍼레이터* 사용해서 가리키려고 하면 오류처리
			}
			
			return m_pData[m_iIdx]; //진짜 포인터(기본문법), 시작주소 포인터T*로부터 인덱스의 값
		}

		iterator& operator ++() //++전위연산
		{
			//1.end iterator 인 경우
			//2.데이터공간 주소 변경된 경우
			if (m_pArr->m_pData != m_pData || -1 == m_iIdx)
			{
				assert(nullptr);
			}

			//3.iterator가 마지막데이터를 가리키고 있는 경우는 ++전위연산을 허용하면 안됨(오류는x 예외처리)
			if (m_pArr->size()-1 == m_iIdx)
			{
				m_iIdx = -1;
			}
			else
			{
				++m_iIdx;
			}

			return *this;
		}

		//매개변수의 자료형을 int로 하면 후위연산, 매개변수가 없으면 전위연산으로 컴파일링 하는 것은 bjarne Stroustrup이 1979년 C++개발을 시작하며 ''임의''로 정한 문법임
		iterator operator ++(int) //후위연산++, 기본연산자가 아니기때문에 호출자체는 바로 되나 연산이 나중에 되도록 짜줘야함
		{
			iterator copy_iter = *this;

			++(*this);

			return copy_iter;
		}

		iterator& operator --() //--전위연산
		{
			//1.end iterator 인 경우
			//2.데이터공간 주소 변경된 경우
			if (m_pArr->m_pData != m_pData || -1 == m_iIdx)
			{
				assert(nullptr);
			}

			//3.iterator가 마지막데이터를 가리키고 있는 경우(오류는x 예외처리)
			if (0 == m_iIdx)
			{
				assert(nullptr);
			}
			else
			{
				--m_iIdx;
			}

			return *this;
		}

		iterator operator --(int) //후위연산--
		{
			iterator copy_iter = *this;

			--(*this);

			return copy_iter;
		}

		//비교연산자
		bool operator == (const iterator& _otheriter)
		{
			if (m_pData == _otheriter.m_pData && m_iIdx == _otheriter.m_iIdx) //m_pData 대신 m_pArr로 비교해도되긴함
			{
				return true;
			}

			return false;
	
		
		}
		
		bool operator != (const iterator& _otheriter)
		{
			/*if (m_pData == _otheriter.m_pData && m_iIdx == _otheriter.m_iIdx)
			{
				return false;
			}

			return true;*/
			//아래 한줄코드
			return !(*this == _otheriter);

		}


	public:
		iterator()
			:m_pArr(nullptr)
			,m_pData(nullptr)
			,m_iIdx(-1)
			,m_bValid(false)
		{

		}
		iterator(CArr* _pArr, T* _pData, int _iIdx)
			:m_pArr(_pArr)
			,m_pData(_pData)
			,m_iIdx(_iIdx)
			,m_bValid(false)
		{
			if (nullptr != _pArr && 0 <= _iIdx) //nullptr일때 iIdx = -1로 하기로 했으므로
			{
				m_bValid = true;
			}
		}

		~iterator()
		{

		}

		friend class CArr; //iterator가 Arr을 친구로 선언
		//이너클래스는 모클래스의 프라이빗에 접근가능하지만 그 역은 성립하지 않음, 친구선언필요
	};


};

template<typename T>
CArr<T>::CArr() //클래스 밖에서 구현시 다음과 같이 지정
	: m_pData(nullptr) //m_ 멤버
	, m_iCount(0)
	, m_iMaxCount(2) //초기화
{
	m_pData = new T[2];//C++의 동적할당 키워드

}

template<typename T>
CArr<T>::~CArr()
{
	delete[] m_pData; //C의 free대신 동적할당 해제, 자료형 여러개 삭제시 [] 추가

}


template<typename T>
void CArr<T>::push_back(const T& _iData) //this->는 전체적으로 생략이 가능
{
	//힙영역 공간 여유있는가?
	if (this->m_iMaxCount <= this->m_iCount)
	{
		//없으면 자동 재할당 처리
		resize(m_iMaxCount * 2);
	}

	//데이터추가
	this->m_pData[this->m_iCount++] = _iData; //힙메모리 주소관리자인 pInt의 끝부분에 저장하라는 주문

}

template<typename T>
void CArr<T>::resize(int _iResizeCount) //단독으로 호출할 경우
{
	//기존 메모리보다 작게는 안됨(C++추가)
	if (m_iMaxCount >= _iResizeCount)
	{
		assert(nullptr);//False인 경우 프로그램 중단 및 오류메시지 출력
	}

	//메모리공간 2배로 늘려주기
	//int* pNew = (int*)malloc(_pArr->iMaxCount * sizeof(int) * 2);
	T* pNew = new T[_iResizeCount];

	//기존 데이터를 새로운 공간으로 이동
	for (int i = 0; i < this->m_iCount; ++i)
	{
		pNew[i] = this->m_pData[i];
	}

	//기존 공간은 메모리 해제
	delete[] m_pData;

	//새로 확장된 배열로 pInt를 업데이트
	this->m_pData = pNew;

	//MaxCount변경점 적용
	this->m_iMaxCount = _iResizeCount;



}

template<typename T>
T& CArr<T>::operator[](int idx)
{
	return this->m_pData[idx];//int*는 애초에 주소연산

}

template<typename T>
typename CArr<T>::iterator CArr<T>::begin() //★타입네임중요
{
	//시작을 가리키는 iterator를 만들어서 변환해줌
	if (0 == m_iCount)
		return iterator(this, m_pData, -1);//배열안에 아무것도 없는데 begin을 가리키는 경우
	else
		return iterator(this, m_pData, 0);//this는 CArr포인터(메인객체)

}


template<typename T>
typename CArr<T>::iterator CArr<T>::end() //★타입네임중요
{
	//시작을 가리키는 iterator를 만들어서 변환해줌
	return iterator(this, m_pData, -1);

}

template<typename T>
typename CArr<T>::iterator CArr<T>::erase(iterator& _iter)
{
	//방어적인코드 iterator가 다른 Arr쪽 요소를 가리키는 경우
	if (this != _iter.m_pArr || end() == _iter || m_iCount <= _iter.m_iIdx)
	{
		assert(nullptr);
	}

	//iterator가 가리키는 데이터를 배열내에서 제거한다
	int iLoopCount = m_iCount - (_iter.m_iIdx + 1); //제거할 배열위치 _iter.m_iIdx, 제거하고 뒤에 남은 데이터갯수 iLoopCount
	for (int i = 0; i < iLoopCount; ++i)
	{
		m_pData[i + _iter.m_iIdx] = m_pData[i + _iter.m_iIdx + 1]; //제거한 배열위치를 다음 배열로 채우고, 그걸 iLoopCount번 반복(0 ~ iLoopCount-1번)
	}

	_iter.m_bValid = false; //한번 사용한 이터레이터는 예외처리(재사용금지), 이터레이터란 모든 자료구조에서 동일한 의미로 사용되어야함 .. 삭제된 주소는 사용될 수 없음이 상식
	--m_iCount;

	//return iterator(_iter);배열 자료구조에서는 이렇게 제자리로 돌아오기만 해도 충분하지만, 이터레이터는 모든 자료구조에서 범용적인 의미로 사용되어야하므로 삭제된 이터레이터는 사용될 수 없도록 예외처리필요★
	return iterator(this, m_pData, _iter.m_iIdx); //되돌려주게 되면 나머지는 같더라도 bValid값 true로 초기화됨

}