#pragma once

#include "IEffect.h"

#include <iostream>

namespace effects 
{
	class AmplifyParam
	{
	public:
		AmplifyParam();

		friend std::istream& operator>>(std::istream& is,  AmplifyParam& opts)
		{
			return is;
		}

		friend std::ostream& operator<<(std::ostream& os, const AmplifyParam& opts)
		{
			return os;
		}

	private:

	};

	class Amplify : public IEffect
	{
	public:
		Amplify(const AmplifyParam& amplifyParam);

		void process(cycfi::q::wav_memory& wav) override;

	private:
		AmplifyParam m_amplifyParam;
	};
}