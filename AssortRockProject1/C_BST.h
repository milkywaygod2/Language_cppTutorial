#pragma once
#include <assert.h>


enum class NODE_TYPE
{
	PARENT,	//0
	LCHILD, //1
	RCHILD, //2
	END,	//3
};

template<typename T1, typename T2>
struct tPair
{
	T1 first;
	T2 second;
};

template<typename T1, typename T2>
struct tBST_Node
{
	tPair<T1, T2>	pair;
	tBST_Node* arrNode[(int)NODE_TYPE::END]; //arrNode[3]
	/* ����
	//tBST_Node*	arrNode[];
	tBST_Node*		pPrt;		//Parent
	tBST_Node*		pLC;		//LeftChild
	tBST_Node*		pRC;		//RightChild
	*/

	//------------------------------------------------------------------------������ȸ�� ���� �ΰ���ɱ���
	bool IsRoot()
	{
		if (nullptr == arrNode[(int)NODE_TYPE::PARENT])
			return true;
		return false;
	}

	bool IsLeftChild()
	{
		if (arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] == this)
		{
			return true;
		}return false;
	}

	bool IsRightChild()
	{
		if (arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::RCHILD] == this)
		{
			return true;
		}return false;
	}

	bool IsLeaf() //�ܸ����?
	{
		if (nullptr == arrNode[(int)NODE_TYPE::LCHILD] && nullptr == arrNode[(int)NODE_TYPE::RCHILD])
			return true;
		return false;
	}

	bool IsFull() //�ڽ� ��?
	{
		if (arrNode[(int)NODE_TYPE::LCHILD] && arrNode[(int)NODE_TYPE::RCHILD])
			return true;
		return false;
	}

	//------------------------------------------------------------------------������ȸ�� ���� �ΰ���ɱ���_��

	tBST_Node()
		: pair()
		, arrNode{}
	{}

	tBST_Node(const tPair<T1, T2>& _pair, tBST_Node* _pPrt, tBST_Node* _pLC, tBST_Node* _pRC)
		: pair(_pair)
		, arrNode{ _pPrt, _pRC, _pLC }
	{}
};
//��---- C_BST�� ������� ----
// ===========================================================
//��---- C_BST class ������ ----
template<typename T1, typename T2>
class C_BST
{
private:
	tBST_Node<T1, T2>*		m_pRoot;	//��Ʈ����ּ�
	int						m_iCount;	//�����Ͱ���

public:
	bool insert(const tPair<T1, T2>& _pair);
	tBST_Node<T1, T2>* GetInOrderSuccessor(tBST_Node<T1, T2>* _pNode);
	tBST_Node<T1, T2>* GetInOrderPredecessor(tBST_Node<T1, T2>* _pNode);


	class iterator;

public:
	iterator begin();
	iterator end();
	iterator find(const T1& _find);
	iterator erase(const iterator& _iter);

private: //�����˻�Ʈ�� ���� ���� ����
	tBST_Node<T1, T2>* DeleteNode(tBST_Node<T1, T2>* _pTargetNode);

public:
	C_BST()
		: m_pRoot(nullptr)
		, m_iCount(0)
	{

	}

	//iterator---------------------------------���ͷ����� �� ������ ����
	class iterator
	{
	private:
		C_BST<T1, T2>*		m_pBST;
		tBST_Node<T1, T2>*	m_pNode; //null�� ���, end iterator�� ����

	public:
		bool operator ==(const iterator& _other)
		{
			if (m_pBST == _other.m_pBST && m_pNode == _other.m_pNode)
				return true;

			return false;
		}
		bool operator != (const iterator& _other)
		{
			return !(*this == _other);

		}

		const tPair<T1, T2>& operator *() //���⼭*�� ...������ �� ��� ��ü�� ��Ī&
		{
			//m_pNode nullptr üũ(end iterator���� �ƴ���)
			assert(m_pNode);
			return m_pNode->pair;
		}

		const tPair<T1, T2>* operator ->() //���⼭->�� ...�� ����� �ּҸ� ��Ī*
		{
			//m_pNode nullptr üũ(end iterator���� �ƴ���)
			assert(m_pNode);
			return &m_pNode->pair;
		}

