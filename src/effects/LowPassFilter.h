#pragma once

#include "IEffect.h"

namespace effects
{
	class LowPassFilterParam 
	{
	public:
		LowPassFilterParam();

		friend std::istream& operator>>(std::istream& is, LowPassFilterParam& opts);
		friend std::ostream& operator<<(std::ostream& os, const LowPassFilterParam& opts);
	private:
	
	};

	class LowPassFilter : public IEffect
	{
	public:
		LowPassFilter(const LowPassFilterParam& lowPassFilterParam);

		kfr::univector<kfr::fbase> process(const kfr::univector<kfr::fbase>&, const kfr::audio_format_and_length&) override;


	private:
		LowPassFilterParam m_lowPassFilterParam;
	};
}