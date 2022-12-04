#include "Invert.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include <algorithm>

kfr::univector<kfr::fbase> effects::Invert::process(const kfr::univector<kfr::fbase>& input, const kfr::audio_format_and_length& format)
{
	spdlog::info("Applying invert effect");
    std::size_t outLen = format.length;
	kfr::univector<kfr::fbase> out(outLen);
	
    for (auto i = 0; i < format.length; i++)
    {
        out[i] = -input[i];
    }
    
	return out;
}