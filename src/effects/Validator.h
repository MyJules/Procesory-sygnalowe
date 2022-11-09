#pragma once

#include <Echo.h>

namespace effects
{
	template<typename T>
	bool validate(const T&) 
	{
		static_assert("Please implement validator for this type");
	}

	bool validate<Echo>(const Echo& echo) 
	{
		return true;
	}
}