#pragma once
#include <Assert.h>


//struct�� ����Ʈ �������������ڰ� public, class�� private

template<typename T>
struct tListNode //����Ʈ�� Ŭ������ ���� ����ü��, C++���� ���� ���̴� ������ ���ӽ� ǥ���� ����� ���� ���� ��� ����ü��
{
//public:
	T				data;
	tListNode<T>*	pNext; //����
	tListNode*		pPrev; //���� �������� <T>��������

	tListNode() //�ʱ�ȭ�� ����
		: data()
		, pPrev(nullptr)
		, pNext(nullptr)
	{
	
	}

	tListNode(const T& _data, tListNode<T>* _pPrev, tListNode<T>* _pNext) //���ϴ� ������ �ٷ� �ʱ�ȭ �ϱ����� ���� �ϳ��� �����ε�
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
	int				m_iCount;//������ ���� ����

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
		tListNode<T>*	m_pNode; //null�� ��� end iterator�� ����
		bool			m_bValid;

	public:
		//�����Ϳ�����
		T& operator* ()
		{
			return m_pNode->data;
		}

		//�񱳿�����
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

		//�������� ������
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

		m_pTail = pNewNode; //���� �� ���� ��, ������ �ּҰ��� ���ο� ���� ����

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


//���ø��� �����ڸ� ������ٰ� �����ؾ���
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
	//��������ڵ�
	if (this != _iter.m_pList || end() == _iter || nullptr == _iter.m_pNode)
	{
		assert(nullptr);
	}

	tListNode<T>* pDeleteNode = _iter.m_pNode;
	tListNode<T>* pPrevNode = pDeleteNode->pPrev;
	tListNode<T>* pNextNode = pDeleteNode->pNext;

	if (nullptr != pPrevNode) //������ ���� �ִ�?
	{
		pPrevNode->pNext = pNextNode; //������ �� ���� ��带, ���� ����� �������� ����
	}
	else //ù ����
	{
		m_pHead = pNextNode; //������ �� ���� ��带, ����
	}

	if (nullptr != pNextNode) //������ ���� �ִ�?
	{
		pNextNode->pPrev = pPrevNode; //������ �� ���� ��带, ���� ����� �������� ����
	}
	else //������ ���� ����?
	{
		m_pTail = pPrevNode; //������ �� ���� ��带, ���Ϸ�
	}

	delete(pDeleteNode); //�����ϰ�
	--m_iCount; //���� �ϳ� ���̰�

	return iterator(this, pNextNode); //������ �������� ��Ī
}



//inline�� �ǹ� : ���ÿ������ ����ȭ ��û, ���� ���� �ʰ� ���ս��Ѽ� ��ť�� ����(������� ���ٿ���ó��), �����Ϸ��� �ʹ� ��� ������ ������ ������ ����

template<typename T>
inline typename CList<T>::iterator CList<T>::insert(const iterator& _iter, const T& _data)
{
	if (end() == _iter)
	{
		assert(nullptr);
	}

	//����Ʈ�� �߰��� �����͸� ������ Node����
	tListNode<T>* pNode = new tListNode<T>(_data, nullptr, nullptr);

	//������?
	if (_iter.m_pNode == m_pHead)
	{
		_iter.m_pNode->pPrev = pNode;
		pNode->pNext = _iter.m_pNode;

		m_pHead = pNode;
	}
	else //���ƴϸ�
	{
		_iter.m_pNode->pPrev->pNext = pNode;
		pNode->pPrev = _iter.m_pNode->pPrev;

		_iter.m_pNode->pPrev = pNode;
		pNode->pNext = _iter.m_pNode;
	
	}

	++m_iCount; //��¶�ų� data������ ���������Ƿ�

	return iterator(this, pNode);
}
