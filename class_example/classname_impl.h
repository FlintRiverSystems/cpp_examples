
#pragma once

#include "classname.h"

namespace Namespace {

class classname_impl : public classname
{
public:
	using ptr		= std::shared_ptr<classname_impl>;
	using cptr		= std::shared_ptr<const classname_impl>;
	using wptr		= std::weak_ptr<classname_impl>;
	using vector	= std::vector<ptr>;

	static classname::ptr create ();
	static classname::ptr create (classname_impl::cptr rhs);

	virtual auto prop1() const -> int override { return _prop1; }

	virtual void set_prop1(int val) override { _update_prop(_prop1, val); }

	virtual auto prop2() const -> int override { return _prop2; }

	virtual void method1 () override;

	virtual bool dirty() override { return _dirty; }
	virtual void set_dirty() override { _dirty = true; }
	virtual void clear_dirty() override { _dirty = false; }

	virtual auto to_string() const -> std::string override;

protected:
	wptr _self;

	void _init();
	void _copy (classname_impl::cptr rhs);
	void _update();

	int _prop1;
	int _prop2;

	bool _dirty;

	template<class T, class U>
	void _update_prop(T& member, const U& new_value)
	{
		if (member == new_value) return;
		member = new_value;
		_dirty = true;
		_update();
	}

protected:
	class protected_token {}; /* exists to prevent public use of ctor */
						 	  /* we want the ctor to be public so we can use make_shared in create()
							   * which reduces heap fragmentation */
public:
	classname_impl() = delete;
	classname_impl(protected_token) {}
	virtual ~classname_impl () override = default;

	/* remove copy ctors and assignment */
	classname_impl (const classname_impl &) = delete;
	classname_impl (classname_impl &&) = delete;
	auto operator= (const classname_impl &) -> classname_impl& = delete;	
	auto operator= (classname_impl &&) -> classname_impl& = delete;	

};

#if 0
inline auto to_string (const classname_impl& rhs) -> std::string
{
	return rhs.to_string();
}

inline auto operator<< (std::ostream& os, const classname_impl& rhs) -> std::ostream&
{
	/* TODO: write object to ostream */
	return os;
}

inline auto operator<< (std::ostream& os, const classname_impl::ptr rhs) -> std::ostream&
{
	os << *rhs;
	return os;
}


inline auto operator>> (std::istream& is, classname_impl& rhs) -> std::istream&
{
	/* TODO: parse object from istream */
	return is;
}

inline auto operator>> (std::istream& is, classname_impl::ptr& rhs) -> std::istream&
{
	/* ptr passed to us is empty, allocate an actual object */
	//rhs = std::make_shared<classname>();
	//rhs = classname::create();

	is >> *rhs;
	return is;
}
#endif

}

