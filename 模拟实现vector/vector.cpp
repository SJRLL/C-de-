#define _CRT_SECURE_NO_WARNINGS 1
#pragma  once
#include<assert.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

template<class T>//ģ��
class Vector
{
public:
	typedef T* iterator;

	Vector()//���캯��
		:_start(nullptr)
		,_finish(nullptr)
		,_endofstorage(nullptr)
	{}

	Vector(const Vector<T>& v)      //��������(���)
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

	void reserve(size_t n)//����
		//1.�����µĿռ�
		//2.��������
		//3.�ͷžɵĿռ�
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

	void Push_back(const T& x)//β��
	{
		if (_finish == _endofstorage)
		{
			size_t  newcapacity = Capacity() == 0 ? 2 : Capacity() * 3;
			reserve(newcapacity);
		}
		*_finish = x;
		++_finish;
	}

	void Pop_back()//βɾ
	{
		if (Size() == 0)
		{
			cout << "�޷�ɾ��������" << endl;
				return;
		}

		_finish--;
	}

	void Insert(iterator pos,const T& x)//����λ�ò�������
	{
		if (_finish == _endofstorage)
		{
			size_t n = pos - _start;
			size_t newcapacity = Capacity() == 0 ? 2 : Capacity() * 3;
			reserve(newcapacity);
			pos = _start + n;
		}

		iterator end = _finish - 1;
		while (end >= pos)//����Ų��
		{
			*(end + 1) = *(end);
			--end;
		}

		*pos = x;
		++_finish;
	}

	void Erase(iterator pos)//ɾ��
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

	//Vector<T>& operator=(Vector<T> v)//���������
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