#ifndef _HMT_H_
#define _HMT_H_

#include"Heap.h"


template<class T>
struct HuffmanTreeNode
{
	HuffmanTreeNode<T>* _left;
	HuffmanTreeNode<T>* _right;
	HuffmanTreeNode<T>* _parent;
	T _w;

	 HuffmanTreeNode(const T& w)
		:_w(w)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
	{};
};

//仿函数
template<class T >
struct Com
{
	bool operator()(const HuffmanTreeNode<T>*left, const HuffmanTreeNode<T>* right) const
	{
		return left->_w < right->_w;
	}
};

template<class W>
class HuffmanTree
{
	typedef HuffmanTreeNode<W> Node;
public:
	HuffmanTree()
		:_root(NULL)
	{}

	HuffmanTree(W* a, size_t n, const W& ivaliad)
	{
		
		Heap<Node*, Com<W> > SmallHeap;
		for (size_t i = 0; i < n; i++)
		{
			if (a[i] != ivaliad)
			{
				SmallHeap.Push(new Node(a[i]));
			}
		}

		while (SmallHeap.Size() > 1)
		{
			Node* left = SmallHeap.Top();
			SmallHeap.Pop();
			Node* right = SmallHeap.Top();
			SmallHeap.Pop();

			Node* parent = new Node(left->_w + right->_w);
			parent->_left = left;
			parent->_right = right;
			left->_parent = parent;
			right->_parent = parent;
			SmallHeap.Push(parent);
		}
		_root = SmallHeap.Top();
	}
	Node* GetRoot()
	{
		return _root;
	}
private:
	Node* _root;
};

#endif
