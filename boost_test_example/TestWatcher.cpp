
#include "TestWatcher.h"

#include "boost_log.h"

#include <cstdlib>

//#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

void setup_logging();

bool TestWatcher::_logging_initialized = false;
bool TestWatcher::_test_failed = false;
std::string TestWatcher::_prev_test_name;

static logger_t lg;

void TestWatcher::EnterTest()
{
	if (!_logging_initialized)
	{
		_logging_initialized = true;
		setup_logging();
	}
	
	if (_test_failed)
	{
		BOOST_LOG(lg) << "================================================================================";
		BOOST_LOG(lg) << "Previous Test " + _prev_test_name + " Failed, exiting";
		BOOST_LOG(lg) << "================================================================================"; 

		exit(1);
	}

	_prev_test_name = boost::unit_test::framework::current_test_case().full_name();
	BOOST_LOG(lg) << "================================================================================";
	BOOST_LOG(lg) << "Executing " + _prev_test_name;
	BOOST_LOG(lg) << "================================================================================";

	_test_failed = true;
}

void TestWatcher::ExitTest()
{
	_test_failed = false;
}
