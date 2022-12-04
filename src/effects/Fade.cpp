#include "Fade.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace effects 
{
	Fade::Fade(const FadeParam& FadeParam)
		: m_fadeParam(FadeParam)
	{
	
	}

	FadeParam Fade::getParam()
	{
		return m_fadeParam;
	}

	kfr::univector<kfr::fbase> Fade::process(const kfr::univector<kfr::fbase>& input, const kfr::audio_format_and_length& format)
	{
		spdlog::info("Applying Fade effect with parameters: {}", m_fadeParam);
		kfr::univector<kfr::fbase> out = input;
		std::size_t length = format.samplerate * m_fadeParam.getFadeTime() * 2;
		double mSample = 0;
        double mSampleCnt = format.samplerate * m_fadeParam.getFadeTime() * 2;
		//kfr::univector<kfr::fbase> history(histLen);

		if (m_fadeParam.getFadeTime() == 0.0)
		{
			return out;
		}

       
        for (auto i = 0; i < length; i++)
		{
		    out[i] = (input[i] * (mSample++))/mSampleCnt;
		}
        
        /*else
        {
            for (auto i = 0; i < length; i++)
		    {
			out[i] = (input[i] * (mSampleCnt - 1 - mSample++))/mSampleCnt;
		    }
        }*/
        
		return out;
	}

	FadeParam::FadeParam() : m_fadeTime(0)
	{
	}
/*
	bool FadeParam::getFadeType()
	{
		return m_fadeType;
	}*/

	float FadeParam::getFadeTime()
	{
		return m_fadeTime;
	}

    std::string fadeType(bool type)
    {
        std::string out;
        if (type == true)
        {
            out = "Out";
        }
        else
        {
            out = "In";
        }
        return out;
    }

	std::istream& operator>>(std::istream& is, FadeParam& opts)
	{
		is >>  opts.m_fadeTime;
		return is;
	}

	std::ostream& operator<<(std::ostream& os, const FadeParam& opts)
	{
		os << "Fade In" << ", fade time: " << opts.m_fadeTime;
		return os;
	}
}