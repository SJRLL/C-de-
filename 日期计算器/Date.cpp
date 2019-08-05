#define _CRT_SECURE_NO_WARNINGS 1


#include<iostream>
#pragma once
using namespace std;


class  Date
{
public:
	//���캯��
	Date(int year = 2018, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	~Date()//��������
	{

	}

	//�������캯��
	Date(const Date& d)//���봫���ã������������޵ݹ�
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	//��ֵ����
	Date& operator=(const Date& d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}


	bool IsLeapyear(int year)
	{
		return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
	}

	int GetmonthDay(int year, int month)
	{
		static int monthDay[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (IsLeapyear(year) && month == 2)
		{
			return 29;
		}
		else
		{
			return monthDay[month];
		}
	}

	bool operator==(const Date& d)
	{
		return _year == d._year
			&&_month == d._month
			&&_day == d._day;
	}

	bool operator!=(const Date& d)
	{
		return !(*this == d);
	}

	bool operator>(const Date& d)
	{
		if ((_year > d._year) || (_year == d._year && _month > d._month) || (_year == d._year && _month == d._month  && _day > d._day))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator>=(const Date& d)
	{
		return (*this>d || (*this == d));
	}

	bool operator<(const Date& d)
	{
		if ((_year < d._year) || (_year == d._year && _month < d._month) || (_year == d._year && _month == d._month  && _day < d._day))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	Date& operator+=(int day)
	{
		_day += day;
		while (_day > GetmonthDay(_year, _month))	
		{
			_day =_day- GetmonthDay(_year, _month);
			_month += 1;
			if (_month > 12)
			{
				++_year;
				_month = 1;
			}
		}
			return *this;
	}


	Date operator+(int day)//����ı�ԭ������ֵ�����ڼ�������
	{
		Date ret= *this;//����thisָ��
		return ret += day;

	}

	Date& operator-=(int day)
	{
		if (day < 0)
		{
			return *this += (-day);
		}

		_day = _day - day;
		while (_day < 1)
		{
			_month -= 1;
			if (_month == 0)
			{
				_month = 12;
				--_year;
			}

			_day += GetmonthDay(_year, _month);
		}

		return *this;
	}

	Date operator-(int day)
	{
		Date ret = *this;
		return ret -= day;
	}

	int operator-(const Date& d)
	{
		int count = 0;
		if (*this > d)
		{
			while (*this != d)
			{
				count++;
				*this = *this - 1;
			}
		}
		else
		{
			while (*this != d)
			{
				count++;
				*this = *this + 1;
			}
		}

		return count;

	}

	void PrintDate1()
	{
		cout << "ԭ��������" << _year << "-" << _month << "-" << _day << endl;
	}

	void PrintDate2()
	{
		cout << "�����ں������" << _year << "-" << _month << "-" << _day << endl;
	}

	void PrintDate3()
	{
		cout << "�����ں������" << _year << "-" << _month << "-" << _day << endl;
	}

	void PrintDate4()
	{
		cout << "�������ں������" << _year << "-" << _month << "-" << _day << endl;
	}


	void PrintDate5()
	{
		cout << "���ڼ������ں������" << _year << "-" << _month << "-" << _day << endl;
	}

private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	Date d1(2018, 1, 1);
	d1.PrintDate1();

	Date d2;
	d2=d1 + 66;
	d2.PrintDate2();

	Date d3;
	d3 += 66;
	d3.PrintDate3();

	Date d4 = d1 - 66;
	d4.PrintDate4();

	Date d5=d1-d4;
	d5.PrintDate5();
	system("pause");
	return 0;
}