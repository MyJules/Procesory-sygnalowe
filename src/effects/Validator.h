#pragma once

#include <Echo.h>
#include <LowPassFilter.h>

#define Tprint(x) print<x>(#x)

namespace effects
{
	template<typename T>
	[[nodiscard]] bool validate(const T& value) 
	{
		spdlog::warn("Validator is not implemented fo this value: {}", value);
		return false;
	}

	template<>
	[[nodiscard]] bool validate<LowPassFilterParam>(const LowPassFilterParam& lowPassParam)
	{
		int validRollOff[] = {6, 12, 24, 36, 48};
		bool isValid = false;

		for (int i : validRollOff) 
		{
			if (i == lowPassParam.getRollOff()) 
			{
				isValid = true;
			}
		}
		
		return isValid;
	}
}