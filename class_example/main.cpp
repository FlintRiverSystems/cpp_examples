
#include <iostream>

#include "ClassName.h"

using namespace std;

int main()
{
	auto ptr = Namespace::ClassName::create();

	cout << ptr->to_string() << endl;
}
