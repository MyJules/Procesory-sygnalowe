#pragma once

#include <Echo.h>
#include <LowPassFilter.h>
#include <Invert.h>
#include <Fade.h>

namespace effects
{
	template<typename T>
	[[nodiscard]] bool validate(const T&) 
	{
		//static_assert(false, "Please implement validator for this type");
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
