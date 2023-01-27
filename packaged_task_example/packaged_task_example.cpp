
#include <iostream>
#include <future>

//using task_t = std::packaged_task<void()>;
using task_t = std::packaged_task<int()>;

int main()
{
	task_t work([]()
	{
		std::cout << "starting work" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));
		std::cout << "work finished" << std::endl;
		return 4;
	});

	/* get handle to future result */
	auto result = work.get_future();

	/* execute on background thread */
	std::thread t (std::move(work));
	t.detach();

	/* wait for result */
	std::cout << "main waiting for result" << std::endl;
	auto x = result.get();
	std::cout << "main exiting, result=" << x << std::endl;
}
