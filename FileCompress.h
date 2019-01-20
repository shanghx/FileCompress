#ifndef _HEAP_H_
#define _HEAP_H_
#include<iostream>

#include<vector>
#include<assert.h>
using namespace std;

template<class T>
struct Small
{

	bool operator()(const T& left, const T& right)

	{
		return left < right;
	}
};
template<class T>
struct Big
{
	bool operator()(const T& left, const T& right)
	{

		return left > right;
	}
};

template<class T,class Compress=Small<T>>
class Heap
{
public:
	Heap()
	{

	}
	Heap(T* a, size_t n)
	{
		//现将元素插入到_a数组里面
		_a.reserve(n);
		for (size_t i = 0; i < n; i++)
		{
			_a.push_back(a[i]);
		}
		//开始建堆
		for (int i = (_a.size() - 2) / 2; i >= 0; --i)
		{
			//向下调整
			AdjustDown(i);
		}
	}
	//调整函数
	void AdjustDown(int root)
	{
		Compress com;
		int Parent = root;
		int Child = 2 * Parent + 1;
		while (Child < _a.size())
		{
			if ((Child + 1) < _a.size() && com(_a[Child + 1], _a[Child]))
			{
				Child++;
			}
			if (com(_a[Child], _a[Parent]))
			{
				swap(_a[Parent], _a[Child]);
				Parent = Child;
				Child = 2 * Parent + 1;
			}
			else
			{
				break;
			}
		}
	}
	void AdjustUp(int root)
	{
		Compress com;
		int Child = root;
		int Parent = (Child - 1) / 2;
		while (Parent >= 0)
		{
			if (com(_a[Child], _a[Parent]))
			{
				swap(_a[Parent], _a[Child]);
				Child = Parent;
				Parent = (Child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}

	void Push(T x)
	{
		_a.push_back(x);
		AdjustUp(_a.size() - 1);
		AdjustDown(0);
	}
	size_t Size()
	{
		return _a.size();
	}
	bool Empty()
	{
		return _a.empty();
	}
	T& Top()
	{
		assert(_a.size() > 0);
		return _a[0];
	}
	bool IsHeap()
	{
		for (size_t i = 0; i < (_a.size() - 2) / 2; i++)
		{
			if (_a[i] < _a[i * 2 + 1] || (i * 2 + 2) < _a.size() && _a[i] < _a[i * 2 + 2])
			{
				return false;
			}
			
		}
		return true;
	}
	bool IsHeapR(int root)
	{
		if(root >= _a.size())
			return true;

		int left = root * 2 + 1;
		int right = root * 2 + 2;

		if (left < _a.size())
		{
			if(_a[left] > _a[root])

				return false;
			if (right < _a.size())
			{
				if (_a[right] > _a[root])
					return false;
			}
			
		}
		return IsHeapR(left) && IsHeapR(right);
	}
	protected:
		vector<T> _a;
};
void TestHeap()
{
	int a[] = { 20,21,13,12,16,18,15,17,14,19 };
	Heap<int>hp1(a, sizeof(a) / sizeof(a[0]));
	
	if (hp1.IsHeapR(19))
	{
		cout << "ok" << endl;
	}
}

#endif
