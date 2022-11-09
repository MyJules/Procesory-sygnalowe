#pragma once

#include "IEffect.h"

namespace effects
{
	class Reverse : public IEffect
	{
		kfr::univector<kfr::fbase> process(const kfr::univector<kfr::fbase>& input, const kfr::audio_format_and_length& format) override;
	};
}