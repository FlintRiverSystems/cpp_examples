
#include "ClassNameImpl.h"

using namespace Namespace;

ClassName::ptr ClassNameImpl::create () 
{
	auto p = std::make_shared<ClassNameImpl>(protected_token());
	return p;
}

ClassName::ptr ClassNameImpl::create (ClassNameImpl::cptr rhs) 
{
	auto p = std::make_shared<ClassNameImpl>(protected_token());
	p->_copy(rhs);
	return p;
}

void ClassNameImpl::_init ()
{
	_dirty = false;
	_prop1 = 0;
	_update();
}

void ClassNameImpl::_copy (ClassNameImpl::cptr rhs)
{
	_prop1 = rhs->_prop1;
	_update();
}

void ClassNameImpl::_update ()
{
	_prop2 = 2 * _prop1;
}

void ClassNameImpl::method1 ()
{
}

auto ClassNameImpl::to_string() const -> std::string
{
	/* not the most efficient but you shouldn't be calling
	 * to_string in a tight loop.
	 *
	 * cache if higher performance is necessary
	 */

	std::stringstream ss;
	ss << "Hello from ClassNameImpl";
	return ss.str();
}

