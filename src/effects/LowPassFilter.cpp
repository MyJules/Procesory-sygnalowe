#include "LowPassFilter.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

effects::LowPassFilterParam::LowPassFilterParam()
	: m_frequency(0), m_rollOff(0)
{
}

float effects::LowPassFilterParam::getFrequency()
{
	return m_frequency;
}

float effects::LowPassFilterParam::getRollOff()
{
	return m_rollOff;
}

std::istream& effects::operator>>(std::istream& is, LowPassFilterParam& opts)
{
	is >> opts.m_frequency >> opts.m_rollOff;
	return is;
}

std::ostream& effects::operator<<(std::ostream& os, const LowPassFilterParam& opts)
{
	os << "Frequency: " << opts.m_frequency << ", Roll off: " << opts.m_rollOff;
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
