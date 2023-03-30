
#include <iostream>

#include "classname.h"

using namespace std;

int main()
{
	auto ptr = Namespace::classname::create();

	cout << ptr->to_string() << endl;
}
