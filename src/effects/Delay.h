#pragma once

#include "IEffect.h"
#include <q/support/literals.hpp>
#include <q/fx/delay.hpp>
#include <q_io/audio_stream.hpp>
#include <q_io/audio_file.hpp>

#include <iostream>

namespace effects
{
	class DelayParam
	{
	public:
		DelayParam() : m_delay(0), m_feedback(0) {};
		DelayParam(cycfi::q::duration delay, float feedback, float y);

		cycfi::q::duration getDelay() { return m_delay; };
		float getFeedback() { return m_feedback; };

		friend std::istream& operator>>(std::istream& is, DelayParam& opts)
		{
			double delay;
			is >> delay;
			opts.m_delay = cycfi::q::duration(delay);
			return is >> opts.m_feedback;
		}

		friend std::ostream& operator<<(std::ostream& os, const DelayParam& opts)
		{
			return os << "Delay: " << opts.m_delay.rep << " Feedback: " << opts.m_feedback;
		}

	private:
		cycfi::q::duration m_delay;
		float m_feedback;

	};

	class Delay : public IEffect
	{
	public:
		Delay(const DelayParam& amplifyParam);
		void process(cycfi::q::wav_memory& wav) override;
		DelayParam getDelayParam() { return m_delayParam; };

	private:
		DelayParam m_delayParam;
	};

	class DelayProcessor : public cycfi::q::port_audio_stream
	{
	public:
		DelayProcessor(Delay delay, cycfi::q::wav_memory& wav) : m_delay(delay), m_wav(wav), port_audio_stream(0, 2, wav.sps()) {};
		void process(const out_channels& out);

	private:
		cycfi::q::wav_memory& m_wav;
		Delay m_delay;
		float m_y = 0.0f;
	};
}