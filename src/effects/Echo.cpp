#include "Echo.h"

namespace audio {
	EchoParam::EchoParam() : m_delayFactor(0), m_delayTime(0)
	{
	}

	int EchoParam::getDelayTime()
	{
		return m_delayTime;
	}

	int EchoParam::getDelayFactor()
	{
		return m_delayFactor;
	}

	std::istream& operator>>(std::istream& is, EchoParam& opts)
	{
		is >> opts.m_delayTime >> opts.m_delayFactor;
		return is;
	}

	std::ostream& operator<<(std::ostream& os, EchoParam& opts)
	{
		os << "Delay time: " << opts.m_delayTime << ", Delay factor: " << opts.m_delayFactor;
		return os; 
	}
}