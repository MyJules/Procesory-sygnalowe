#include "HighPassFilter.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include <kfr/all.hpp>

effects::HighPassFilterParam::HighPassFilterParam()
	: m_frequency(0), m_rollOff(0)
{
}

float effects::HighPassFilterParam::getFrequency() const
{
	return m_frequency;
}

int effects::HighPassFilterParam::getRollOff() const
{
	return m_rollOff;
}

std::istream& effects::operator>>(std::istream& is, HighPassFilterParam& opts)
{
	is >> opts.m_frequency >> opts.m_rollOff;
	return is;
}

std::ostream& effects::operator<<(std::ostream& os, const HighPassFilterParam& opts)
{
	os << "Frequency: " << opts.m_frequency << ", Roll off: " << opts.m_rollOff;
	return os;
}

effects::HighPassFilter::HighPassFilter(const HighPassFilterParam& HighPassFilterParam)
	: m_HighPassFilterParam(HighPassFilterParam)
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

kfr::univector<kfr::fbase> effects::HighPassFilter::process(const kfr::univector<kfr::fbase>& input, const kfr::audio_format_and_length& format)
{
	spdlog::info("Applying High Pass Filter effect with parameters: {}", m_HighPassFilterParam);

	const int rollOff = m_HighPassFilterParam.getRollOff();

	kfr::univector<kfr::fbase> out = input;
	kfr::zpk<kfr::fbase> filt = kfr::avx2::iir_highpass(kfr::butterworth<kfr::fbase>(rollOffParamMap.at(rollOff)),
													   m_HighPassFilterParam.getFrequency(),
													   format.samplerate);
	std::vector<kfr::biquad_params<kfr::fbase>> bqs = kfr::to_sos(filt);
	kfr::biquad<32>(bqs, kfr::unitimpulse());

	kfr::avx2::biquad_filter<kfr::fbase> filter(bqs);

	filter.apply(out);

	return out;
}
