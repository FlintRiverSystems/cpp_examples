
#include "ClassName.h"

#include "ClassNameImpl.h"

using namespace Namespace;

auto ClassName::create() -> ClassName::ptr
{
	return ClassNameImpl::create();
}

auto ClassName::create (cptr rhs) -> ClassName::ptr
{
	auto rhs2 = std::dynamic_pointer_cast<const ClassNameImpl, const ClassName>(rhs);
	return ClassNameImpl::create(rhs2);
}
