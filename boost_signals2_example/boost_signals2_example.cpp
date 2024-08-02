
using namespace std;


/* example of an eventbus singleton that just holds signals for other
 * objects to connect to and fire. provides a method to fire on a background thread.
 */
class EventBus
{
public:
	static EventBus& Singleton()
	{
		static EventBus instance;
		return instance;
	}

	/* helper method to connect with a tracking shared_ptr */
	template<class S, class P, class F>
	static auto connect_signal_w_tracking(S& s, P ptr, F f)
	{
		return s.connect(typename S::slot_type(f).track_foreign(ptr));
	}

	template<class S>
	static void fire_signal_async(S& s)
	{
		std::thread t([&s]() { s(); });
		t.detach();
	}

	boost::signals2::signal<void()> Event1;

	void Event1_async() { fire_signal_async(Event1); }

private:
	EventBus() = default;

public:
	EventBus(const EventBus&) = delete;
	void operator= (const EventBus&) = delete;
};

/* receiver that hooks the signals using a shared_ptr */
class receiver : public std::enable_shared_from_this<receiver>
{
public:
	using ptr = std::shared_ptr<receiver>;

	static ptr create()
	{
		auto p = std::make_shared<receiver>();

		auto& eb = EventBus::Singleton();
		EventBus::connect_signal_w_tracking(eb.Event1, p->shared_from_this(), []()
		{
			cout << "receiver got Event1 on thread " << this_thread::get_id() << endl;
		});

		return p;
	}

};

int main ()
{
	cout << "Main Thread: " << this_thread::get_id() << endl;

	auto& eb = EventBus::Singleton();

	eb.Event1.connect([]()
	{
		cout << "slot1 caught signal Event1 on thread " << this_thread::get_id() << endl;
	});

	eb.Event1.connect([]()
	{
		cout << "slot2 caught signal Event1 on thread " << this_thread::get_id() << endl;
	});

	auto r = receiver::create();

	eb.Event1();
	eb.Event1_async();

	this_thread::sleep_for(chrono::seconds(1));

	/* deallocate the receiver and verify that signals can be fired again without a crash */
	r.reset();

	eb.Event1_async();

	this_thread::sleep_for(chrono::seconds(1));

	return 0;
}
