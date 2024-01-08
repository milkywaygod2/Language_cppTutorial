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
	/* 통합
	//tBST_Node*	arrNode[];
	tBST_Node*		pPrt;		//Parent
	tBST_Node*		pLC;		//LeftChild
	tBST_Node*		pRC;		//RightChild
	*/

	//------------------------------------------------------------------------중위선회를 위한 부가기능구현
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

	bool IsLeaf() //단말노드?
	{
		if (nullptr == arrNode[(int)NODE_TYPE::LCHILD] && nullptr == arrNode[(int)NODE_TYPE::RCHILD])
			return true;
		return false;
	}

	bool IsFull() //자식 둘?
	{
		if (arrNode[(int)NODE_TYPE::LCHILD] && arrNode[(int)NODE_TYPE::RCHILD])
			return true;
		return false;
	}

	//------------------------------------------------------------------------중위선회를 위한 부가기능구현_끝

	tBST_Node()
		: pair()
		, arrNode{}
	{}

	tBST_Node(const tPair<T1, T2>& _pair, tBST_Node* _pPrt, tBST_Node* _pLC, tBST_Node* _pRC)
		: pair(_pair)
		, arrNode{ _pPrt, _pRC, _pLC }
	{}
};
//↑---- C_BST의 구성요소 ----
// ===========================================================
//↓---- C_BST class 구현부 ----
template<typename T1, typename T2>
class C_BST
{
private:
	tBST_Node<T1, T2>*		m_pRoot;	//루트노드주소
	int						m_iCount;	//데이터갯수

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

private: //이진검색트리 삭제 과정 보조
	tBST_Node<T1, T2>* DeleteNode(tBST_Node<T1, T2>* _pTargetNode);

public:
	C_BST()
		: m_pRoot(nullptr)
		, m_iCount(0)
	{

	}

	//iterator---------------------------------이터레이터 및 연산자 구현
	class iterator
	{
	private:
		C_BST<T1, T2>*		m_pBST;
		tBST_Node<T1, T2>*	m_pNode; //null인 경우, end iterator로 간주

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

		const tPair<T1, T2>& operator *() //여기서*은 ...역참조 그 대상 자체를 지칭&
		{
			//m_pNode nullptr 체크(end iterator인지 아닌지)
			assert(m_pNode);
			return m_pNode->pair;
		}

		const tPair<T1, T2>* operator ->() //여기서->은 ...그 대상의 주소만 지칭*
		{
			//m_pNode nullptr 체크(end iterator인지 아닌지)
			assert(m_pNode);
			return &m_pNode->pair;
		}

		iterator& operator ++() //중위순회, 중위선행자(inorder predecessor) 중위후속자(inorder successor)
		{
			m_pNode = m_pBST->GetInOrderSuccessor(m_pNode);
			return *this;		
		
		}

		iterator& operator --() //중위순회, 중위선행자(inorder predecessor) 중위후속자(inorder successor)
		{
			m_pNode = m_pBST->GetInOrderPredecessor(m_pNode);
			return *this;

		}

		iterator& operator ++(int) //중위순회, 중위선행자(inorder predecessor) 중위후속자(inorder successor)
		{
			m_pNode = m_pBST->GetInOrderSuccessor(m_pNode);
			return *this;

		}

		iterator& operator --(int) //중위순회, 중위선행자(inorder predecessor) 중위후속자(inorder successor)
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

//----------------------------------------------------------------------------기능 구현부 ((함수))

template<typename T1, typename T2>
tPair<T1, T2> make_bstpair(const T1& _first, const T2& _second) //페어생성함수
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
		tBST_Node<T1, T2>* pNode = m_pRoot;//루트자체를 바꾸면 안되니까 생성
		NODE_TYPE node_type = NODE_TYPE::END;
		
		
		while (true)
		{
			//방향을 먼저정해주고
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

			//그 방향을 변수로 해서, 해당 방향에 넣을지 다시 while돌릴지 판단
			if (nullptr == pNode->arrNode[(int)node_type])
			{
				pNode->arrNode[(int)node_type] = pNewNode;			//해당방향에 자식으로 넣고
				pNewNode->arrNode[(int)NODE_TYPE::PARENT] = pNode;	//해당 자식의 부모를 설정해줌
				break;
			}
			else
			{
				pNode = pNode->arrNode[(int)node_type];		//이미 자식있음, 그 자식을 pNode로 갱신해서 다시 비교(while)
			}	
		
		}
	}

	++m_iCount;

	return true;

}

template<typename T1, typename T2>
inline tBST_Node<T1, T2>* C_BST<T1, T2>::GetInOrderSuccessor(tBST_Node<T1, T2>* _pNode) //중위후속자
{
	tBST_Node<T1, T2>* pSuccessor = nullptr;

	//1.오른쪽 자식이 있는 경우, 오른쪽 자식으로가서, 왼쪽 자식이 없을때까지 내려감
	if (nullptr != _pNode->arrNode[(int)NODE_TYPE::RCHILD])
	{
		pSuccessor = _pNode->arrNode[(int)NODE_TYPE::RCHILD];

		while (pSuccessor->arrNode[(int)NODE_TYPE::LCHILD])
		{
			pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::LCHILD];

		}
	}
	
	//2.오른쪽 자식이 없는 경우, 경로상의 부모중, 왼쪽 자식으로 가진 '부모'까지 올라감
	else
	{
		pSuccessor = _pNode;

		while (true)
		{
			//더이상 올라갈 곳 없다 == 마지막노드
			if (pSuccessor->IsRoot())
				return nullptr; //end iterator

			//부모로부터 왼쪽자식인가?
			if (pSuccessor->IsLeftChild())
			{
				//그때 부모를 후행후속자로 갱신
				pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::PARENT];
				break;
			}
			else
			{
				pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::PARENT];
			}

		}
		//pSuccessor->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] == pSuccessor;너무 장황하니 위쪽에 함수부 구현
	}


	return pSuccessor;
}

