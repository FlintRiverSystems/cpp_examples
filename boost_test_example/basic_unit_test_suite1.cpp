
#include "boost_log.h"

using namespace std;
using namespace boost;


/* this is how to handle types without operator<< defined
 * if it's not possible to define it
 * 
 * from: https://stackoverflow.com/a/17573165/70964 */
namespace boost { namespace test_tools { namespace tt_detail 
{
template <>
struct print_log_value<vector<int>>
{
	void operator() (std::ostream& os, const vector<int>& v)
	{
		if (v.empty()) return;
		os << v[0];
		for_each(v.begin()+1, v.end(), [&](const auto& x) { os << ", " << x;  });
	}
};
}}}

static logger_t lg;

BOOST_AUTO_TEST_SUITE(Suite1);

BOOST_AUTO_TEST_CASE(test1)
{
	TestWatcher::EnterTest();

	BOOST_LOG(lg) << "Starting test1";
	BOOST_LOG(lg) << "UTF-8 character: \xd0\xb6";
	BOOST_LOG(lg) << "UTF-8 character: ж";

	vector<int> a{1, 2, 3};
	vector<int> b{4, 5, 6};
	//vector<int> b{1, 2, 3};

	BOOST_REQUIRE_EQUAL(a, b); /* must use REQUIRE, which aborts test case */

	TestWatcher::ExitTest();
}

BOOST_AUTO_TEST_CASE(test2) /* never runs */
{
	TestWatcher::EnterTest();

	BOOST_REQUIRE_EQUAL(1, 1);

	TestWatcher::ExitTest();
}

BOOST_AUTO_TEST_SUITE_END();
