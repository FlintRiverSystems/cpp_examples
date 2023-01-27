
#include <iostream>

#include <boost/regex.hpp>

using namespace std;

int main ()
{
	{ /* find all matches in a string */

		string input ("find 1 the 2 numbers 37");

		boost::regex re(R"(\d+)");

		boost::sregex_iterator re_it(input.begin(), input.end(), re);
		boost::sregex_iterator e;

		for (; re_it != e; ++re_it)
		{
			cout << "match : " << (*re_it)[0].str() << endl;
		}
	}

	cout << endl;

	{ /* parsing */

		string input ("BOO1-2");

		boost::regex  re(R"(BOO(\d+)-(\d+))");

		boost::smatch result;
		if (boost::regex_match(input, result, re))
		{
			cout << "Whole String: " << result.str(0) << endl;
			cout << "Match1: " << result.str(1) << endl;
			cout << "Match2: " << result.str(2) << endl;
		}
		else
			cout << "No Match" << endl;

	}

	/* Warning: make sure the string used for the match is not destroyed. 
	 * ie don't use the return from a function in the call to regex_match
	 */

	return 0;
}
