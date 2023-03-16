
/* based on https://itnext.io/c-20-coroutines-complete-guide-7c3fc08db89d */

#include <coroutine>

using namespace std;

/*
 * coroutine example that doesn't actually do anything except demonstrate the mechanism
 */

/* return type of our coroutine */
struct generator_t
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
		generator_t get_return_object()
		{
			cout << "get_return_object()" << endl;

			/* capture the promise in the generator_t instance */
			return generator_t{handle_t::from_promise(*this)};
		}

		/* called before the body of the coroutine is executed */
		std::suspend_always initial_suspend()
		{
			cout << "initial_suspend()" << endl;
			return {};
		}

		/* called to yield a value */
		std::suspend_always yield_value(int value)
		{
			cout << "yield_value(" << value << ")" << endl;
			current_value = value;
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

		int current_value;
	};

	/* the methods/members of the outer generator_t struct are user defined, not compiler dictated */

	explicit generator_t(promise_type::handle_t handle) : _handle(handle) {}

	~generator_t()
	{
		if (_handle) _handle.destroy();
	}

	generator_t(const generator_t&) = delete;
	generator_t& operator= (const generator_t&) = delete;

	generator_t(generator_t&& rhs) noexcept : _handle(rhs._handle)
	{
		rhs._handle = {};
	}

	generator_t& operator= (generator_t&& rhs) noexcept
	{
		if (this == &rhs) return *this;
		if (_handle) _handle.destroy();
		_handle = rhs._handle;
		rhs._handle = {};
		return *this;

	}

	const int get_next()
	{
		cout << "get_next() - resuming..." << endl;
		_handle.resume(); /* blocks until next co_yield */
		cout << "get_next() - returning value" << endl;
		return _handle.promise().current_value;
	}

private:
	promise_type::handle_t _handle;
};

generator_t my_generator()
{
	cout << "my_generator()" << endl;
	int x = 0;
	while (true)
	{
		co_yield x;
		cout << "incrementing" << endl;
		x++;
	}
}

void generator_ex()
{
	generator_t g = my_generator();

	for (int i = 0; i < 10; ++i)
		cout << g.get_next() << endl;
}
