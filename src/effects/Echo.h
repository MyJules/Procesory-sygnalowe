#pragma once

#include "IEffect.h"

#include <iostream>

namespace effects 
{
	class EchoParam
	{
	public:
		EchoParam();

		float getDelayTime();
		float getDecayFactor();

		friend std::istream& operator>>(std::istream& is, EchoParam& opts)
		{
			is >> opts.m_delayTime >> opts.m_decayFactor;
			return is;
		}

		friend std::ostream& operator<<(std::ostream& os, const EchoParam& opts)
		{
			os << "Delay time: " << opts.m_delayTime << ", Delay factor: " << opts.m_decayFactor;
			return os;
		}

	private:
		float m_delayTime;
		float m_decayFactor;
	};

	class Echo : public IEffect
	{
	public:
		Echo(const EchoParam& echoParam);

		kfr::univector<kfr::fbase> process(const kfr::univector<kfr::fbase>& input, const kfr::audio_format_and_length& format) override;

	private:
		EchoParam m_echoParam;
	};
}