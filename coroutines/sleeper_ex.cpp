
/* based on https://itnext.io/c-20-coroutines-complete-guide-7c3fc08db89d */

#include <coroutine>
#include <chrono>

using namespace std;
using namespace std::chrono;
using namespace std::chrono_literals;

/*
 * coroutine example that uses a custom awaitable to sleep on a different thread
 */

struct sleeper_task_t
{
	struct promise_type
	{
		using handle_t = std::coroutine_handle <promise_type> ;

		sleeper_task_t get_return_object() { return {}; }

		std::suspend_never initial_suspend() { return {}; }
		std::suspend_never final_suspend() noexcept { return {}; }

		void return_void() { }
		void unhandled_exception() {}
	};
};

struct awaitable_sleep
{
	bool await_ready() { return false; }

	bool await_suspend (std::coroutine_handle<> h)
	{
		cout << "await_suspend" << endl;
		auto t = std::jthread([h, l = length]
		{
			this_thread::sleep_for(l);
			cout << endl << "resuming on thread " << this_thread::get_id() << endl;
			h.resume();
		});

		t.detach(); /* must detach, otherwise dtor blocks this function from returning */

		cout << "await_suspend finished" << endl;

		return true;
	}

	int await_resume()
	{
		cout << "await_resume" << endl;
		return 37;
	}

	std::chrono::duration<int, std::milli> length;
};

sleeper_task_t sleepy_coroutine()
{
	cout << "before sleep, tid=" << this_thread::get_id() << endl;
	auto before = steady_clock::now();

	auto result = co_await awaitable_sleep{ 2s };

	/* the rest of this function is executed on the thread created in await_suspend above */

	auto after = steady_clock::now();

	cout << "coroutine continuing on id=" << this_thread::get_id() << endl;
	cout << "co_await returned: " << result << endl;
	cout << "slept for " << (after - before) / 1ms << " ms" << endl;
}

void sleeper_ex()
{
	cout << "calling coroutine, tid=" << this_thread::get_id() << endl;

	sleepy_coroutine();

	cout << endl << "control returned to caller, tid=" << this_thread::get_id() << endl;

	cout << "delaying to allow coroutine to resume" << endl;
	this_thread::sleep_for(3s);
}

