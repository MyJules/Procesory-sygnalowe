#pragma once

#include "IEffect.h"

#include <iostream>

namespace effects
{
	class DelayParam
	{
	public:
		friend std::istream& operator>>(std::istream& is, DelayParam& opts)
		{

			return is;
		}

		friend std::ostream& operator<<(std::ostream& os, const DelayParam& opts)
		{
			return os;
		}

	private:


	};

	class Delay : public IEffect
	{
	public:
		Delay(const DelayParam& amplifyParam);
		void process() override;
		DelayParam getDelayParam() { return m_delayParam; };

	private:
		DelayParam m_delayParam;
	};

}