
#include "ClassName.h"

#include "ClassNameImpl.h"

using namespace Namespace;

auto ClassName::Create() -> ClassName::ptr
{
	return ClassNameImpl::Create();
}

auto ClassName::Create (cptr rhs) -> ClassName::ptr
{
	auto rhs2 = std::dynamic_pointer_cast<const ClassNameImpl, const ClassName>(rhs);
	return ClassNameImpl::Create(rhs2);
}
