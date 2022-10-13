#pragma once

#include "IEffect.h"

#include <iostream>

namespace effects 
{
	class AmplifyParam; 

	class Amplify : public IEffect
	{
	public:
		Amplify(const AmplifyParam& amplifyParam);

		void process() override { std::cout << "Amplify\n"; }

	private:
	};

	class AmplifyParam
	{
	public:
		AmplifyParam();

		friend std::istream& operator>>(std::istream& is, AmplifyParam& opts);
		friend std::ostream& operator<<(std::ostream& os, AmplifyParam& opts);

	private:
	
	};
}