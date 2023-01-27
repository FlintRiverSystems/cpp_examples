
#include <iostream>
#include <regex>

using namespace std;

int main()
{
	std::string s = "1.2.3";
	std::regex version_num_regex (R"(\d\.(\d)\.\d)");
	std::smatch m;

	/* regex_match requires that the entire sequence matches the regex */
	if (std::regex_match(s, m, version_num_regex))
	{
		cout << "itsa match" << endl;
		cout << "matches: " << m.size() << endl;
		cout << "match 1: " << m[0] << endl;
		cout << "match 2: " << m[1] << endl;
	}

	/* regex_search searches the string for first occurrence of the regex */
	s = "this is the string 3.4.5 with a version numbers 6.7.8 in it";
	if (std::regex_search(s, m, version_num_regex))
	{
		cout << "itsa match" << endl;
		cout << "match: " << m.str() << endl;
	}
}

