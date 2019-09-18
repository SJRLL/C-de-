//#define _CRT_SECURE_NO_WARNINGS 1
//
//#include<iostream>
//using namespace std;
//
//class String
//{
//public:
//	typedef const char* const_iterator;
//	typedef char* iterator;
//
//	const_iterator begin() const
//	{
//		return _str;
//	}
//
//	iterator begin()
//	{
//		return _str;
//	}
//
//	iterator end()
//	{
//		return _str + _size;
//	}
//
//	String(const char* str = "")//���캯��
//		:_str(new char[strlen(str)+1])
//	{
//		//�Ѿ�����'\0'
//		strcpy(_str, str);
//		_size = strlen(str);
//		_capacity = _size;
//	}
//
//
//	~String()//��������
//	{
//		delete[]_str;
//		_str = nullptr;
//		_size = _capacity=0;
//	}
//
//	String(const String& s)//��������
//	
//		:_str(new char[s._size+1])
//		,_size(s._size)
//		, _capacity(s._size)
//
//		{
//			strcpy(_str, s._str);
//		}
//	
//
//	//s1 = s1;
//	//s1 = s2;
//
//	//���������
//	String& operator=(const String& s)
//	{
//		if (this != &s)
//		{
//			delete[]_str;
//			_str = new char[s._size + 1];
//			strcpy(_str, s._str);
//			_size = s._size;
//			_capacity = s._capacity;
//		}
//		return *this;
//	}
//
//	const char* c_str()
//	{
//		return _str;
//	}
//
//	char& operator[](size_t  pos)
//	{
//		return _str[pos];
//	}
//
//	size_t size()
//	{
//		return _size;
//	}
//
//	void reserve(size_t n)//����
//	{
//		if (n > _capacity)
//		{
//			char* tmp = new char[n + 1];
//			strcpy(tmp, _str);
//			delete[]_str;
//			_str = tmp;
//			_capacity = n;
//		}
//	}
//	void push_back(char ch)
//	{
//		if (_size == _capacity)
//		{
//			//����
//			reserve(_capacity * 2);
//		}
//
//		_str[_size] = ch;
//		++_size;
//		_str[_size] = '\0';
//
//	}
//
//	//s1.append("11111")
//	void append(const char* str)
//	{
//		size_t len = strlen(str);
//		if (_size + len > _capacity)
//		{
//			//����
//			{
//				reserve(_capacity * 2);
//			}
//		}
//
//	}
//
//	const  String& operator+=(char ch)
//	{
//		push_back(ch);
//		return *this;
//	}
//
//
//
//private:
//
//	char* _str;
//	size_t _size;
//	size_t _capacity;
//};
//
//void test1()
//{
//	String s1("hello");
//	cout << s1.c_str() << endl;
//
//	/*s1 += "world";
//	cout << s1._capacity() << endl;*/
//}
//
//int main()
//{
//	test1();
//	system("pause");
//	return 0;
//}


#include<iostream>
using namespace std;

class String
{
public:

	String(const char* str = "")//���캯��
		:_str(new char[strlen(str) + 1])
	{
		strcpy(_str, str);
		_size = strlen(str);
		_capacity = _size;
	}

	~String()//��������
	{
		delete[]_str;
		_str = nullptr;
		_size = _capacity = 0;
	}


	String(const String& s)//��������
		:_str(new char[s._size + 1])
		, _size(s._size)
		, _capacity(s._size)
	{
		strcpy(_str, s._str);
	}

	String& operator=(const String& s)//��ֵ����
	{
		if (this != &s)
		{
			delete[]_str;
			_str = new char[strlen(s._size + 1)];
			strcpy(_str, s._str);
			_size = s._size;
			_capacity = s._capacity;
		}

		return *this;
	}


private:
	char* _str;
};