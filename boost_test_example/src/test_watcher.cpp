
#include "test_watcher.h"

#include "boost_log.h"

#include <cstdlib>

//#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

void setup_logging();

bool test_watcher::_logging_initialized = false;
bool test_watcher::_test_failed = false;
std::string test_watcher::_prev_test_name;

static logger_t lg;

void test_watcher::enter_test()
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

void test_watcher::exit_test()
{
	_test_failed = false;
}
