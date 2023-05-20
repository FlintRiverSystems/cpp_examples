
#pragma once

class test_watcher
{
private:
	static bool _logging_initialized;

	static bool _test_failed;
	static std::string _prev_test_name;

public:
	static void enter_test();
	static void exit_test();
};
