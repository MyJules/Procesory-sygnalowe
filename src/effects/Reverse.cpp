#include "Reverse.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include <algorithm>

kfr::univector<kfr::fbase> effects::Reverse::process(const kfr::univector<kfr::fbase>& input, const kfr::audio_format_and_length& format)
{
	spdlog::info("Applying reverse effect");
	kfr::univector<kfr::fbase> out = input;
	std::reverse(out.begin(), out.end());
	return out;
}
