
#include "classname_impl.h"

using namespace Namespace;

classname::ptr classname_impl::create () 
{
	auto p = std::make_shared<classname_impl>(protected_token());
	p->_self = p;
	p->_init();
	return p;
}

classname::ptr classname_impl::create (classname_impl::cptr rhs) 
{
	auto p = std::make_shared<classname_impl>(protected_token());
	p->_self = p;
	p->_init();
	p->_copy(rhs);
	return p;
}

void classname_impl::_init ()
{
	_dirty = false;
	_prop1 = 0;
	_update();
}

void classname_impl::_copy (classname_impl::cptr rhs)
{
	_prop1 = rhs->_prop1;
	_update();
}

void classname_impl::_update ()
{
	_prop2 = 2 * _prop1;
}

void classname_impl::method1 ()
{
}

auto classname_impl::to_string() const -> std::string
{
	/* not the most efficient but you shouldn't be calling
	 * to_string in a tight loop.
	 *
	 * cache if higher performance is necessary
	 */

	std::stringstream ss;
	ss << "Hello from classname_impl";
	return ss.str();
}

