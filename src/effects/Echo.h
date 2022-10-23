#pragma once

#include "IEffect.h"

#include <iostream>

namespace effects 
{
	class EchoParam
	{
	public:
		EchoParam();

		int getDelayTime();
		int getDelayFactor();

		friend std::istream& operator>>(std::istream& is, EchoParam& opts)
		{
			is >> opts.m_delayTime >> opts.m_delayFactor;
			return is;
		}

		friend std::ostream& operator<<(std::ostream& os, const EchoParam& opts)
		{
			os << "Delay time: " << opts.m_delayTime << ", Delay factor: " << opts.m_delayFactor;
			return os;
		}

	private:
		int m_delayTime;
		int m_delayFactor;
	};

	class Echo : public IEffect
	{
	public:
		Echo(const EchoParam& echoParam);

		void process(cycfi::q::wav_memory& wav) override;

	private:
		EchoParam m_echoParam;
	};
}