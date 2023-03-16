
/* based on https://itnext.io/c-20-coroutines-complete-guide-7c3fc08db89d */

#include <coroutine>

using namespace std;

/*
 * coroutine example that doesn't actually do anything except demonstrate the mechanism
 */

/* return type of our coroutine */
struct task_t
{

	struct promise_type
	{
		/* the compiler will create an instance of promise_type when the coroutine is called
		 *
		 * the specific typename "promise_type" and the method names inside
		 * are prescribed by the standard
		 */

		using handle_t = std::coroutine_handle <promise_type> ;

		/* creates an instance of the outer type, called when coroutine is called */
		task_t get_return_object()
		{
			cout << "get_return_object()" << endl;

			/* capture the promise in the task_t instance */
			return task_t{handle_t::from_promise(*this)};
		}

		/* called before the body of the coroutine is executed */
		std::suspend_always initial_suspend()
		{
			cout << "initial_suspend()" << endl;
			return {};
		}

		/* called after the coroutine returns */
		std::suspend_never final_suspend() noexcept
		{
			cout << "final_suspend()" << endl;
			return {};
		}

		void return_void()
		{
			cout << "return_void()" << endl;
		}

		void unhandled_exception() {}
	};

	/* the methods/members of the outer task_t struct are user defined, not compiler dictated */

	explicit task_t(promise_type::handle_t handle) : _handle(handle) {}

	task_t(const task_t&) = delete;
	task_t& operator= (const task_t&) = delete;

	task_t(task_t&& rhs) noexcept : _handle(rhs._handle)
	{
		rhs._handle = {};
	}

	task_t& operator= (task_t&& rhs) noexcept
	{
		if (this == &rhs) return *this;
		if (_handle) _handle.destroy();
		_handle = rhs._handle;
		rhs._handle = {};
		return *this;

	}

	void resume()
	{
		cout << "resume()" << endl;
		_handle.resume();
	}

	void destroy()
	{
		cout << "destroy()" << endl;
		_handle.destroy();
	}

private:
	promise_type::handle_t _handle;
};

task_t my_coroutine()
{
	cout << "my_generator()" << endl;
	co_return;
}

void empty_coroutine_ex()
{
	task_t c = my_coroutine();

	cout << "calling resume" << endl;

	c.resume();
}

