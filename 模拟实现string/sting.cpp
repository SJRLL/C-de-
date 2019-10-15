#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

class String
{
public:
	typedef const char* const_iterator;
	typedef char* iterator;

	const_iterator begin() const
	{
		return _str;
	}

	iterator begin()
	{
		return _str;
	}

	iterator end()
	{
		return _str + _size;
	}

	String(const char* str = "")//构造函数
	{

		_size = strlen(str);
		
		_str = new char[_size + 1];
		strcpy(_str, str);
		_capacity = _size+1;
	}


	~String()//析构函数
	{
		delete[]_str;
		_str = nullptr;
		_size = _capacity = 0;
	}

	String(const String& s)//拷贝构造

		:_str(new char[strlen(s._str) + 1])
	{
		strcpy(_str, s._str);
		_size = s._size;
		_capacity = s._capacity;

	}


	//
	//	//s1 = s1;
	//s1 = s2;

	//运算符重载
	String& operator=(const String& s)
	{
		if (this != &s)
		{
			delete[] _str;
			_str = new char[s._capacity];
			strcpy(_str, s._str);
			_size = s._size;
			_capacity = s._capacity;
		}
		return *this;
	}


	char* String_str()
	{
		return _str;
	}

	char& operator[](size_t  pos)
	{
		return _str[pos];
	}

	size_t String_size()
	{
		return _size;
	}

	void reserve(size_t n)//扩容
	{
		if (n > _capacity)
		{
			char* tmp = new char[n + 1];
			strcpy(tmp, _str);
			delete[]_str;
			_str = tmp;
			_capacity = n;
		}
	}
	void PushBack(char c)//尾插字符
	{
		if (_size == _capacity)
		{
			reserve(_capacity * 2);
		}


		_str[_size++] = c;
		_str[_size] = '\0';
	}

	void PushBack(const char* str)//尾插字符串
	{
		size_t str_size = strlen(str);
		//扩容
		if (_size + str_size >= _capacity)
		{
			reserve(_capacity * 2);
		}

		//拷贝
		while (*str != '\0')
		{
			_str[_size++] = *str++;
		}

		_str[_size] = '\0';
	}

	void PushFront(char ch)//头插字符
	{
		if (_size + 1 >= _capacity)
		{
			reserve(_capacity * 2);
		}

		_str[_size + 1] = '\0';
		for (int i = _size; i > 0; --i)
		{
			_str[i] = _str[i - 1];
		}

		_str[0] = ch;
		_size += 1;
	}

	void PopBack()//尾删
	{
		if (_size == 0)
		{
			cout << "该字符串为空" << endl;
			return;
		}

		_size--;
		_str[_size] = '\0';
	}

	void PopFront()//头删
	{
		if (_size == 0)
		{
			cout << "该字符串为空" << endl;
		}

		for (int i = 0; i<(_size+1); ++i)
		{
			_str[i] = _str[i+1];
		}
		_size--;
		_str[_size] = '\0';

	}


	void Insert(size_t pos, char ch)//在任意位置插入字符
	{
	   if (pos > _size)
	   {
	     cout << "pos位置有误！" << endl;
	   }
	  else
	  {
	    if (_size + 1 >= _capacity)
	      {
	         reserve(_capacity * 2);
	      }

	     _str[_size + 1] = '\0';
	     for (int i = _size; i >(int)pos; --i)
	     {
	       _str[i] = _str[i - 1];
	     }

	     _str[pos] = ch;
	     _size++;
	  }

	}

	void Insert(size_t pos, const char* str)//在指定位置插入字符串
	{
		if (pos > _size)
		{
			cout << "pos位置有误" << endl;
			return;
		}
		else
		{
			size_t str_size = strlen(str);
			
			if (_size + str_size+1 >= _capacity)//+1是因为要给'\0'留出位置
			{
				reserve(_capacity * 3);
			}
			int Last_size = _size + str_size;
			_str[Last_size--] = '\0';

			for (int i = _size-1 ; i > (int)pos; --i)//pos后的字符串向后移动str_size个位置
			{
				_str[Last_size--] = _str[i];
			}

			//插入字符串
			while (*str != '\0')
			{
				_str[pos++] = *str++;
			}
			_size += str_size;
		}
		
	}

	//s1.append("11111")
	void append(size_t n, char c)
	{

		for (size_t i = 0; i < n; ++i)
		{
			PushBack(c);
		}
	}

	const  String& operator+=(char ch)
	{
		PushBack(ch);
		return *this;
	}

	bool operator<(const String& s)
	{
		int i = 0;
		while (_str[i] == s._str[i] && i<_size)
		{
			i++;
		}
		if (i == _size)
		{
			return false;
		}
		return _str[i]>s._str[i] ? true : false;
	}

	bool operator<=(const String& s)
	{
		return !(*this > s);
	}

	bool operator>(const String& s)
	{
		return (*this < s || *this == s);
	}

	bool operator>=(const String& s)
	{
		return !(*this < s);
	}

