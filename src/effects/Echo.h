#pragma once

#include <iostream>

namespace audio {
	struct EchoParam;

	class Echo
	{
	};

	struct EchoParam
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