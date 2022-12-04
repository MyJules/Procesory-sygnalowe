#pragma once

#include "IEffect.h"

#include <iostream>

namespace effects 
{
	class FadeParam
	{
	public:
		FadeParam();

		//bool getFadeType();
		float getFadeTime();

        friend std::string fadeType(bool type);
		friend std::istream& operator>>(std::istream& is, FadeParam& opts);
		friend std::ostream& operator<<(std::ostream& os, const FadeParam& opts);

	private:
		//bool m_fadeType;
		float m_fadeTime;
	};

	class Fade final : public IEffect
	{
	public:
		Fade(const FadeParam& fadeParam);

		FadeParam getParam();
		kfr::univector<kfr::fbase> process(const kfr::univector<kfr::fbase>& input, const kfr::audio_format_and_length& format) override;

	private:
		FadeParam m_fadeParam;
	};
}