#include <string>
#include <stdio.h>
#include <algorithm>
#include <sstream>
#include <iomanip>
using namespace std;

const int MAX_DIGITS = 10000;

class MyBigNumber
{
protected:
	int data[MAX_DIGITS];
	int len;
	int sign;
	int arraylen;
	
public:
	MyBigNumber();
	virtual ~MyBigNumber() {}

	MyBigNumber(string s);
	MyBigNumber(const MyBigNumber &); // copy constructor
	MyBigNumber& operator=(const MyBigNumber &num);
	MyBigNumber operator+(const MyBigNumber &rhs) const;
	string getValue();
	bool operator>(const MyBigNumber &rhs) const;
	MyBigNumber operator-() const;
	MyBigNumber operator-(const MyBigNumber &rhs) const;
};

MyBigNumber::MyBigNumber()
	: len(0)
	, sign(0)
	, arraylen(0)
{
	memset(data, 0, sizeof(data));
}

MyBigNumber::MyBigNumber(const MyBigNumber &obj)
{
	*this = obj;
}

MyBigNumber& MyBigNumber::operator=(const MyBigNumber &num)
{
	memcpy(data, num.data, sizeof(data));
	len = num.len;
	sign = num.sign;
	arraylen = num.arraylen;
	return *this;
}

MyBigNumber::MyBigNumber(string s)
{
	memset(data, 0, sizeof(data));
	
	if(s[0] == '-')
	{
		sign = -1;
		s = s.substr(1);
	}
	else
	{
		sign = 1;
	}
	len = s.size();
	int digitcount = 0;
	string tmp;
	int i = 0;
	for(i = len - 4; i >= 0; i -= 4)
	{
		tmp = s.substr(i, 4);
		data[digitcount++] = abs(atoi(tmp.c_str()));
	}
	if(i % 4 != 0)
	{
		tmp = s.substr(0, i+4);
		data[digitcount++] = abs(atoi(tmp.c_str()));
	}
	arraylen = digitcount;
}

bool MyBigNumber::operator>(const MyBigNumber &rhs) const
{
	return true;
}

MyBigNumber MyBigNumber::operator-() const
{
	MyBigNumber ret(*this);
	ret.sign = -sign;
	return ret;
}

MyBigNumber MyBigNumber::operator+(const MyBigNumber &rhs) const
{
	if(sign != rhs.sign)
	{
		return *this - (-rhs);
	}
	MyBigNumber sum(*this);
	int sumlen = max(sum.arraylen, rhs.arraylen);
	int carry = 0;
	for(int i = 0; i < sumlen; i++)
	{
		int tmp = sum.data[i] + rhs.data[i] + carry;
		carry = tmp / 10000;
		sum.data[i] = tmp % 10000;
	}
	sum.arraylen = sumlen;
	if(carry != 0)
	{
		sum.data[sumlen] = carry;
		sum.arraylen++;
	}
	sum.len = sum.sign < 0 ? sum.getValue().size() - 1 : sum.getValue().size();
	return sum;
}

MyBigNumber MyBigNumber::operator-(const MyBigNumber &rhs) const
{
	if(sign != rhs.sign)
	{
		return *this + (-rhs);
	}
	MyBigNumber ret(*this);
	int carry = 0;
	int loop = max(ret.arraylen, rhs.arraylen);
	for(int i = 0; i < loop; i++)
	{
		int tmp =  data[i] - rhs.data[i] + carry;
		carry = tmp < 0 ? -1 : 0;
		ret.data[i] = abs(tmp);
		if(i == loop - 1)
		{
			ret.sign = (tmp < 0 ? -1 : 1) * sign;
		}
	}
	ret.arraylen = 0;
	for(int j = loop - 1; j >= 0; j--)
	{
		if(ret.data[j] != 0)
		{
			ret.arraylen = j + 1;
			break;
		}
	}
	ret.len = ret.sign < 0 ? ret.getValue().size() - 1 : ret.getValue().size();
	return ret;
}

string MyBigNumber::getValue()
{
	ostringstream oss;
	if(sign == -1)
		oss << '-';
	for(int i = arraylen - 1; i >= 0; i--)
	{
		if(i < arraylen - 1)
			oss << setw(4) << setfill('0') << abs(data[i]);
		else if( i == arraylen - 1 || data[i])
			oss << abs(data[i]);
	}
	return oss.str();
}

