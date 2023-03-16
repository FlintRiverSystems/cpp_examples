


#include <iostream>

using namespace std;

void empty_coroutine_ex();
void generator_ex();
void sleeper_ex();

int main (int argc, char** argv)
{
	cout << "coroutines..." << endl;
	//empty_coroutine_ex();
	//generator_ex();
	sleeper_ex();
	cout << "finished" << endl;
	return 0;
}
