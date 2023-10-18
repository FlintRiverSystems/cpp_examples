
#pragma once

#include "ClassName.h"

namespace Namespace {

class ClassNameImpl : public ClassName
{
public:
	using ptr		= std::shared_ptr<ClassNameImpl>;
	using cptr		= std::shared_ptr<const ClassNameImpl>;
	using wptr		= std::weak_ptr<ClassNameImpl>;
	using vector	= std::vector<ptr>;

	static ClassName::ptr create ();
	static ClassName::ptr create (ClassNameImpl::cptr rhs);

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
	void _copy (ClassNameImpl::cptr rhs);
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
	ClassNameImpl() = delete;
	ClassNameImpl(protected_token) { _init();  }
	virtual ~ClassNameImpl () override = default;

	/* remove copy ctors and assignment */
	ClassNameImpl (const ClassNameImpl &) = delete;
	ClassNameImpl (ClassNameImpl &&) = delete;
	auto operator= (const ClassNameImpl &) -> ClassNameImpl& = delete;	
	auto operator= (ClassNameImpl &&) -> ClassNameImpl& = delete;	

};

#if 0
inline auto to_string (const ClassNameImpl& rhs) -> std::string
{
	return rhs.to_string();
}

inline auto operator<< (std::ostream& os, const ClassNameImpl& rhs) -> std::ostream&
{
	/* TODO: write object to ostream */
	return os;
}

inline auto operator<< (std::ostream& os, const ClassNameImpl::ptr rhs) -> std::ostream&
{
	os << *rhs;
	return os;
}


inline auto operator>> (std::istream& is, ClassNameImpl& rhs) -> std::istream&
{
	/* TODO: parse object from istream */
	return is;
}

inline auto operator>> (std::istream& is, ClassNameImpl::ptr& rhs) -> std::istream&
{
	/* ptr passed to us is empty, allocate an actual object */
	//rhs = std::make_shared<ClassName>();
	//rhs = ClassName::create();

	is >> *rhs;
	return is;
}
#endif

}