		iterator& operator ++() //������ȸ, ����������(inorder predecessor) �����ļ���(inorder successor)
		{
			m_pNode = m_pBST->GetInOrderSuccessor(m_pNode);
			return *this;		
		
		}

		iterator& operator --() //������ȸ, ����������(inorder predecessor) �����ļ���(inorder successor)
		{
			m_pNode = m_pBST->GetInOrderPredecessor(m_pNode);
			return *this;

		}

		iterator& operator ++(int) //������ȸ, ����������(inorder predecessor) �����ļ���(inorder successor)
		{
			m_pNode = m_pBST->GetInOrderSuccessor(m_pNode);
			return *this;

		}

		iterator& operator --(int) //������ȸ, ����������(inorder predecessor) �����ļ���(inorder successor)
		{
			m_pNode = m_pBST->GetInOrderPredecessor(m_pNode);
			return *this;

		}


	public:
		iterator()
			: m_pBST(nullptr)
			, m_pNode(nullptr)
		{}
		 
		iterator(C_BST<T1, T2>* _pBST, tBST_Node<T1, T2>* _pNode)
			: m_pBST(_pBST)
			, m_pNode(_pNode)
		{}
		
		friend class C_BST<T1, T2>;
	};

};

//----------------------------------------------------------------------------��� ������ ((�Լ�))

template<typename T1, typename T2>
tPair<T1, T2> make_bstpair(const T1& _first, const T2& _second) //�������Լ�
{
	return tPair<T1, T2>{_first, _second};
}


template<typename T1, typename T2>
inline bool C_BST<T1, T2>::insert(const tPair<T1, T2>& _pair)
{
	tBST_Node<T1,T2>* pNewNode = new tBST_Node<T1, T2>(_pair, nullptr, nullptr, nullptr);

	if (nullptr == m_pRoot)
	{
		m_pRoot = pNewNode;
	}
	else
	{
		tBST_Node<T1, T2>* pNode = m_pRoot;//��Ʈ��ü�� �ٲٸ� �ȵǴϱ� ����
		NODE_TYPE node_type = NODE_TYPE::END;
		
		
		while (true)
		{
			//������ ���������ְ�
			if (pNode->pair.first < pNewNode->pair.first)
			{
				node_type = NODE_TYPE::RCHILD;
			}
			else if (pNode->pair.first > pNewNode->pair.first)
			{
				node_type = NODE_TYPE::LCHILD;
			}
			else
			{
				return false;
			}

			//�� ������ ������ �ؼ�, �ش� ���⿡ ������ �ٽ� while������ �Ǵ�
			if (nullptr == pNode->arrNode[(int)node_type])
			{
				pNode->arrNode[(int)node_type] = pNewNode;			//�ش���⿡ �ڽ����� �ְ�
				pNewNode->arrNode[(int)NODE_TYPE::PARENT] = pNode;	//�ش� �ڽ��� �θ� ��������
				break;
			}
			else
			{
				pNode = pNode->arrNode[(int)node_type];		//�̹� �ڽ�����, �� �ڽ��� pNode�� �����ؼ� �ٽ� ��(while)
			}	
		
		}
	}

	++m_iCount;

	return true;

}

template<typename T1, typename T2>
inline tBST_Node<T1, T2>* C_BST<T1, T2>::GetInOrderSuccessor(tBST_Node<T1, T2>* _pNode) //�����ļ���
{
	tBST_Node<T1, T2>* pSuccessor = nullptr;

	//1.������ �ڽ��� �ִ� ���, ������ �ڽ����ΰ���, ���� �ڽ��� ���������� ������
	if (nullptr != _pNode->arrNode[(int)NODE_TYPE::RCHILD])
	{
		pSuccessor = _pNode->arrNode[(int)NODE_TYPE::RCHILD];

		while (pSuccessor->arrNode[(int)NODE_TYPE::LCHILD])
		{
			pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::LCHILD];

		}
	}
	
	//2.������ �ڽ��� ���� ���, ��λ��� �θ���, ���� �ڽ����� ���� '�θ�'���� �ö�
	else
	{
		pSuccessor = _pNode;

		while (true)
		{
			//���̻� �ö� �� ���� == ���������
			if (pSuccessor->IsRoot())
				return nullptr; //end iterator

			//�θ�κ��� �����ڽ��ΰ�?
			if (pSuccessor->IsLeftChild())
			{
				//�׶� �θ� �����ļ��ڷ� ����
				pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::PARENT];
				break;
			}
			else
			{
				pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::PARENT];
			}

		}
		//pSuccessor->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] == pSuccessor;�ʹ� ��Ȳ�ϴ� ���ʿ� �Լ��� ����
	}


	return pSuccessor;
}

