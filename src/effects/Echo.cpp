#include "Echo.h"

namespace effects 
{
	Echo::Echo(const EchoParam& echoParam)
		: m_echoParam(echoParam)
	{
	
	}

	kfr::univector<kfr::fbase> Echo::process(const kfr::univector<kfr::fbase>& input)
	{
		kfr::univector<kfr::fbase> out = input;
		std::size_t hitPos = 0;
		std::size_t histLen = 44100 * m_echoParam.getDelayTime();
		kfr::univector<kfr::fbase> history(histLen);

		if (m_echoParam.getDelayTime() == 0.0)
		{
			return out;
		}

		for (auto i = 0; i < input.size(); i++, hitPos++)
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
}