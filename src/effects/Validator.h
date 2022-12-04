#pragma once

#include <Echo.h>
#include <LowPassFilter.h>
#include <Invert.h>
#include <Fade.h>

#define Tprint(x) print<x>(#x)

namespace effects
{
	template<typename T>
	[[nodiscard]] bool validate(const T& value) 
	{
<<<<<<< HEAD
		//static_assert(false, "Please implement validator for this type");
=======
		spdlog::warn("Validator is not implemented fo this value: {}", value);
>>>>>>> c521b0c5eb01b29c389d5d488df85802d7162abe
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