template<typename T1, typename T2>
inline tBST_Node<T1, T2>* C_BST<T1, T2>::GetInOrderPredecessor(tBST_Node<T1, T2>* _pNode) //���������� (�ļ��ڿ� ��Ī)
{
	tBST_Node<T1, T2>* pSuccessor = nullptr;

	//1.���� �ڽ��� �ִ� ���, ���� �ڽ����ΰ���, ������ �ڽ��� ���������� ������
	if (nullptr != _pNode->arrNode[(int)NODE_TYPE::LCHILD])
	{
		pSuccessor = _pNode->arrNode[(int)NODE_TYPE::LCHILD];

		while (pSuccessor->arrNode[(int)NODE_TYPE::RCHILD])
		{
			pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::RCHILD];

		}
	}
	
	//2.���� �ڽ��� ���� ���, ��λ��� �ڽ��� ������ �ڽ����� ���� '�θ�'���� �ö�
	else
	{
		pSuccessor = _pNode;

		while (true)
		{
			//���̻� �ö� �� ���� == ���������
			if (pSuccessor->IsRoot())
				return nullptr; //end iterator

			//�θ�κ��� �����ڽ��ΰ�?
			if (pSuccessor->IsRightChild())
			{
				//�׶� �θ� �����ļ��ڷ� ����
				pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::PARENT];
				break;
			}
			else
			{
				pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::PARENT];
			}

		}
		//pSuccessor->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] == pSuccessor;�ʹ� ��Ȳ�ϴ� ���ʿ� �Լ��� ����
	}


	return pSuccessor;
}

template<typename T1, typename T2>
inline typename C_BST<T1,T2>::iterator C_BST<T1, T2>::begin()
{
	tBST_Node<T1,T2>* pNode = m_pRoot;

	while (pNode->arrNode[(int)NODE_TYPE::LCHILD]) //���� ������ true, nullptr�� 0 �� false
	{
		pNode = pNode->arrNode[(int)NODE_TYPE::LCHILD];
	}

	return iterator(this, pNode);
}

template<typename T1, typename T2>
inline typename C_BST<T1, T2>::iterator C_BST<T1, T2>::end()
{
	return iterator(this, nullptr); //end�� ������ ���� �ƴ϶� �״��� nullptr ����
}

template<typename T1, typename T2>
inline typename C_BST<T1, T2>::iterator C_BST<T1, T2>::find(const T1& _find)
{
	tBST_Node<T1, T2>* pNode = m_pRoot;//��Ʈ��ü�� �ٲٸ� �ȵǴϱ� ����
	NODE_TYPE node_type = NODE_TYPE::END;//�ʱ�ȭ


	while (true)
	{
		//������ ���������ְ�
		if (pNode->pair.first < _find) //�Ѵ� T1 Ÿ�� �񱳿��갡��
		{
			node_type = NODE_TYPE::RCHILD;
		}
		else if (pNode->pair.first > _find)
		{
			node_type = NODE_TYPE::LCHILD;
		}
		else //ã��!
		{
			break;
		}

		//�� ã��
		if (nullptr == pNode->arrNode[(int)node_type])
		{
			pNode = nullptr; // iterator end()�� �ǹ�
			break;
		}
		else
		{
			pNode = pNode->arrNode[(int)node_type];		//���� �ڽ��� pNode�� �����ؼ� �ٽ� ��(while)
		}
	}
	return iterator(this, pNode);
}


