
#define KEEP_ENUM_LIST
#include "MyEnum.h"

#include <iostream>
#include <stdexcept>
#include <format>

#define TO_STRING(VAR) if (v == MyEnum::VAR) return #VAR;

std::string to_string (MyEnum v)
{
	ENUM_LIST(TO_STRING)

	throw std::runtime_error (
		(std::format("{}:{} - enum value {} not in {}", 
			__FILE__, __LINE__, static_cast<int>(v), typeid(MyEnum).name())));
}

#define FROM_STRING(VAR) if (s == #VAR) return MyEnum::VAR;

MyEnum MyEnum_from_string (const std::string& s)
{
	ENUM_LIST(FROM_STRING)

	throw std::runtime_error (
		(std::format("{}:{} - invalid string value \"{}\" for {}",
			__FILE__, __LINE__, s, typeid(MyEnum).name())));
}

std::ostream& operator<< (std::ostream& os, MyEnum v)
{
	os << to_string(v);
	return os;
}

std::wostream& operator<< (std::wostream& os, MyEnum v)
{
	auto s = to_string(v);
	os << std::wstring(s.begin(), s.end());
	return os;
}

