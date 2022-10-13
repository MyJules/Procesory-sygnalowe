#pragma once

#include "IEffect.h"

#include <iostream>

namespace effects 
{
	class EchoParam;

	class Echo : public IEffect
	{
	public:
		Echo(const EchoParam& echoParam);

		void process() override { std::cout << "Echo\n"; }
	};

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
}