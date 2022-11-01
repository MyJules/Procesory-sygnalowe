#include "Echo.h"

namespace effects 
{
	Echo::Echo(const EchoParam& echoParam)
		: m_echoParam(echoParam)
	{
	
	}

	kfr::univector<kfr::fbase> Echo::process(const kfr::univector<kfr::fbase>& input, const kfr::audio_format_and_length& format)
	{
		kfr::univector<kfr::fbase> out = input;
		std::size_t histLen = format.samplerate * m_echoParam.getDelayTime();
		std::size_t hitPos = 0;
		kfr::univector<kfr::fbase> history(histLen);

		if (m_echoParam.getDelayTime() == 0.0)
		{
			return out;
		}

		for (auto i = 0; i < format.length; i++, hitPos++)
		{
			if (hitPos == histLen)
			{
				hitPos = 0;
			}
			history[hitPos] = out[i] = input[i] + history[hitPos] * m_echoParam.getDecayFactor();
		}

		return out;
	}

	EchoParam::EchoParam() : m_decayFactor(0), m_delayTime(0)
	{
	}

	float EchoParam::getDelayTime()
	{
		return m_delayTime;
	}

	float EchoParam::getDecayFactor()
	{
		return m_decayFactor;
	}

	std::istream& operator>>(std::istream& is, EchoParam& opts)
	{
		is >> opts.m_delayTime >> opts.m_decayFactor;
		return is;
	}

	std::ostream& operator<<(std::ostream& os, const EchoParam& opts)
	{
		os << "Delay time: " << opts.m_delayTime << ", Delay factor: " << opts.m_decayFactor;
		return os;
	}
}