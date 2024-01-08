#pragma once

#include <Assert.h>


template<typename T>
class CArr 
{
private: //�ƹ��͵� ���� ������ private�� ����Ʈ

	T*		m_pData;	//8����Ʈ
	int		m_iCount;	//4����Ʈ
	int		m_iMaxCount;//4����Ʈ
	

public:
	void push_back(const T& _iData);
	void resize(int _iResizeCount);
	T* data() { return m_pData; }
	int size() { return m_iCount; }
	int capacity() { return m_iMaxCount; }

	T& operator[] (int idx);

	//Ŭ�����ȿ� ����Ǿ������� ����, ���� Ŭ������ �����͸� ����ų �� �ְԲ� ���� ����(�����ּ�+�ε��� �ʿ�)
	class iterator; //�̳�Ŭ���� ����� ���� ���漱��
	iterator begin();
	iterator end();
	iterator erase(iterator& _iter);

public: //�ڻ����ڴ� �ڵ�ȣ�⸦ �����ϱ����� �ۺ���, �ȸ��� ������ ������ ���������� ��
	CArr();
	~CArr(); //���������� �����ο�
	//����) Ŭ���� ���� ���� ������ϻ󿡼� ���ο� �Լ��� �����ϴ��� �ߺ����� �߻�x

	//�Ҽ� Ŭ���� ���� private�� �̳�Ŭ������ ������ ���� 	
	class iterator
	{
	private:
		CArr*	m_pArr;		//�����迭 ��ü�� �ּ�
		T*		m_pData;	//�޸𸮰������� �̽��� ���� ũ�ν�üũ�Ұ� �ƴϸ� ���� ������ �ʿ����, �����͵��� ���� �ּ�
		int		m_iIdx;		//�������� �ε���
		bool	m_bValid;	//iterator�� ��ȿ��üũ

	public:
		T& operator * ()	//�ּҸ� ����Ű�� ����� ���� ���۷����� �����ڸ����
		{
			if (m_pArr->m_pData != m_pData || -1 == m_iIdx || false == m_bValid)
			{
				assert(nullptr); //�޸��ּҴ޶������ �Ǵ� �迭�� �ƹ� �����Ͱ� ������ ���۷�����* ����ؼ� ����Ű���� �ϸ� ����ó��
			}
			
			return m_pData[m_iIdx]; //��¥ ������(�⺻����), �����ּ� ������T*�κ��� �ε����� ��
		}