//�������˻�Ʈ�� ������� :::: �����

	//0.(����) ��������� �ļ���, ��ȯ�� ���� �������� �����ص�
	// 
	//1.��������� �ڽ��� �ϳ��� ���� ���
	//	1-1 ����� Root�� Root�� nullptr��ȯ => 1-4
	//	1-2 ����� ��/�� ����� �ڽ����� Ȯ��
	//  1-3 �θ�� ����, �ش� ���� �ڽİ��踦 ����
	//  1-4 ��� ��� ����
	// 
	//
	//2.��������� �ڽ��� ���� ��� ((������� ����� �ڽ��� 2�̰� �� ���ڰ� 2��, ���θ��� �����ļ��ڴ� ����. �ڽ�2����1�� �ִ�))
	//  2-1 �����ڸ� ������� ���� (�����ڷ� ¥�� ����)
	//  2-2 ������ ��� ���� + ������ �ߺ� ���ҵǴ� iCount���� (DeleteNode, 2��° ����� ������1,3���� �ɸ� 2 & 2 �������� ����x)
	//	2-3 _pTargetNode�� �����ص� �������� ���� pSuccessor ��ȯ������ ����
	//
	//3.��������� �ڽ��� �ϳ��� ���(else)
	//  3-1 ����� �ڽ��� ��/�� ���� ����(eChildType)
	//  3-2 ����� Root�� Root�� �ڽ��� ���� + �ڽ��� �θ� nullptr�� => 3-6
	//	3-3 ����� ��/�� ����� �ڽ����� Ȯ��
	//  3-4 �θ�� ����, �ش� ���� �ڽİ��踦 ���ڿ� ����
	//  3-5 ������ �θ� ���θ�� ����
	//	3-6 ��� ��� ����
	// 
	//4.iCount����+�ļ��ڹ�ȯ
	//

template<typename T1, typename T2>
inline typename C_BST<T1, T2>::iterator C_BST<T1, T2>::erase(const iterator& _iter)
{
	assert(this == _iter.m_pBST); //���������� ������ �� false�� ��������, m_pBST ==> �̳�Ŭ������ iterator�� private member�� ������ C_BST���� �����Ұ� (ģ���߰��ʿ�)

	tBST_Node<T1, T2>* pSuccessor = DeleteNode(_iter.m_pNode);
	
	return iterator(this, pSuccessor);
}

template<typename T1, typename T2>
inline tBST_Node<T1, T2>* C_BST<T1, T2>::DeleteNode(tBST_Node<T1, T2>* _pTargetNode)
{
	tBST_Node<T1, T2>* pSuccessor = GetInOrderSuccessor(_pTargetNode); // 0

	if (_pTargetNode->IsLeaf()) // 1
	{
		if (_pTargetNode == m_pRoot) // 1-1
		{
			m_pRoot = nullptr;
		}
		else
		{
			if (_pTargetNode->IsLeftChild()) // 1-2
			{
				_pTargetNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] = nullptr; // 1-3
			}
			else
			{
				_pTargetNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::RCHILD] = nullptr; // 1-3
			}
		}


		delete _pTargetNode; // 1-4

	}
	else if (_pTargetNode->IsFull()) // 2
	{
		_pTargetNode->pair = pSuccessor->pair; // 2-1

		DeleteNode(pSuccessor); // 2-2
		++m_iCount; // 2-2

		pSuccessor = _pTargetNode; // 2-3
		//??��������� ��Ʈ�̰� ��������� �ڽ��� �ڽ��� ���� ���, ��Ʈ->������ ���� ���� �����൵��??
	}
	else // 3
	{
		NODE_TYPE eChildType = NODE_TYPE::LCHILD;
		if (_pTargetNode->arrNode[(int)NODE_TYPE::RCHILD]) // 3-1
			eChildType = NODE_TYPE::RCHILD;

		if (_pTargetNode == m_pRoot) // 3-2
		{
			m_pRoot = _pTargetNode->arrNode[(int)eChildType];
			_pTargetNode->arrNode[(int)eChildType]->arrNode[(int)NODE_TYPE::PARENT] = nullptr;
		}
		else
		{
			if (_pTargetNode->IsLeftChild()) // 3-3
			{
				_pTargetNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] = _pTargetNode->arrNode[(int)eChildType]; // 3-4
			}
			else
			{
				_pTargetNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::RCHILD] = _pTargetNode->arrNode[(int)eChildType]; // 3-4
			}

			_pTargetNode->arrNode[(int)eChildType]->arrNode[(int)NODE_TYPE::PARENT] = _pTargetNode->arrNode[(int)NODE_TYPE::PARENT]; // 3-5

		}

		delete _pTargetNode; // 3-6

	}

	--m_iCount; // 4

	return pSuccessor; // 4
}
