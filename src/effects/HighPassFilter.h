#pragma once

#include "IEffect.h"

namespace effects
{
	class HighPassFilterParam 
	{
	public:
	 HighPassFilterParam();

		float getFrequency() const;
		int getRollOff() const;

		friend std::istream& operator>>(std::istream& is, HighPassFilterParam& opts);
		friend std::ostream& operator<<(std::ostream& os, const HighPassFilterParam& opts);

	private:
		float m_frequency;
		int m_rollOff;
	};

	class HighPassFilter final : public IEffect
	{
	public:
	 HighPassFilter(const HighPassFilterParam& HighPassFilterParam);

		kfr::univector<kfr::fbase> process(const kfr::univector<kfr::fbase>&, const kfr::audio_format_and_length&) override;

	private:
	 HighPassFilterParam m_HighPassFilterParam;
	};
}