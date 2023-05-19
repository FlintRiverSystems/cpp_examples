
using namespace std;
using namespace boost;

BOOST_AUTO_TEST_SUITE(suite2);

BOOST_AUTO_TEST_CASE(test1)
{
	test_watcher::enter_test();

	BOOST_REQUIRE_EQUAL(1, 1);

	test_watcher::exit_test();
}

BOOST_AUTO_TEST_SUITE_END();
