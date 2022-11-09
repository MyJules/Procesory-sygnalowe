#include "LowPassFilter.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

effects::LowPassFilterParam::LowPassFilterParam()
{
}

std::istream& effects::operator>>(std::istream& is, LowPassFilterParam& opts)
{
	return is;
}

std::ostream& effects::operator<<(std::ostream& os, const LowPassFilterParam& opts)
{
	return os;
}

effects::LowPassFilter::LowPassFilter(const LowPassFilterParam& lowPassFilterParam)
	: m_lowPassFilterParam(lowPassFilterParam)
{
}

kfr::univector<kfr::fbase> effects::LowPassFilter::process(const kfr::univector<kfr::fbase>&, const kfr::audio_format_and_length&)
{
	spdlog::error("Low pass filter is not implemented!!!");
	return kfr::univector<kfr::fbase>();
}
