#include <string.h>
#include <stdio.h>
#include <algorithm>
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

	MyBigNumber(char *s, int sLen);
	MyBigNumber& operator=(const MyBigNumber &num);
	MyBigNumber operator+(const MyBigNumber &num) const;

};

MyBigNumber::MyBigNumber()
	: len(0)
	, sign(0)
	, arraylen(0)
{
	memset(data, 0, sizeof(data));
}

MyBigNumber::MyBigNumber(char *s, int sLen)
{
	memset(data, 0, sizeof(data));
	len = sLen;
	if(s[0] == '-')
	{
		sign = -1;
	}
	else
	{
		sign = 1;
	}
	int digitcount = 0;
	for(int i = sLen - 1; i >= 0 && s[i] >= '0' && s[i] <= '9'; i--)
	{
		
	}
}

MyBigNumber MyBigNumber::operator+(const MyBigNumber &num) const
{
	MyBigNumber sum;
	
	return sum;
}