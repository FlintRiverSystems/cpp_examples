
#include "classname.h"

#include "classname_impl.h"

using namespace Namespace;

auto classname::create() -> classname::ptr
{
	return classname_impl::create();
}

auto classname::create (cptr rhs) -> classname::ptr
{
	auto rhs2 = std::dynamic_pointer_cast<const classname_impl, const classname>(rhs);
	return classname_impl::create(rhs2);
}
