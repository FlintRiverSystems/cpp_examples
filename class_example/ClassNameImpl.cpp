
#include "ClassNameImpl.h"

using namespace Namespace;

ClassName::ptr ClassNameImpl::Create () 
{
	auto p = std::make_shared<ClassNameImpl>(protected_token());
	p->_self = p;
	p->_init();
	return p;
}

ClassName::ptr ClassNameImpl::Create (ClassNameImpl::cptr rhs) 
{
	auto p = std::make_shared<ClassNameImpl>(protected_token());
	p->_self = p;
	p->_init();
	p->_copy(rhs);
	return p;
}

void ClassNameImpl::_init ()
{
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

auto ClassNameImpl::Prop1 () const -> int
{
	return _prop1;
}

void ClassNameImpl::setProp1 (int val)
{
	_prop1 = val;
	_update();
}

auto ClassNameImpl::Prop2() const -> int
{
	return _prop2;
}

void ClassNameImpl::Method1 ()
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

