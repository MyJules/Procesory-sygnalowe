#include "Delay.h"

effects::DelayParam::DelayParam(cycfi::q::duration delay, float feedback, float y)
	: m_delay(delay), m_feedback(feedback)
{
}

effects::Delay::Delay(const DelayParam& amplifyParam)
	: m_delayParam(amplifyParam)
{
}


void effects::Delay::process(cycfi::q::wav_memory& wav)
{
	DelayProcessor processor(*this, wav);
	if (processor.is_valid())
	{
		processor.start();
		cycfi::q::sleep(cycfi::q::duration(wav.length()) / wav.sps());
		processor.stop();
	}
}

void effects::DelayProcessor::process(out_channels const& out)
{
    auto left = out[0];
    auto right = out[1];
    cycfi::q::delay delay(cycfi::q::duration(m_delay.getDelayParam().getDelay()), m_wav.sps());
    float feedback = m_delay.getDelayParam().getFeedback();

    for (auto frame : out.frames())
    {
        // Get the next input sample
        auto sample = m_wav()[0];

        // Mix the signal and the delayed signal
        m_y = sample + delay();

        // Feed back the result to the delay
        delay.push(m_y * feedback);

        // Output
        left[frame] = sample;
        right[frame] = m_y;
    }
}