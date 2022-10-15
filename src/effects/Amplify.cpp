#include "Amplify.h"

namespace effects 
{
	Amplify::Amplify(const AmplifyParam& amplifyParam)
	{
	}

	void Amplify::process(const cycfi::q::wav_memory& wav)
	{

	}

	AmplifyParam::AmplifyParam()
	{
	}

	std::istream& operator>>(std::istream& is, AmplifyParam& opts)
	{
		return is;
	}

	std::ostream& operator<<(std::ostream& os, AmplifyParam& opts)
	{
		return os;
	}
}