		iterator& operator ++() //++��������
		{
			//1.end iterator �� ���
			//2.�����Ͱ��� �ּ� ����� ���
			if (m_pArr->m_pData != m_pData || -1 == m_iIdx)
			{
				assert(nullptr);
			}

			//3.iterator�� �����������͸� ����Ű�� �ִ� ���� ++���������� ����ϸ� �ȵ�(������x ����ó��)
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

		//�Ű������� �ڷ����� int�� �ϸ� ��������, �Ű������� ������ ������������ �����ϸ� �ϴ� ���� bjarne Stroustrup�� 1979�� C++������ �����ϸ� ''����''�� ���� ������
		iterator operator ++(int) //��������++, �⺻�����ڰ� �ƴϱ⶧���� ȣ����ü�� �ٷ� �ǳ� ������ ���߿� �ǵ��� ¥�����
		{
			iterator copy_iter = *this;

			++(*this);

			return copy_iter;
		}

		iterator& operator --() //--��������
		{
			//1.end iterator �� ���
			//2.�����Ͱ��� �ּ� ����� ���
			if (m_pArr->m_pData != m_pData || -1 == m_iIdx)
			{
				assert(nullptr);
			}

			//3.iterator�� �����������͸� ����Ű�� �ִ� ���(������x ����ó��)
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

		iterator operator --(int) //��������--
		{
			iterator copy_iter = *this;

			--(*this);

			return copy_iter;
		}

		//�񱳿�����
		bool operator == (const iterator& _otheriter)
		{
			if (m_pData == _otheriter.m_pData && m_iIdx == _otheriter.m_iIdx) //m_pData ��� m_pArr�� ���ص��Ǳ���
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
			//�Ʒ� �����ڵ�
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
			if (nullptr != _pArr && 0 <= _iIdx) //nullptr�϶� iIdx = -1�� �ϱ�� �����Ƿ�
			{
				m_bValid = true;
			}
		}

		~iterator()
		{

		}

		friend class CArr; //iterator�� Arr�� ģ���� ����
		//�̳�Ŭ������ ��Ŭ������ �����̺��� ���ٰ��������� �� ���� �������� ����, ģ�������ʿ�
	};


};

template<typename T>
CArr<T>::CArr() //Ŭ���� �ۿ��� ������ ������ ���� ����
	: m_pData(nullptr) //m_ ���
	, m_iCount(0)
	, m_iMaxCount(2) //�ʱ�ȭ
{
	m_pData = new T[2];//C++�� �����Ҵ� Ű����

}

template<typename T>
CArr<T>::~CArr()
{
	delete[] m_pData; //C�� free��� �����Ҵ� ����, �ڷ��� ������ ������ [] �߰�

}


template<typename T>
void CArr<T>::push_back(const T& _iData) //this->�� ��ü������ ������ ����
{
	//������ ���� �����ִ°�?
	if (this->m_iMaxCount <= this->m_iCount)
	{
		//������ �ڵ� ���Ҵ� ó��
		resize(m_iMaxCount * 2);
	}

	//�������߰�
	this->m_pData[this->m_iCount++] = _iData; //���޸� �ּҰ������� pInt�� ���κп� �����϶�� �ֹ�

}

template<typename T>
void CArr<T>::resize(int _iResizeCount) //�ܵ����� ȣ���� ���
{
	//���� �޸𸮺��� �۰Դ� �ȵ�(C++�߰�)
	if (m_iMaxCount >= _iResizeCount)
	{
		assert(nullptr);//False�� ��� ���α׷� �ߴ� �� �����޽��� ���
	}

	//�޸𸮰��� 2��� �÷��ֱ�
	//int* pNew = (int*)malloc(_pArr->iMaxCount * sizeof(int) * 2);
	T* pNew = new T[_iResizeCount];

	//���� �����͸� ���ο� �������� �̵�
	for (int i = 0; i < this->m_iCount; ++i)
	{
		pNew[i] = this->m_pData[i];
	}

	//���� ������ �޸� ����
	delete[] m_pData;

	//���� Ȯ��� �迭�� pInt�� ������Ʈ
	this->m_pData = pNew;

	//MaxCount������ ����
	this->m_iMaxCount = _iResizeCount;



}

template<typename T>
T& CArr<T>::operator[](int idx)
{
	return this->m_pData[idx];//int*�� ���ʿ� �ּҿ���

}

template<typename T>
typename CArr<T>::iterator CArr<T>::begin() //��Ÿ�Գ����߿�
{
	//������ ����Ű�� iterator�� ���� ��ȯ����
	if (0 == m_iCount)
		return iterator(this, m_pData, -1);//�迭�ȿ� �ƹ��͵� ���µ� begin�� ����Ű�� ���
	else
		return iterator(this, m_pData, 0);//this�� CArr������(���ΰ�ü)

}


template<typename T>
typename CArr<T>::iterator CArr<T>::end() //��Ÿ�Գ����߿�
{
	//������ ����Ű�� iterator�� ���� ��ȯ����
	return iterator(this, m_pData, -1);

}

template<typename T>
typename CArr<T>::iterator CArr<T>::erase(iterator& _iter)
{
	//��������ڵ� iterator�� �ٸ� Arr�� ��Ҹ� ����Ű�� ���
	if (this != _iter.m_pArr || end() == _iter || m_iCount <= _iter.m_iIdx)
	{
		assert(nullptr);
	}

	//iterator�� ����Ű�� �����͸� �迭������ �����Ѵ�
	int iLoopCount = m_iCount - (_iter.m_iIdx + 1); //������ �迭��ġ _iter.m_iIdx, �����ϰ� �ڿ� ���� �����Ͱ��� iLoopCount
	for (int i = 0; i < iLoopCount; ++i)
	{
		m_pData[i + _iter.m_iIdx] = m_pData[i + _iter.m_iIdx + 1]; //������ �迭��ġ�� ���� �迭�� ä���, �װ� iLoopCount�� �ݺ�(0 ~ iLoopCount-1��)
	}

	_iter.m_bValid = false; //�ѹ� ����� ���ͷ����ʹ� ����ó��(�������), ���ͷ����Ͷ� ��� �ڷᱸ������ ������ �ǹ̷� ���Ǿ���� .. ������ �ּҴ� ���� �� ������ ���
	--m_iCount;

	//return iterator(_iter);�迭 �ڷᱸ�������� �̷��� ���ڸ��� ���ƿ��⸸ �ص� ���������, ���ͷ����ʹ� ��� �ڷᱸ������ �������� �ǹ̷� ���Ǿ���ϹǷ� ������ ���ͷ����ʹ� ���� �� ������ ����ó���ʿ��
	return iterator(this, m_pData, _iter.m_iIdx); //�ǵ����ְ� �Ǹ� �������� ������ bValid�� true�� �ʱ�ȭ��

}