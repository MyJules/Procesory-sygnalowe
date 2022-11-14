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