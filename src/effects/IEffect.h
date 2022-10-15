#pragma once

#include <q_io/audio_file.hpp>

namespace effects
{
	class IEffect
	{
	public:
		virtual ~IEffect() = default;

		virtual void process(const cycfi::q::wav_memory &wav) = 0;
	};
}