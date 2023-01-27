
using namespace std;
using namespace boost;

BOOST_AUTO_TEST_SUITE(Suite2);

BOOST_AUTO_TEST_CASE(test1)
{
	TestWatcher::EnterTest();

	BOOST_REQUIRE_EQUAL(1, 1);

	TestWatcher::ExitTest();
}

BOOST_AUTO_TEST_SUITE_END();
