#pragma once

#include "IEffect.h"

#include <iostream>

namespace effects 
{
	class AmplifyParam
	{
	public:
		AmplifyParam();

		friend std::istream& operator>>(std::istream& is, AmplifyParam& opts);
		friend std::ostream& operator<<(std::ostream& os, AmplifyParam& opts);

	private:

	};

	class Amplify : public IEffect
	{
	public:
		Amplify(const AmplifyParam& amplifyParam);

		void process(const cycfi::q::wav_memory& wav) override;

	private:
		AmplifyParam m_amplifyParam;
	};
}