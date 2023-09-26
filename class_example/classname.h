
#pragma once

#include <vector>
#include <memory>
#include <sstream>

/* example of a class with the full implementation details hidden in a derived class.
 *
 * this is used as a better alternative to pimpl - supports multiple implementations
 * of the derived classes (for testing, etc)
 *
 * this class is simply the interface. The derived class, ClassNameImpl, contains all the
 * necessary data members and details.  This implements a "compiler firewall" which
 * reduces the dependencies (ie headers) that the consumers of this class will see.
 *
 * if this level of separation is unnecessary, just define all the details here
 * and don't use the derived class.  If only data members need to be firewalled
 * and derived classes will not be used, use a data pimpl.
 *
 * This implementation also forces the use of shared_ptr. The class cannot
 * be instantiated directly.
 */

namespace Namespace {

/* this is the interface */

class ClassName
				// don't use enabled_shared_from_this - it complicates inheritance
{
public:
	using ptr		= std::shared_ptr<ClassName>;
	using cptr		= std::shared_ptr<const ClassName>;
	using wptr		= std::weak_ptr<ClassName>;
	using vector	= std::vector<ptr>;

	static ptr create ();
	static ptr create (cptr rhs);

	virtual auto prop1() const -> int = 0;
	virtual void set_prop1 (int val) = 0;

	virtual auto prop2() const -> int = 0;

	virtual void method1() = 0;

	virtual bool dirty() = 0;
	virtual void set_dirty() = 0;
	virtual void clear_dirty() = 0;

	virtual std::string to_string() const = 0;

protected:
	ClassName () = default; /* necessary for derived implementation classes */

public:
	virtual ~ClassName () = default;

	/* remove copy ctors and assignment */
	ClassName (const ClassName&) = delete;
	ClassName (ClassName&&) = delete;
	auto operator= (const ClassName&) -> ClassName& = delete;	
	auto operator= (ClassName&&) -> ClassName& = delete;	
};


inline auto to_string (const ClassName& rhs) -> std::string
{
	return rhs.to_string();
}

inline auto operator<< (std::ostream& os, const ClassName& rhs) -> std::ostream&
{
	/* TODO: write object to ostream */
	return os;
}

inline auto operator<< (std::ostream& os, const ClassName::ptr rhs) -> std::ostream&
{
	os << *rhs;
	return os;
}


inline auto operator>> (std::istream& is, ClassName& rhs) -> std::istream&
{
	/* TODO: parse object from istream */
	return is;
}

inline auto operator>> (std::istream& is, ClassName::ptr& rhs) -> std::istream&
{
	/* ptr passed to us is empty, allocate an actual object */
	//rhs = std::make_shared<ClassNameInterface>();
	//rhs = ClassNameInterface::create();

	is >> *rhs;
	return is;
}

}

