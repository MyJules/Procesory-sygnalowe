#pragma once

#include "IEffect.h"
#include "Echo.h"
#include "Amplify.h"

#include <memory>

namespace effects
{
	template <class Effect, class... Types>
	std::unique_ptr<IEffect> createEffect(Types&&... params)
	{
		return std::make_unique<Effect>(std::forward<Types>(params)...);
	}
}