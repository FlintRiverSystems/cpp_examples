
#pragma once

#include <string>

#define ENUM_LIST(FN) \
	FN(Value0) \
	FN(Value1) \
	FN(Value2)

#define MAKE_ENUM(VAR) VAR,
enum class MyEnum : unsigned int { ENUM_LIST(MAKE_ENUM) };

#undef MAKE_ENUM

#ifndef KEEP_ENUM_LIST
#undef ENUM_LIST
#endif

std::string to_string (MyEnum v);

MyEnum MyEnum_from_string (const std::string& s);

std::ostream& operator<< (std::ostream& os, MyEnum v);

std::wostream& operator<< (std::wostream& os, MyEnum v);

