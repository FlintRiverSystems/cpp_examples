
#pragma once

class TestWatcher
{
private:
	static bool _logging_initialized;

	static bool _test_failed;
	static std::string _prev_test_name;

public:
	static void EnterTest();
	static void ExitTest();
};
