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

	String(const char* str = "")//���캯��
	{

		_size = strlen(str);
		
		_str = new char[_size + 1];
		strcpy(_str, str);
		_capacity = _size+1;
	}


	~String()//��������
	{
		delete[]_str;
		_str = nullptr;
		_size = _capacity = 0;
	}

	String(const String& s)//��������

		:_str(new char[strlen(s._str) + 1])
	{
		strcpy(_str, s._str);
		_size = s._size;
		_capacity = s._capacity;

	}


	//
	//	//s1 = s1;
	//s1 = s2;

	//���������
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

	void reserve(size_t n)//����
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
	void PushBack(char c)//β���ַ�
	{
		if (_size == _capacity)
		{
			reserve(_capacity * 2);
		}


		_str[_size++] = c;
		_str[_size] = '\0';
	}

	void PushBack(const char* str)//β���ַ���
	{
		size_t str_size = strlen(str);
		//����
		if (_size + str_size >= _capacity)
		{
			reserve(_capacity * 2);
		}

		//����
		while (*str != '\0')
		{
			_str[_size++] = *str++;
		}

		_str[_size] = '\0';
	}

	void PushFront(char ch)//ͷ���ַ�
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

	void PopBack()//βɾ
	{
		if (_size == 0)
		{
			cout << "���ַ���Ϊ��" << endl;
			return;
		}

		_size--;
		_str[_size] = '\0';
	}

	void PopFront()//ͷɾ
	{
		if (_size == 0)
		{
			cout << "���ַ���Ϊ��" << endl;
		}

		for (int i = 0; i<(_size+1); ++i)
		{
			_str[i] = _str[i+1];
		}
		_size--;
		_str[_size] = '\0';

	}


	void Insert(size_t pos, char ch)//������λ�ò����ַ�
	{
	   if (pos > _size)
	   {
	     cout << "posλ������" << endl;
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

	void Insert(size_t pos, const char* str)//��ָ��λ�ò����ַ���
	{
		if (pos > _size)
		{
			cout << "posλ������" << endl;
			return;
		}
		else
		{
			size_t str_size = strlen(str);
			
			if (_size + str_size+1 >= _capacity)//+1����ΪҪ��'\0'����λ��
			{
				reserve(_capacity * 3);
			}
			int Last_size = _size + str_size;
			_str[Last_size--] = '\0';

			for (int i = _size-1 ; i > (int)pos; --i)//pos����ַ�������ƶ�str_size��λ��
			{
				_str[Last_size--] = _str[i];
			}

			//�����ַ���
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
	

    // ����c��string�е�һ�γ��ֵ�λ��
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

	// �����Ӵ�s��string�е�һ�γ��ֵ�λ��
	size_t Find(const char* str, size_t pos = 0) const 
	//(����ָ�룬�ִ��͸����ӵ�һ����ʼ�ַ�ƥ�䣬�����һ���ַ�ƥ���
	//��ʼ����ַ���ƥ�䵽���һ������;���в�ͬ���ִ��˻ؿ�ʼ���������䣬�����ظ�������ֱ���ҵ�Ϊֹ)
	{
		if (pos > _size)
		{
			cout << "posλ������<<endl";
		}
		size_t index_str = 0;

		//��ѭ�������˳���Ҫô�ҵ��ˣ�Ҫô�ҵ���βҲû�ҵ�
		while (_str[index_str] != '\0')
		{
			if (_str[index_str] == *str)//�ӿ�ͷ��ʼƥ���ַ�
			{
				size_t  Find_index = index_str;
				size_t  str_index = 0;
				while (1)
				{
					//�����������strû��ͣ�������ͱ�ʾ�ҵ���
					if (str[str_index] == '\0')
					{
						return index_str;
					}

					//�������Ⱦͽ���ѭ��
					if (_str[Find_index] != str[str_index])
					{
						break;
					}
					Find_index++;
					str_index++;
				}
				//����ѭ��
			}
			//��ƥ�������ǰ��
			index_str++;
		}

		return -1;
	}


	////// ɾ��pos���len���ַ�
	//void String::Erase(size_t pos, size_t len)
	//{
	//	if (pos > _size)
	//	{
	//		cout << "posλ������<<endl";
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


//����β��  βɾ
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
//����ͷ��   ͷɾ
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


//���Բ���   �������  ��ָ��λ�ò����ַ���
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
////��ͳд��
//#include<iostream>
//#include<string>
//#include<assert.h>
//using namespace std;
//
//class String
//{
//public:
//
//	String(const char* str = "")//���캯��
//	{
//		// ����string�����ʱ���������nullptrָ�룬��Ϊ����Ƿ����˴�������
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
//	~String()//��������
//	{
//		delete[]_str;
//		_str = nullptr;
//	}
//
//
//	String(const String& s)//��������
//		: _str(new char[strlen(s._str) + 1])
//	{
//			strcpy(_str, s._str);
//	}
//
//
//	String& operator=(const String& s)//��ֵ����
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
////�ִ�д��
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

//	// �Ա��º�����ĸ�ֵ�Ǹ�ʵ�ֱȽϺã�
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
