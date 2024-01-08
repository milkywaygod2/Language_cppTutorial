#pragma once
#include <Assert.h>


//struct는 디폴트 범위지정연산자가 public, class는 private

template<typename T>
struct tListNode //리스트는 클래스로 노드는 구조체로, C++기준 둘의 차이는 없으나 뉘앙스 표현상 기능이 많지 않은 경우 구조체로
{
//public:
	T				data;
	tListNode<T>*	pNext; //정석
	tListNode*		pPrev; //본인 내에서는 <T>생략가능

	tListNode() //초기화용 선언문
		: data()
		, pPrev(nullptr)
		, pNext(nullptr)
	{
	
	}

	tListNode(const T& _data, tListNode<T>* _pPrev, tListNode<T>* _pNext) //원하는 값으로 바로 초기화 하기위해 선언문 하나더 오버로딩
		: data(_data)
		, pPrev(_pPrev)
		, pNext(_pNext)
	{

	}

};

template<typename T>
class CList
{
//private:
	tListNode<T>*	m_pHead;
	tListNode<T>*	m_pTail; 
	int				m_iCount;//데이터 개수 관리

public:
	void push_back(const T& _data);
	void push_front(const T& _data);
	int size() { return m_iCount; }

public:
	class iterator;
	iterator begin();
	iterator end();
	iterator erase(iterator& _iter);
	iterator insert(const iterator& _iter, const T& _data);



public:
	CList();
	~CList();

	class iterator
	{
	private:
		CList*			m_pList;
		tListNode<T>*	m_pNode; //null인 경우 end iterator로 간주
		bool			m_bValid;

	public:
		//포인터연산자
		T& operator* ()
		{
			return m_pNode->data;
		}

		//비교연산자
		bool operator ==(const iterator& _otheriter)
		{
			if (m_pList == _otheriter.m_pList && m_pNode == _otheriter.m_pNode)
			{
				return true;
			}
			return false;
		}

		bool operator !=(const iterator& _otheriter)
		{
			return !(*this == _otheriter);
		}

		//전위후위 연산자
		iterator& operator ++()
		{
			if (nullptr == m_pNode || !m_bValid)
			{
				assert(nullptr);
			}
			m_pNode = m_pNode->pNext;
			return *this;
		}

		iterator operator ++(int)
		{
			iterator copyiter(*this);
			++(*this);
			return copyiter;
		}

		iterator& operator --()
		{
			if (nullptr == m_pNode || !m_bValid)
			{
				assert(nullptr);
			}
			m_pNode = m_pNode->pPrev;
			return *this;
		}

		iterator operator --(int)
		{
			iterator copyiter(*this);
			--(*this);
			return copyiter;
		}


	public:
		iterator()
			: m_pList(nullptr)
			, m_pNode(nullptr)
			, m_bValid(false)
		{}

		iterator(CList<T>* _pList, tListNode<T>* _pNode)
			: m_pList(_pList)
			, m_pNode(_pNode)
			, m_bValid(false)
		{
			if (nullptr != _pList && nullptr != _pNode)
			{
				m_bValid = true;
			}
		}

		friend class CList;
	};
};


template<typename T>
void CList<T>::push_back(const T& _data)
{
	tListNode<T>* pNewNode = new tListNode<T>(_data, nullptr, nullptr);
	if (nullptr == m_pHead)
	{
		m_pHead = pNewNode;
		m_pTail = pNewNode;
	}
	else
	{
		m_pTail->pNext = pNewNode;
		pNewNode->pPrev = m_pTail;

		m_pTail = pNewNode; //물릴 것 물린 후, 마지막 주소값을 새로운 노드로 갱신

	}
	++m_iCount;
	  
}

template<typename T>
void CList<T>::push_front(const T& _data)
{
	tListNode<T>* pNewNode = new tListNode<T>(_data, nullptr, m_pHead);
	m_pHead->pPrev = pNewNode;

	m_pHead = pNewNode;

	++m_iCount;
}


//탬플릿은 생성자를 헤더에다가 선언해야함
template<typename T>
CList<T>::CList()
	: m_pHead(nullptr)
	, m_pTail(nullptr)
	, m_iCount(0)
{

}

template<typename T>
CList<T>::~CList()
{
	tListNode<T>* pDeletNode = m_pHead;

	while (pDeletNode)
	{
		tListNode<T>* pNext = pDeletNode->pNext;
		delete(pDeletNode);
		pDeletNode = pNext;
	}
}

template<typename T>
inline typename CList<T>::iterator CList<T>::begin()
{
	return iterator(this ,m_pHead );
}

template<typename T>
inline typename CList<T>::iterator CList<T>::end()
{
	return iterator(this, nullptr);
}


template<typename T>
inline typename CList<T>::iterator CList<T>::erase(iterator& _iter)
{
	//방어적인코드
	if (this != _iter.m_pList || end() == _iter || nullptr == _iter.m_pNode)
	{
		assert(nullptr);
	}

	tListNode<T>* pDeleteNode = _iter.m_pNode;
	tListNode<T>* pPrevNode = pDeleteNode->pPrev;
	tListNode<T>* pNextNode = pDeleteNode->pNext;

	if (nullptr != pPrevNode) //이전에 뭐가 있다?
	{
		pPrevNode->pNext = pNextNode; //삭제할 것 다음 노드를, 이전 노드의 다음으로 연결
	}
	else //첫 노드다
	{
		m_pHead = pNextNode; //삭제할 것 다음 노드를, 헤드로
	}

	if (nullptr != pNextNode) //다음에 뭐가 있다?
	{
		pNextNode->pPrev = pPrevNode; //삭제할 것 이전 노드를, 다음 노드의 이전으로 연결
	}
	else //다음에 뭐가 없다?
	{
		m_pTail = pPrevNode; //삭제할 것 이전 노드를, 테일로
	}

	delete(pDeleteNode); //삭제하고
	--m_iCount; //갯수 하나 줄이고

	return iterator(this, pNextNode); //삭제한 다음것을 지칭
}



//inline의 의미 : 스택연산시의 최적화 요청, 스택 쌓지 않고 통합시켜서 한큐에 연산(헤더같이 복붙연산처리), 컴파일러가 너무 길다 싶으면 무조건 해주진 않음

template<typename T>
inline typename CList<T>::iterator CList<T>::insert(const iterator& _iter, const T& _data)
{
	if (end() == _iter)
	{
		assert(nullptr);
	}

	//리스트에 추가할 데이터를 저장할 Node생성
	tListNode<T>* pNode = new tListNode<T>(_data, nullptr, nullptr);

	//헤드노드면?
	if (_iter.m_pNode == m_pHead)
	{
		_iter.m_pNode->pPrev = pNode;
		pNode->pNext = _iter.m_pNode;

		m_pHead = pNode;
	}
	else //헤드아니면
	{
		_iter.m_pNode->pPrev->pNext = pNode;
		pNode->pPrev = _iter.m_pNode->pPrev;

		_iter.m_pNode->pPrev = pNode;
		pNode->pNext = _iter.m_pNode;
	
	}

	++m_iCount; //어쨋거나 data갯수는 증가했으므로

	return iterator(this, pNode);
}