	bool operator==(const String& s)
	{
		int i = 0;
		while (_str[i] == s._str[i] && i < _size)
		{
			i++;
		}
		if (i == _size && s._str[i] == '\0')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator!=(const String& s)
	{
		return !(*this==s);
	}
	

    // 返回c在string中第一次出现的位置
	size_t Find(char c, size_t pos = 0) const
	{
		if (_size == 0)
		{
			return -1;
		}

		for (size_t i = 0; i < _size; ++i)
		{
			if (_str[i] == c)
			{
				return i;
			}
		
		}
		return -1;
	}

	// 返回子串s在string中第一次出现的位置
	size_t Find(const char* str, size_t pos = 0) const 
	//(两个指针，字串和父串从第一个开始字符匹配，如果第一个字符匹配后，
	//开始逐个字符串匹配到最后一个，中途若有不同，字串退回开始，父串不变，继续重复操作，直至找到为止)
	{
		if (pos > _size)
		{
			cout << "pos位置有误报<<endl";
		}
		size_t index_str = 0;

		//若循环条件退出，要么找到了，要么找到结尾也没找到
		while (_str[index_str] != '\0')
		{
			if (_str[index_str] == *str)//从开头开始匹配字符
			{
				size_t  Find_index = index_str;
				size_t  str_index = 0;
				while (1)
				{
					//如果遍历完了str没有停下来，就表示找到了
					if (str[str_index] == '\0')
					{
						return index_str;
					}

					//如果不相等就结束循环
					if (_str[Find_index] != str[str_index])
					{
						break;
					}
					Find_index++;
					str_index++;
				}
				//跳出循环
			}
			//不匹配继续向前找
			index_str++;
		}

		return -1;
	}


	////// 删除pos后的len个字符
	//void String::Erase(size_t pos, size_t len)
	//{
	//	if (pos > _size)
	//	{
	//		cout << "pos位置有误<<endl";
	//	}
	//	if (pos + len < _size)
	//	{
	//		size_t n = pos + len;
	//		while (n != _size)
	//		{
	//			_str[pos++] = _str[n++];
	//		}
	//	}
	//	_str[pos] = '\0';
	//	_size = pos;
	//}

	void Show()
	{
		printf("%s", _str);
	}

private:

	char* _str;
	size_t _size;
	size_t _capacity;
};


//
//void test2()
//{
//	String s1;
//	String s2("hello bit");
//	String s3(s2);
//	s1 = s3;
//	cout << s1.c_str() << endl;
//	cout << s2.c_str() << endl;
//	cout << s3.c_str() << endl;
//}


//测试尾插  尾删
//void test1()
//{
//	String s1("hello");
//	s1.Show();
//
//	s1.PushBack('w');
//	s1.PushBack('o');
//	s1.PushBack('r');
//	s1.PushBack('l');
//	s1.PushBack('d');
//	s1.Show();
//
//	s1.append(5,'q');
//	s1.Show();
//
//	s1 += 'b';
//	s1.Show();
//
//	s1.PushBack("world");
//	s1.Show();
//
//     s1.PopBack();
//	 s1.PopBack();
//	 s1.PopBack();
//	 s1.Show();
//}
//
//测试头插   头删
//void test3()
//{
//	String s1("ello");
//	/*s1.Show();*/
//
//	s1.PushFront('h');
//	s1.Show();
//
//	s1.PopFront();
//	s1.Show();
//
//}


//测试查找   随机插入  在指定位置插入字符串
void test4()
{
	String s1("world");
	/*s1.Show();*/

	//s1.Insert(0, 'h');
	//s1.Show();

	//s1.Insert(4, 'd');
	//s1.Show();

	//size_t  pos = s1.Find('l');
	//printf("%d\n", pos);

	/*size_t pos = s1.Find("llo");
	printf("%d\n", pos);*/

	//s1.Insert( 2,"hel");
	//s1.Show();

	s1.SubStr(3, 2);
	s1.Show();

	//s1.Erase(2, 3);
	//s1.Show();
}

int main()
{

	//Test2();
	//test1();
	//test3();
	test4();
	system("pause");
	return 0;
}
//
////传统写法
//#include<iostream>
//#include<string>
//#include<assert.h>
//using namespace std;
//
//class String
//{
//public:
//
//	String(const char* str = "")//构造函数
//	{
//		// 构造string类对象时，如果传递nullptr指针，认为程序非法，此处断言下
//	  if (nullptr == str)
//	    {
//		  assert(false);
//		  return;
//	    }
//
//	    _str = new char[strlen(str) + 1];
//	    strcpy(_str, str);
//
//	}
//
//
//
//	~String()//析构函数
//	{
//		delete[]_str;
//		_str = nullptr;
//	}
//
//
//	String(const String& s)//拷贝构造
//		: _str(new char[strlen(s._str) + 1])
//	{
//			strcpy(_str, s._str);
//	}
//
//
//	String& operator=(const String& s)//赋值运算
//	{
//		if (this != &s)
//		{
//			
//			char* Ptr = new char[strlen(_str) + 1];		
//			strcpy(Ptr, s._str);
//			delete[]_str;
//			_str = Ptr;
//
//		}
//
//		return *this;
//	}
//
//
//private:
//	char* _str;
//};
//
//void test1()
//{
//	string s1("hello");
//	cout << s1.c_str() << endl;
//
//
//
//}
//
//int main()
//{
//	test1();
//	system("pause");
//	return 0;
//}
//
////现代写法
//class String
//{
//public:
//	String(const char* str = "")
//	{
//		if (nullptr == str)
//			str = "";
//
//		_str = new char[strlen(str) + 1];
//		strcpy(_str, str);
//	}
//
//	String(const String& s)
//		: _str(nullptr)
//	{
//		String strTmp(s._str);
//		swap(_str, strTmp);
//	}

//	// 对比下和上面的赋值那个实现比较好？
//	String& operator=(String s)
//	{
//		swap(_str, s._str);
//		return *this;
//	}
//
//	~String()
//	{
//		if (_str)
//		{
//			delete[] _str;
//			_str = nullptr;
//		}
//	}
//
//private:
//	char* _str;
//};
