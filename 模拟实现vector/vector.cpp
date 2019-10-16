#define _CRT_SECURE_NO_WARNINGS 1
#pragma  once
#include<assert.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

template<class T>//模板
class Vector
{
public:
	typedef T* iterator;

	Vector()//构造函数
		:_start(nullptr)
		,_finish(nullptr)
		,_endofstorage(nullptr)
	{}

	Vector(const Vector<T>& v)      //拷贝构造(深拷贝)
	{
		_start = new T[v.Size()];
		//for (size_t i = 0; i < v.Size(); i++)
		//{
		//	_start[i] = T[i];
		//}
		memcpy(_start, v._start, sizeof(T)*v.Size());
		_finish = _start + v.Size();
		_endofstorage = _start + v.Size();
	}

	iterator  begin()
	{
		return _start;
	}

	iterator end()
	{
		return _finish;
	}

	size_t Size() const
	{
		return _finish - _start;
	}

	size_t Capacity() const
	{
		return _endofstorage - _start;
	}

	T& operator[](size_t pos)
	{
		assert(pos < Size());
			return _start[pos];
	}

	const T& operator[](size_t pos) const
	{
		assert(pos < Size());
			return _start[pos];
	}

	void reserve(size_t n)//扩容
		//1.申请新的空间
		//2.拷贝数据
		//3.释放旧的空间
	{
		if (Capacity() < n)
		{
			size_t size = Size();
			T* tmp = new T[n];
			if (_start>0)
			{
				for (size_t i = 0; i < size; i++)
				{
					tmp[i] = this->_start[i];
				}
				delete[] _start;
			}

			_start = tmp;
			_finish = _start + size;
			_endofstorage = _start + n;
		}
	}

	void Push_back(const T& x)//尾插
	{
		if (_finish == _endofstorage)
		{
			size_t  newcapacity = Capacity() == 0 ? 2 : Capacity() * 3;
			reserve(newcapacity);
		}
		*_finish = x;
		++_finish;
	}

	void Pop_back()//尾删
	{
		if (Size() == 0)
		{
			cout << "无法删除空数组" << endl;
				return;
		}

		_finish--;
	}

	void Insert(iterator pos,const T& x)//任意位置插入数据
	{
		if (_finish == _endofstorage)
		{
			size_t n = pos - _start;
			size_t newcapacity = Capacity() == 0 ? 2 : Capacity() * 3;
			reserve(newcapacity);
			pos = _start + n;
		}

		iterator end = _finish - 1;
		while (end >= pos)//往后挪动
		{
			*(end + 1) = *(end);
			--end;
		}

		*pos = x;
		++_finish;
	}

	void Erase(iterator pos)//删除
	{
		assert(pos < _finish && pos >= _start);
		iterator  end = pos + 1;
		while (end < _finish)
		{
			*(end-1) = *end;
			++end;
		}
		--_finish;
	}

	//Vector<T>& operator=(Vector<T> v)//运算符重载
	//{
	//	swap(v);
	//	return *this;
	//}

	//void swap(Vector<T>& v)
	//{
	//	swap(_start, v._start);
	//	swap(_finish, v._finish);
	//	swap(_endofstorage, v._endofstorage);
	//}
private:
	iterator _start;
	iterator _finish;
	iterator _endofstorage;
};

void tset1()
{
	Vector<int> v;
	v.Push_back(1);
	v.Push_back(2);
	v.Push_back(3);
	v.Push_back(4);

	/*v.Pop_back();*/
	auto it = v.begin();
	it = v.begin();
	v.Erase(it);
	v.Erase(it);

	v.Insert(it, 2);
	v.Insert(it, 1);

	Vector<int>copy(v);
	for (auto e : copy)
	{
		cout << e << " ";
	}
	cout << endl;
}

int main()
{
	tset1();
	system("pause");
	return 0;
}