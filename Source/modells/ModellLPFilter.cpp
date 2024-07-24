/*
  ==============================================================================

    ModellLPFilter.cpp
    Created: 13 Oct 2023 4:41:42pm
    Author:  Michael

  ==============================================================================
*/

#include "ModellLPFilter.h"

ModellLPFilter::ModellLPFilter()
{
    // Set first 3 filters to highpass, and last 3 to lowpass
    for (int i = 0; i < filters.size(); ++i)
    {
        filters[i].setType(juce::dsp::StateVariableTPTFilterType::lowpass);
    }
}

void ModellLPFilter::prepare(juce::dsp::ProcessSpec spec)
{
    reset();

    for (auto& filter : filters)
    {
        filter.prepare(spec);
    }
}

void ModellLPFilter::process(juce::dsp::AudioBlock<float> dspAudioBlock)
{
    for (auto& filter : filters)
    {
        filter.process(juce::dsp::ProcessContextReplacing<float>(dspAudioBlock));
    }
}

// For access via buffer
void ModellLPFilter::renderNextBlock(juce::AudioBuffer<float>& outputBuffer)
{
    juce::dsp::AudioBlock<float> dspAudioBlock{ outputBuffer };

    for (auto& filter : filters)
    {
        filter.process(juce::dsp::ProcessContextReplacing<float>(dspAudioBlock));
    }
}

void ModellLPFilter::updateParameters(const float frequency)
{
    for (int i = 0; i < filters.size(); ++i)
    {
        filters[i].setCutoffFrequency(frequency);
    }
}

void ModellLPFilter::reset()
{
    for (auto& filter : filters)
    {
        filter.reset();
    }
}