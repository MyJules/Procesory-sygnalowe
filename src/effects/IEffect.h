#pragma once

namespace effects
{
	class IEffect
	{
	public:
		virtual ~IEffect() = default;

		virtual void process() = 0;
	};
}