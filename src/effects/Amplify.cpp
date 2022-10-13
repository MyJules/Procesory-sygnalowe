#include "Amplify.h"

namespace effects 
{
	Amplify::Amplify(const AmplifyParam& amplifyParam)
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