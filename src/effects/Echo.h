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

		friend std::istream& operator>>(std::istream& is, EchoParam& opts);
		friend std::ostream& operator<<(std::ostream& os, EchoParam& opts);

	private:
		int m_delayTime;
		int m_delayFactor;
	};

	class Echo : public IEffect
	{
	public:
		Echo(const EchoParam& echoParam);

		void process(const cycfi::q::wav_memory& wav) override;

	private:
		EchoParam m_echoParam;
	};
}