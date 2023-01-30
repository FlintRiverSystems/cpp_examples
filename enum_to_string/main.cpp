
#include <iostream>

#include "MyEnum.h"

using namespace std;

int main (int argc, char** argv)
{
	MyEnum e = MyEnum::Value1;

	cout << to_string(e) << endl;
	cout << (int)MyEnum_from_string("Value2") << endl;

	try
	{
		to_string((MyEnum)37);
	}
	catch (std::exception& ex)
	{
		cout << "Exception: " << ex.what() << endl;
	}

	try
	{
		MyEnum_from_string("unknown");
	}
	catch (std::exception& ex)
	{
		cout << "Exception: " << ex.what() << endl;
	}

	return 0;
}