template<typename T1, typename T2>
inline tBST_Node<T1, T2>* C_BST<T1, T2>::GetInOrderPredecessor(tBST_Node<T1, T2>* _pNode) //중위선행자 (후속자와 대칭)
{
	tBST_Node<T1, T2>* pSuccessor = nullptr;

	//1.왼쪽 자식이 있는 경우, 왼쪽 자식으로가서, 오른쪽 자식이 없을때까지 내려감
	if (nullptr != _pNode->arrNode[(int)NODE_TYPE::LCHILD])
	{
		pSuccessor = _pNode->arrNode[(int)NODE_TYPE::LCHILD];

		while (pSuccessor->arrNode[(int)NODE_TYPE::RCHILD])
		{
			pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::RCHILD];

		}
	}
	
	//2.왼쪽 자식이 없는 경우, 경로상의 자식을 오른쪽 자식으로 가진 '부모'까지 올라감
	else
	{
		pSuccessor = _pNode;

		while (true)
		{
			//더이상 올라갈 곳 없다 == 마지막노드
			if (pSuccessor->IsRoot())
				return nullptr; //end iterator

			//부모로부터 왼쪽자식인가?
			if (pSuccessor->IsRightChild())
			{
				//그때 부모를 후행후속자로 갱신
				pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::PARENT];
				break;
			}
			else
			{
				pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::PARENT];
			}

		}
		//pSuccessor->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] == pSuccessor;너무 장황하니 위쪽에 함수부 구현
	}


	return pSuccessor;
}

template<typename T1, typename T2>
inline typename C_BST<T1,T2>::iterator C_BST<T1, T2>::begin()
{
	tBST_Node<T1,T2>* pNode = m_pRoot;

	while (pNode->arrNode[(int)NODE_TYPE::LCHILD]) //뭐라도 있으면 true, nullptr는 0 즉 false
	{
		pNode = pNode->arrNode[(int)NODE_TYPE::LCHILD];
	}

	return iterator(this, pNode);
}

template<typename T1, typename T2>
inline typename C_BST<T1, T2>::iterator C_BST<T1, T2>::end()
{
	return iterator(this, nullptr); //end는 오른쪽 끝이 아니라 그다음 nullptr ㅋㅋ
}

template<typename T1, typename T2>
inline typename C_BST<T1, T2>::iterator C_BST<T1, T2>::find(const T1& _find)
{
	tBST_Node<T1, T2>* pNode = m_pRoot;//루트자체를 바꾸면 안되니까 생성
	NODE_TYPE node_type = NODE_TYPE::END;//초기화


	while (true)
	{
		//방향을 먼저정해주고
		if (pNode->pair.first < _find) //둘다 T1 타입 비교연산가능
		{
			node_type = NODE_TYPE::RCHILD;
		}
		else if (pNode->pair.first > _find)
		{
			node_type = NODE_TYPE::LCHILD;
		}
		else //찾음!
		{
			break;
		}

		//못 찾음
		if (nullptr == pNode->arrNode[(int)node_type])
		{
			pNode = nullptr; // iterator end()의 의미
			break;
		}
		else
		{
			pNode = pNode->arrNode[(int)node_type];		//다음 자식을 pNode로 갱신해서 다시 비교(while)
		}
	}
	return iterator(this, pNode);
}


//★이진검색트리 삭제기능 :::: 어려움

	//0.(공통) 삭제대상의 후속자, 반환을 위해 삭제전에 저장해둠
	// 
	//1.삭제대상의 자식이 하나도 없는 경우
	//	1-1 대상이 Root면 Root에 nullptr반환 => 1-4
	//	1-2 대상이 왼/오 어느쪽 자식인지 확인
	//  1-3 부모로 접근, 해당 방향 자식관계를 삭제
	//  1-4 대상 노드 삭제
	// 
	//
	//2.삭제대상의 자식이 둘인 경우 ((※참고※ 대상의 자식이 2이고 그 손자가 2인, 조부모의 후행후속자는 없다. 자식2손주1이 최대))
	//  2-1 후행자를 대상으로 복사 (선행자로 짜도 무방)
	//  2-2 후행자 노드 삭제 + 삭제시 중복 감소되는 iCount복원 (DeleteNode, 2번째 실행시 무조건1,3번에 걸림 2 & 2 루프조합 존재x)
	//	2-3 _pTargetNode에 복사해둔 후행자의 값을 pSuccessor 반환값으로 갱신
	//
	//3.삭제대상의 자식이 하나인 경우(else)
	//  3-1 대상의 자식의 왼/오 방향 저장(eChildType)
	//  3-2 대상이 Root면 Root에 자식을 저장 + 자식의 부모 nullptr로 => 3-6
	//	3-3 대상이 왼/오 어느쪽 자식인지 확인
	//  3-4 부모로 접근, 해당 방향 자식관계를 손자와 연결
	//  3-5 손자의 부모를 조부모로 연결
	//	3-6 대상 노드 삭제
	// 
	//4.iCount감소+후속자반환
	//

template<typename T1, typename T2>
inline typename C_BST<T1, T2>::iterator C_BST<T1, T2>::erase(const iterator& _iter)
{
	assert(this == _iter.m_pBST); //같지않으면 문제가 됨 false시 오류문구, m_pBST ==> 이너클래스인 iterator의 private member기 때문에 C_BST에서 열람불가 (친구추가필요)

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
		//??삭제대상이 루트이고 삭제대상의 자식이 자식이 없는 경우, 루트->후행자 관계 삭제 안해줘도됨??
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
