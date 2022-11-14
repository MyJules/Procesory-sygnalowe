#pragma once

#include <Echo.h>
#include <LowPassFilter.h>

namespace effects
{
	template<typename T>
	[[nodiscard]] bool validate(const T&) 
	{
		static_assert("Please implement validator for this type");
	}

	template<>
	[[nodiscard]] bool validate<LowPassFilterParam>(const LowPassFilterParam& lowPassParam)
	{
		return false;
	}
}