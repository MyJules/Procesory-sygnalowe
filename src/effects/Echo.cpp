#include "Echo.h"

namespace effects 
{
	Echo::Echo(const EchoParam& echoParam)
	{
	
	}

	void Echo::process()
	{

	}

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
}