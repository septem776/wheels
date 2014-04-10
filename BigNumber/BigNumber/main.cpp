#include "MyBigNumber.hpp"
#include <iostream>

int main()
{
	MyBigNumber a("1156463123241876151321");
	MyBigNumber b("-31231654894943121");

	cout<<(a+b+a+b).getValue()<<endl;
	return 0;
}