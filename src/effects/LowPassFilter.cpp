#include "LowPassFilter.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include <kfr/all.hpp>

effects::LowPassFilterParam::LowPassFilterParam()
	: m_frequency(0), m_rollOff(0)
{
}

float effects::LowPassFilterParam::getFrequency() const
{
	return m_frequency;
}

int effects::LowPassFilterParam::getRollOff() const
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

static const std::unordered_map<int, int> rollOffParamMap
{
	{6, 1},
	{12, 2},
	{24, 3},
	{36, 4},
	{48, 5},
};

kfr::univector<kfr::fbase> effects::LowPassFilter::process(const kfr::univector<kfr::fbase>& input, const kfr::audio_format_and_length& format)
{
	spdlog::info("Applying Low Pass Filter effect with parameters: {}", m_lowPassFilterParam);

	const int rollOff = m_lowPassFilterParam.getRollOff();

	kfr::univector<kfr::fbase> out = input;
	kfr::zpk<kfr::fbase> filt = kfr::avx2::iir_lowpass(kfr::butterworth<kfr::fbase>(rollOffParamMap.at(rollOff)),
													   m_lowPassFilterParam.getFrequency(),
													   format.samplerate);
	std::vector<kfr::biquad_params<kfr::fbase>> bqs = kfr::to_sos(filt);
	kfr::biquad<32>(bqs, kfr::unitimpulse());

	kfr::avx2::biquad_filter<kfr::fbase> filter(bqs);

	filter.apply(out);

	return out;
}
