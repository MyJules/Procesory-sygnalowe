#pragma once

#include <kfr/io.hpp>

namespace effects
{
	class IEffect
	{
	public:
		virtual ~IEffect() = default;

		[[nodiscard]] virtual kfr::univector<kfr::fbase> process(const kfr::univector<kfr::fbase>&, const kfr::audio_format_and_length&) = 0;
	};
}